<h1 align="center">🔆 SolarSync 🔌</h1>

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

| 🔧 Component                  | 💡 Description                                                         |
| ----------------------------- | ---------------------------------------------------------------------- |
| 🌐 **ESP8266**                | WiFi-enabled microcontroller that sends real-time data to Blynk        |
| ⚡ **INA219**                  | Measures voltage, current, and power from the solar panel              |
| 🔌 **Relay Module**           | Switches load between solar power and backup power source              |
| 🔋 **Battery (Load)**         | Stores energy or acts as the system’s power consumer                   |
| 🌞 **Solar Panel**            | Primary energy source (18V output)                                     |
| 📟 **OLED Display**           | Displays voltage/current/power stats locally via I2C interface         |
| 🔁 **DC-DC Converter**        | Steps down 18V from solar panel to 12V for safe operation of system    |
| 🔻 **Schottky Diode (SB540)** | Prevents reverse current flow from battery to panel (low forward drop) |
| 🔌 **Wiring / Humpers**       | Connects all components securely with voltage-safe cabling             |


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

