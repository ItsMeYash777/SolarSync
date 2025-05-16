#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Energy Monitoring"
#define BLYNK_AUTH_TOKEN "YOUR_TOKEN"
#define BLYNK_FIRMWARE_VERSION "0.1.0"

#define BLYNK_PRINT Serial
#define APP_DEBUG

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <Adafruit_INA219.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

// OLED Display Configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
// #define RELAY_PIN 12 

// WiFi Credentials
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "POCO F6";
char pass[] = "12345678";

// Sensor Objects
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_INA219 ina219_solar(0x40);
Adafruit_INA219 ina219_bus(0x41);
Adafruit_INA219 ina219_load(0x44);

// Energy Tracking
float energyGenerated = 0.00;
float energyCost = 0.00;
float previousEnergyGenerated = 0.00;
float energyPrice = 6.50;

// Latest Sensor Readings
float voltage_solar, current_solar, power_solar;
float voltage_bus, current_bus, power_bus;
float voltage_load, current_load, power_load;

// Blynk Virtual Pins
const int VPIN_SOLAR = 0;   // Solar Power Generation
const int VPIN_LOAD = 1;    // Power Consumed by Load
const int VPIN_BUS = 2;     // Power Sent via Bus
const int VPIN_ENERGY = 3;  // Total Energy Generated
const int VPIN_COST = 4;    // Energy Cost
const int VPIN_TEST = 5;

// Function Prototypes
void scanI2CDevices();
void readAllSensors();
void sendBatchToBlynk();
void readSensor(Adafruit_INA219 &sensor, const char *sensorName, float &voltage, float &current, float &power);
void displayData();
void checkAlerts();

BlynkTimer timer;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  Serial.print("Connecting to WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");

  Blynk.config(auth);

  Wire.begin(4, 5);  // SDA = GPIO4 (D2), SCL = GPIO5 (D1)

  // Scan I2C Devices
  scanI2CDevices();

  // Initialize OLED Display
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (1)
      ;
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(10, 30);
  display.print("IoT Energy Meter");
  display.display();
  pinMode(D5, OUTPUT);
digitalWrite(D5, LOW); 

  // Initialize INA219 Sensors
  if (!ina219_solar.begin()) Serial.println("Failed to find INA219 at 0x40 (Solar)");
  if (!ina219_bus.begin()) Serial.println("Failed to find INA219 at 0x41 (Bus)");
  if (!ina219_load.begin()) Serial.println("Failed to find INA219 at 0x44 (Load)");

  // Set timers: read sensors every 2s, send batch every 60s
  timer.setInterval(2000L, readAllSensors);
  timer.setInterval(60000L, sendBatchToBlynk);
}

void loop() {
  Blynk.run();
  timer.run();
}

// Function to Scan I2C Devices
void scanI2CDevices() {
  Serial.println("Scanning for I2C devices...");
  byte error, address;
  int nDevices = 0;
  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("I2C device found at 0x");
      Serial.println(address, HEX);
      nDevices++;
    }
  }
  if (nDevices == 0) Serial.println("No I2C devices found.");
}
// Track last known states to prevent repeated alerts
bool lastSolarActive = false;
bool lastLowSolar = false;
bool lastNoPower = false;
bool lastNeighborPower = false;
bool lastNeighborUnavailable = false;

void checkAlerts() {
  if (power_solar <= 0.5) {
  digitalWrite(D5, LOW);  // Turn ON relay (active LOW)
  Serial.println("⚡ Switching to backup source (Relay ON)");
} 

  if (power_solar > 5.0) {
    if (!lastSolarActive) {  // Send alert only if state changes
      Blynk.virtualWrite(10, "✅ Solar Panel Active: Using Solar Energy");
      lastSolarActive = true;
    }
  } else {
    lastSolarActive = false;
  }

  if (power_solar > 1.0 && power_solar <= 5.0) {
    if (!lastLowSolar)   {
      Blynk.logEvent("low_solar", "🌑 Low Solar Power: Switching to Battery");
      lastLowSolar = true;
    }
  } else {
    lastLowSolar = false;
  }

  if (power_solar <= 0.1 && power_bus <= 0.1) {
    if (!lastNoPower) {
      Blynk.logEvent("no_power", "🚨 No Solar, No Battery: Using Neighbor Power");
      Blynk.virtualWrite(10, "🚨 No Solar, No Battery: Using Neighbor Power");
      lastNoPower = true;
    }
  } else {
    lastNoPower = false;
  }

  if (power_bus > 5.0) {
    if (!lastNeighborPower) {
      Blynk.logEvent("neighbor_power", "⚠️ Using Neighbor Power");
      lastNeighborPower = true;
    }
  } else {
    lastNeighborPower = false;
  }

  if (power_bus <= 0.1) {
    if (!lastNeighborUnavailable) {
      Blynk.logEvent("neighbor_unavailable", "🚨 No Power Available! Check System");
      lastNeighborUnavailable = true;
    }
  } else {
    lastNeighborUnavailable = false;
  }
}



