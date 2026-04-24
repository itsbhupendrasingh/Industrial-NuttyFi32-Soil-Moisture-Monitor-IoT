# Industrial-NuttyFi32-Soil-Moisture-Monitor-IoT
Industrial IoT soil moisture monitoring system with modern web dashboard
# 🌱 Smart Soil Moisture Monitor With NuttyFi32

A real-time IoT-based soil moisture monitoring system using ESP32 (NuttyFi32) with a live web dashboard.

---

## Features

- 📡 Real-time moisture monitoring
- 🌐 Live web dashboard (no refresh)
- 📱 Mobile-friendly UI
- 🌱 Visual plant indicator (Dry / Medium / Healthy)
- 📶 Captive portal support (auto-open dashboard)
- 🎨 Modern UI design

---

## 🧰 Hardware Used

- NuttyFi32 (ESP32-based board)
- Capacitive Soil Moisture Sensor
- Custom Interfacing PCB (Designed by SME Dehradun)
- Jumper Wires (Female-Female)
- USB Type-C Cable

---

## 🔌 Sensor Used

![Soil Sensor](images/sensor.jpg)

---

## ⚙️ Working Principle

- Sensor outputs analog voltage based on soil moisture
- ESP32 reads ADC value
- Data is mapped to percentage
- Web dashboard updates in real-time using AJAX

---

## 📊 Dashboard Preview

(upding soon dashboard screenshot)

---

## 🛠️ Setup

1. Connect sensor to ESP32 ADC pin (GPIO34)
2. Power using 3.3V
3. Upload code from `/code/NuttyFi32_IoT.ino`
4. Open Serial Monitor → get IP or connect via AP mode

---

## 🌐 Access Dashboard

- Normal Mode (check serial monitor at 115200 Baud Rate:  
  `http://<Nuttyfi32_IP>`

- Captive Portal Mode (Automatically open the dashboard once anyone connected):  
  Connect to WiFi → Dashboard opens automatically

---

## 🏢 Developed By

**SME Dehradun**

We design and develop:
- IoT Systems
- Industrial Prototypes
- Custom Electronics Products

🌐 https://www.smedehradun.com  
🛒 https://www.nuttyengineer.com  

---

## 📩 Need a Custom Product?

We help startups and companies turn ideas into real working products.

👉 Contact us via website
