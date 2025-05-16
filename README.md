<h1 align="center">🔆 SolarSwitch AutoRelayESP 🔌</h1>

<p align="center">
  <img src="https://img.icons8.com/emoji/96/solar-panel.png" height="64"/>
  <img src="https://img.icons8.com/color/96/esp8266.png" height="64"/>
  <img src="https://img.icons8.com/external-flatart-icons-flat-flatarticons/64/000000/external-relay-electronic-device-flatart-icons-flat-flatarticons.png" height="64"/>
</p>

<p align="center">
  <strong>Smart IoT System to Auto-Switch Power Based on Solar Activity using ESP8266, INA219, OLED & Blynk</strong>
</p>

<p align="center">
  <a href="https://github.com/yourusername/SolarSwitch-AutoRelayESP/stargazers">
    <img src="https://img.shields.io/github/stars/yourusername/SolarSwitch-AutoRelayESP?color=yellow&style=for-the-badge" alt="Stars"/>
  </a>
  <a href="https://github.com/yourusername/SolarSwitch-AutoRelayESP/fork">
    <img src="https://img.shields.io/github/forks/yourusername/SolarSwitch-AutoRelayESP?color=blue&style=for-the-badge" alt="Forks"/>
  </a>
  <img src="https://img.shields.io/badge/ESP8266-Enabled-blue?style=for-the-badge&logo=wifi" />
  <img src="https://img.shields.io/badge/Blynk-Integrated-brightgreen?style=for-the-badge&logo=blynk" />
</p>

---

## 🚀 Overview

**SolarSwitch AutoRelayESP** is an IoT-powered smart energy management system that:

- 🟢 Monitors real-time voltage, current & power from a solar panel using **INA219**
- 🔁 Automatically toggles a **relay** to switch between solar & backup sources
- 📲 Syncs with **Blynk App** for live monitoring via mobile
- 📟 Displays key stats on an **OLED screen**
- ⚡️ Built with **ESP8266**, it's affordable, energy-efficient, and WiFi-ready

---

## 📸 Project Demo (Preview)

> *Add your image or GIF of OLED + Blynk UI below*  
![demo-placeholder](https://img.icons8.com/clouds/500/solar-panel.png)

---

## 🔧 Features

✅ Real-time Solar Power Detection  
✅ Auto-Switch Relay when Solar Power Drops  
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

---

## 🧠 How It Works

```mermaid
flowchart TD
    A[INA219 Reads Solar Values] --> B{Is Solar Power Available?}
    B -- Yes --> C[Turn ON Relay | Use Solar Power]
    B -- No --> D[Switch to Backup Power Source]
    C --> E[Update Blynk + OLED]
    D --> E