// Read all sensors and update latest values
void readAllSensors() {
  readSensor(ina219_solar, "Solar", voltage_solar, current_solar, power_solar);
  readSensor(ina219_bus, "Bus", voltage_bus, current_bus, power_bus);
  readSensor(ina219_load, "Load", voltage_load, current_load, power_load);
  // Track total energy generated
  static unsigned long lastUpdateTime = millis();
  unsigned long currentTime = millis();
  float timeElapsed = (currentTime - lastUpdateTime) / 3600000.0;  // Convert ms to hours
  lastUpdateTime = currentTime;

  energyGenerated += power_solar * timeElapsed;  // More accurate energy calculation
  float energyDifference = energyGenerated - previousEnergyGenerated;
  previousEnergyGenerated = energyGenerated;
  energyCost += (energyPrice / 1000 * energyDifference);

  displayData();
  checkAlerts();
}

// Read sensor values, allowing for bidirectional current
void readSensor(Adafruit_INA219 &sensor, const char *sensorName, float &voltage, float &current, float &power) {
  float busVoltage = sensor.getBusVoltage_V();
  float shuntVoltage = sensor.getShuntVoltage_mV();
  float measuredCurrent = sensor.getCurrent_mA();

  if (isnan(busVoltage) || isnan(shuntVoltage) || isnan(measuredCurrent)) {
    Serial.println(String(sensorName) + " | ERROR: Sensor Read Failed");
    voltage = current = power = 0;
    return;
  }

  voltage = busVoltage + (shuntVoltage / 1000);
  current = measuredCurrent;           // Allow negative values for bidirectional flow
  power = voltage * (current / 1000);  // Convert mA to A

  // Print data to Serial Monitor
  Serial.print(sensorName);
  Serial.print(" | Voltage: ");
  Serial.print(voltage);
  Serial.print("V | Current: ");
  Serial.print(current);
  Serial.print("mA | Power: ");
  Serial.print(power);
  Serial.println("W");
}



// Send batch update to Blynk, including energy & cost
void sendBatchToBlynk() {
  // Blynk.virtualWrite(VPIN_TEST, 12);
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    String server = "blynk.cloud";
    String token = auth;
    String url = "http://" + server + "/external/api/batch/update?token=" + token;

    url += "&V" + String(VPIN_SOLAR) + "=" + String(power_solar * 15, 2);
    url += "&V" + String(VPIN_LOAD) + "=" + String(power_load * 12, 2);
    url += "&V" + String(VPIN_BUS) + "=" + String(power_bus, 2);
    url += "&V" + String(VPIN_ENERGY) + "=" + String(energyGenerated, 2);
    url += "&V" + String(VPIN_COST) + "=" + String(energyCost, 2);
    url += "&V" + String(VPIN_TEST) + "=" + String(voltage_bus, 2);
    


    http.begin(client, url);
    int httpCode = http.GET();
    if (httpCode > 0) {
      Serial.println("Batch data sent successfully.");
    } else {
      Serial.println("Error sending batch update: " + http.errorToString(httpCode));
    }
    http.end();
  }
}

// Display data on OLED
void displayData() {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);

  display.setCursor(0, 5);
  display.printf("Solar Power: %.2fW\n", power_solar);
  display.setCursor(0, 20);
  display.printf("Load Power: %.2fW\n", power_load);
  display.setCursor(0, 35);
  display.printf("Energy: %.2fWh\nCost: Rs%.2f\n", energyGenerated, energyCost);

  display.display();
}
