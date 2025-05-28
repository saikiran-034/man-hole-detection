# IoT-Based Manhole Detection and Monitoring System

## Project Title
**IoT-Based Manhole Detection and Monitoring System**

## Team Members
- **Madasai Kiran**
- **Mallarappu Maheshwari**   
- **Bayyanagari Maina** 

## Guide
**Dr. K. Kamakshaiah**

---

## 📄 Abstract

Smart city infrastructure includes an effective underground drainage system to ensure hygiene and safety. The current manual monitoring systems are inefficient and pose health risks to sanitation workers. This project proposes an IoT-based real-time monitoring system using wireless sensor networks that detect hazardous gas levels, water levels, and blockages. Alerts are sent through GSM/GPS to the concerned municipal authorities, enabling prompt action and reducing manual inspection needs.

---

## 🔍 Contents
- Abstract  
- Existing System  
- Proposed System  
- System Configuration  
- System Architecture  
- System Design  
- Literature Survey  
- Pros & Cons  
- Sample Prototype  
- Sample Code  
- Output Screens  
- References  
- Conclusion

---

## 🚫 Existing System

- Manual and non-automated drainage monitoring.
- Inability to pinpoint blockages.
- No alert mechanism for overflows or toxic gas detection.
- Risky and time-consuming for sanitation workers.

---

## ✅ Proposed System

- Integrates sensors (flow, gas, level, tilt, temperature) with **Arduino Uno**.
- Sends alerts via **GSM module (SIM8008)** and tracks location using **GPS**.
- Real-time data transmission using **IoT and ThingSpeak**.
- Displays data locally on **LCD** and remotely on web platforms.
- Reduces manual labor, improves response time, and enhances safety.

---

## ⚙️ System Configuration

### Software Requirements
- Arduino IDE  
- Embedded C  
- Windows OS

### Hardware Components
- Arduino Uno  
- SIM8008 (GSM Module)  
- LCD Display  
- Power Supply  
- DC Motor  
- LEDs  
- Sensors: Water, Gas, Tilt, Temperature  
- Mobile Phone (for receiving alerts)

---

## 🛠️ Sample Code Snippet

```c
#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
#include <SoftwareSerial.h>
#include <dht11.h>
#define RX 9
#define TX 10

SoftwareSerial esp8266(RX, TX);
#define trigger A1
#define echo A2
int sensorPin = A0;
int led = 12;

void setup() {
  lcd.begin(16, 2);
  lcd.print("IOT BASED MANHOLE");
  lcd.setCursor(0, 1);
  lcd.print("  MONITORING");
  delay(1000);

  pinMode(led, OUTPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  Serial.begin(9600);
  esp8266.begin(115200);
}
