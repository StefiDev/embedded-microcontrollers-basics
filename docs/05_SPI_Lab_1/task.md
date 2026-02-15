# SPI Lab 1: Environmental Monitoring System

## Objective
Build an SPI-based system where one Master Arduino collects data from two Slave Arduinos and displays it on a third Slave Arduino.

## System Architecture

### 1. Master (Arduino 1)
- Acts as the central SPI controller.
- Periodically queries **Arduino 2** and **Arduino 3** for data.
- Sends display commands to **Arduino 4**.
- Logs descriptive messages to the Serial Monitor for debugging (e.g., "Polling Temp Sensor...", "Received value: 153").

### 2. Temperature Sensor (Arduino 2)
- Interface: **Slave**.
- Hardware: Connected to a **TMP36** temperature sensor.
- Function: Reads temperature and sends the value to Master when queried.

### 3. Light Sensor (Arduino 3)
- Interface: **Slave**.
- Hardware: Connected to a **Photoresistor**.
- Function: Reads ambient light level and sends the value to Master when queried.

### 4. Visual Display (Arduino 4)
- Interface: **Slave**.
- Hardware: Connected to **2 NeoPixel Rings/Strips** (10-16 LEDs).
- Function: Updates color and brightness based on commands from Master.

#### Visualization Logic:
- **Temperature (Color)**:
    - **Cold (< 15°C)**: Blue
    - **Moderate (15°C - 28°C)**: Green
    - **Warm (> 28°C)**: Red
- **Light Level (Pixels Lit)**:
    - **Dark**: Few pixels lit (1-3).
    - **Bright**: All/Most pixels lit (10-12).
