# First Term Project: Voice Assistant for Device Control

## 1. Project Description
A voice assistant implemented on an embedded microcontroller platform (Arduino Uno with integrated ESP and Bluetooth Low Energy). The assistant recognizes predefined voice commands sent by the user via a mobile phone and controls connected hardware devices such as LEDs and sensors.

The core idea is to create a convenient and intuitive interface for control without physical buttons, using voice instructions. The system demonstrates embedded system principles: input capture (voice/BLE), processing, decision making, and output control.

**Target Audience**: Beginners in electronics, people with limited mobility, students of microcontrollers.

## 2. Functionality

### Core Functions
- **Voice Command Recognition**: Via phone app, sent as text over BLE.
- **Wireless Communication**: Bluetooth Low Energy (BLE).
- **Output Control**: LEDs simulations (lighting).
- **Sensor Reading**: Temperature measurement (DHT11).
- **Feedback**: Results shown on LCD display and sent back to phone as text.

### Example Commands
- "Turn on green LED"
- "Turn off all LEDs"
- "What is the temperature"
- "Disco" (Demonstration mode)

## 3. Hardware Requirements
- **Arduino Uno** (with built-in ESP & BLE)
- **LCD Display** (16x2 I2C)
- **3x LEDs** (Red, Green, Blue)
- **DHT11** Temperature Sensor
- **Breadboard** & Jumper Wires
- **Implementation**: Prototype on breadboard (Real Hardware).

## 4. System Architecture
- **Input**: Smartphone -> BLE
- **Processing**: Arduino UNO
- **Sensors**: DHT11
- **Output**: LEDs and LCD Display

**Logic**: The phone sends text commands via BLE. Arduino processes them to toggle LEDs, read temperature, or update the display.

## 6. Prototype Features
- **Lighting Control**: Individual or group control of Red, Green, and Blue LEDs.
- **Temperature**: "What is the temperature" triggers a reading from DHT11, displayed on LCD and sent back to the phone (e.g., "Temperature is 23.4 °C").
- **Disco Mode**: A demonstration mode where LEDs flash in a rhythmic pattern.
