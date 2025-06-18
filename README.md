# project_V01D
This is project V01D

<img src="https://github.com/5H4RV1L/project_V01D/blob/main/Hardware/device.jpg?raw=true" width="250">

> A pocket-sized, open-source cyber tool inspired by Flipper Zero — designed for Wi-Fi, BLE, and IR mischief. Built using an ESP32-CAM with OLED, buttons, and clean firmware. For educational purposes only. 🧠⚡

---

## 🚀 Overview

**Project V01D** is a DIY hacker device that fits in your palm. It's capable of beacon floods, IR blasting, BLE spoofing, evil portal phishing, and more. Built entirely with affordable components and Arduino code, it brings serious pentest functionality to the streets.<br>
(Project V01D is still in beta version)

---

## 🛠 Features

* 📶 **Beacon Flood** (Custom SSID spam)
* ❌ **Wi-Fi Fake Deauth** *(WIP)*
* 🌐 **Evil Portal** (Captive portal phishing)
* 📡 **BLE Advertise Spoof** (e.g., AirPods, BoAt)
* 👻 **BLE Spam** (Name overload)
* 🔇 **BLE Jammer** *(Experimental)*
* 📺 **IR Blaster**
* 🔁 **IR Replay**

---

## 🧩 Parts List

| Component                      | Description                                                  |
| ------------------------------ | ------------------------------------------------------------ |
| **ESP32-CAM**                  | Main controller with built-in Wi-Fi, BLE, and camera support |
| **0.96" I2C OLED**             | Compact display to navigate and interact with tool features  |
| **3.7V to 5V Boost Converter** | Boosts LiPo voltage to 5V for ESP32 and OLED                 |
| **TP4056 Module**              | Li-ion battery charging + protection circuit (USB charging)  |
| **3 × Tactile Buttons**        | For menu navigation and IO0 flashing control                 |
| **3-Way Switch**               | Toggle between ON, OFF, and Flashing (IO0–GND) modes         |
| **External 2.4GHz Antenna**    | Enhances Wi-Fi range (connects to ESP32-CAM’s u.FL port)     |
| **3.7V Li-ion Battery**        | Portable power source (600–1000mAh recommended)              |
| **2 × IR Transmitters**        | Used for IR blasting + replay functionality                  |
| **1 × TSOP Receiver**          | Infrared receiver module to record IR signals                |
| **Jumper Wires**               | Used to wire everything together cleanly                     |

---

## ⚙️ Hardware Specs

* **MCU**: ESP32-CAM (with removable camera module)
* **Display**: 0.96" I2C OLED
* **Inputs**:

  * 1 × `Select` Button
  * 1 × `Down` Button
  * 1 × `IO0 Flash` Button
  * 1 × 3-way Power/Flash/Off switch
* **Power**: 3.7V Li-ion via boost to 5V (1A+ current recommended)
* **Connectivity**: Wi-Fi, BLE, IR
* **Antenna**: Optional external 2.4GHz for better Wi-Fi range

---

## 🎮 Controls & Usage

| Button / Switch | Action                               |
| --------------- | ------------------------------------ |
| `Down Button`   | Navigate down / Exit                 |
| `Select Button` | Start / Select / Stop                |
| `Switch`        | ON / OFF / Program (pull IO0 to GND) |

### ⚡ Notes

* Use a **high current 3.7V battery** with a boost converter to 5V
* Do **not** cover the **ESP32-CAM’s RF shield** — it gets hot!
* Remove the **TSOP out pin** connected to **GPIO2** before entering flash mode
* Change the value of **USER_NAME** in **project_V01D.ino and menu.h** to whatever you want to be displayed (not 
necessary for code to run)
### 🔧 Development Info

* Arduino IDE (recommended)
* Use **ESP32 Board Version 2.0.7**
* Code written in Arduino C++

---

## 🧠 How It Works

Each tool is a menu option navigable via OLED. The select button runs or stops tools like beacon flood, BLE advertise, or IR replay. New tools can be added by extending the firmware and UI logic. You can flash via USB-TTL by switching the 3-way toggle to flash mode (pulls IO0 to GND).

---

## ⚠️ Legal Disclaimer

This project is intended **strictly for educational and ethical hacking research only**. Do **not** use it to disrupt or attack networks you do not own or have explicit permission to test.

I am not responsible for any misuse. ⚠️

---

## 👤 Author

**Sharvil / V01D**
GitHub: [@5H4RV1L](https://github.com/5H4RV1L)
Insta: [@this\_aint\_void](https://instagram.com/this_aint_void)

---

## 📄 License

MIT License — open to hack, remix, and evolve.

---

## 📸 Gallery

> Will add build images, wiring photos, or demo GIFs here later!

---

## 💬 Contributions & Suggestions

Open to pull requests, ideas, or feature requests. Drop a DM or open an issue!

---

**Let V01D consume the signal 🕶️💀**
