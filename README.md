<h1 align="center">🔆 SolarSwitch 🔌</h1>

<p align="center">
  <img src="https://img.icons8.com/emoji/96/solar-panel.png" height="64"/>
  <img src="https://img.icons8.com/color/96/esp8266.png" height="64"/>
  <img src="https://img.icons8.com/external-flatart-icons-flat-flatarticons/64/000000/external-relay-electronic-device-flatart-icons-flat-flatarticons.png" height="64"/>
</p>

<p align="center">
  <strong>Smart IoT System to Auto-Switch Power Based on Solar Activity using ESP8266, INA219, OLED & Blynk</strong>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/ESP8266-Enabled-blue?style=for-the-badge&logo=wifi" />
  <img src="https://img.shields.io/badge/Blynk-Integrated-brightgreen?style=for-the-badge&logo=blynk" />
</p>

---

## 🚀 Overview

**SolarSwitch** is an IoT-powered smart energy management system that:

- 🟢 Monitors real-time voltage, current & power from a solar panel using **INA219**
- 🔁 Automatically toggles a **relay** to switch between solar & backup sources
- 📲 Syncs with **Blynk App** for live monitoring via mobile
- 📟 Displays key stats on an **OLED screen**
- ⚡️ Built with **ESP8266**, it's affordable, energy-efficient, and WiFi-ready

---


## 🔧 Features

✅ Real-time Solar Power Detection  
✅ OLED Display for Live Data  
✅ Blynk Dashboard Integration  
✅ Simple Arduino Setup  
✅ Budget-Friendly Smart Grid Tool  

---

## 🧰 Hardware Required

| Component         | Description                          |
|------------------|--------------------------------------|
| 🌐 ESP8266        | WiFi-enabled microcontroller         |
| ⚡ INA219         | Voltage, current & power sensor      |
| 🔌 Relay Module   | Switch between power sources         |
| 🔋 Battery        | Load device or power storage         |
| 🌞 Solar Panel    | Main energy source                   |
| 📟 OLED Display   | On-device power stats (via I2C)      |

---

## 📲 Blynk UI

Configure your Blynk mobile app to show:

- Voltage (V)
- Current (mA)
- Power (W)

You can use **Gauge**, **Label**, or **Graph** widgets.

![1000085322](https://github.com/user-attachments/assets/a0cce10b-699e-414b-aac6-cf20c6b6aea8)
![1000085323](https://github.com/user-attachments/assets/1f6e186f-1914-476e-a38e-89b73b226cd6)
![1000085321](https://github.com/user-attachments/assets/21ca7430-b8d2-44c5-bd06-a887c45f8969)


---

## 🧠 How It Works

flowchart TD
    A[INA219 Reads Solar Values] --> B{Is Solar Power Available?}
    B -- Yes --> C[Turn ON Relay: Use Solar Power]
    B -- No --> D[Switch to Backup Power Source]
    C --> E[Update Blynk and OLED]
    D --> E

