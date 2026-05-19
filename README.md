# ESP32 Ultrasonic Distance Alert System

## Overview

A real-time embedded monitoring system using ESP32 and the HC-SR04 ultrasonic sensor for distance-based alert detection.

The system continuously measures object distance and provides visual and audible feedback using:

* SSD1306 OLED display
* Multi-state LED indicators
* Active buzzer alert

This project demonstrates practical embedded systems concepts including real-time sensing, signal timing, GPIO control, and state-based firmware logic.

---

## Features

* Real-time ultrasonic distance measurement
* Multi-state alert system
* OLED live distance display
* LED-based visual indication
* Audible buzzer alarm
* Serial Monitor debugging
* Embedded firmware structure
* Real-time sensor monitoring

---

## System States

| Distance | State   | Behavior             |
| -------- | ------- | -------------------- |
| > 10 cm  | SAFE    | Green LED ON         |
| 5–10 cm  | WARNING | Orange LED ON        |
| < 5 cm   | DANGER  | Blue LED + Buzzer ON |

---

## Hardware Components

* ESP32 Development Board
* HC-SR04 Ultrasonic Sensor
* SSD1306 OLED Display
* Green LED
* Orange LED
* Blue LED
* Active Buzzer
* 220Ω Resistors
* Breadboard
* Jumper Wires

---

## Pin Configuration

| Component    | ESP32 Pin |
| ------------ | --------- |
| HC-SR04 TRIG | GPIO5     |
| HC-SR04 ECHO | GPIO18    |
| Green LED    | GPIO15    |
| Orange LED   | GPIO2     |
| Blue LED     | GPIO4     |
| Buzzer       | GPIO14    |
| OLED SDA     | GPIO21    |
| OLED SCL     | GPIO22    |

---

## OLED Display

The OLED display shows:

* Current system state
* Live measured distance

Example:

SAFE
Distance: 14.2 cm

---

## Formula Used

The HC-SR04 measures ultrasonic echo travel time.

Distance calculation:

distance = (time × speed of sound) / 2

Where:

* speed of sound ≈ 0.0343 cm/µs
* division by 2 compensates for round-trip travel

---

## Project Structure

ESP32-Ultrasonic-Distance-Alert-System/

├── README.md
├── LICENSE
├── images/
│   ├── wiring.png
│   ├── oled_active.png
│   └── circuit_diagram.png
└── src/
└── ultrasonic_alert_system.ino

---

## Embedded Concepts Demonstrated

* GPIO control
* Real-time sensing
* Ultrasonic signal timing
* Distance calculation
* OLED I2C communication
* Event-driven firmware
* Multi-state embedded logic
* Hardware debugging
* Sensor integration

---

## Serial Monitor

Baud Rate:

115200

The Serial Monitor outputs live measured distance values for debugging and verification.

---


## Author

Milad Mohseni

Embedded Systems & IoT
