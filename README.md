# 🐶 Dog Activity Tracker (Simulated)

A simulated activity tracker for dogs using a virtual IMU sensor (QMI8658), accelerometer & gyroscope data, LCD output, and basic logic for classifying physical activity — built to run in Arduino environments or online simulators like [Wokwi](https://wokwi.com/).

---

## 📦 Features

- ✅ Simulated motion detection
- 📊 Classifies activity: **Resting**, **Walking**, **Running**, **Playing**
- 🖥️ Displays live activity status on **16x2 LCD**
- 📓 Logs last 10 detected activities in memory
- 🔄 Real-time activity update every 10 seconds
- 🧪 Perfect for testing ML integration with embedded motion data

---

## 🛠️ Technologies Used

- Arduino / C++
- Simulated IMU sensor class
- LiquidCrystal LCD Library
- Serial Monitor logging
- Compatible with **Wokwi Arduino Simulator**

---

## 🧪 How to Run

### 🖥️ On Wokwi (Recommended)

1. Go to [https://wokwi.com](https://wokwi.com)
2. Click **New Project**
3. Replace the default code with `dog_activity_tracker.ino`
4. Add a **16x2 LCD** and wire it to pins: `RS=12`, `E=11`, `D4=5`, `D5=4`, `D6=3`, `D7=2`
5. Hit **Start Simulation**
6. Open the **Serial Monitor** to see logs
