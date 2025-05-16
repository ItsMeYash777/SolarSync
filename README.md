<h1 align="center">
  🔆 SolarSwitch AutoRelayESP 🔌
</h1>

<p align="center">
  <img src="https://img.icons8.com/emoji/96/solar-panel.png" alt="Solar Panel" />
  <img src="https://img.icons8.com/color/96/esp8266.png" alt="ESP8266" />
  <img src="https://img.icons8.com/fluency/96/relay.png" alt="Relay Module" />
</p>

<p align="center">
  <b>Smart Solar-Powered Relay System</b> using <code>ESP8266</code>, <code>INA219</code> Current Sensor & <code>Blynk</code> for Real-Time Monitoring.
</p>

---

## ⚙️ Features

- 📡 **Real-time power monitoring** using INA219 (Voltage, Current, Power)
- 🔀 **Automatic relay switching** based on solar power availability
- ☁️ **Blynk app integration** to display real-time values on your smartphone
- 💡 **OLED display** for quick physical readouts
- 🔋 Smart switching between solar panel and alternate power sources

---

## 🧠 How It Works

1. The system reads current, voltage, and power values from the **INA219 sensor**.
2. It calculates whether solar power is actively generating electricity.
3. If no power is detected from the solar panel, it automatically switches the **relay** to a backup power source.
4. All real-time data is sent to the **Blynk IoT app** for remote monitoring.
5. An **OLED display** shows essential metrics on-device.

---

## 🛠️ Hardware Used

| Component             | Description                            |
|----------------------|----------------------------------------|
| ESP8266 (NodeMCU)     | Microcontroller with WiFi capability   |
| INA219                | Current, Voltage & Power sensor        |
| Relay Module          | To switch between power sources        |
| Solar Panel           | Power generator                        |
| Battery               | Connected as load                      |
| OLED Display (I2C)    | For on-device stats                    |

---

## 📱 Blynk Dashboard

Monitor values live in your Blynk app:

- ⚡ Voltage (V)
- 🔌 Current (mA)
- ⚙ Power (W)

You can customize widgets as per your setup.

---

## 📁 File Structure

```bash
SolarSwitch-AutoRelayESP/
├── SolarRelayAutoSwitch.ino   # Main code file
└── README.md                  # You're here!
