# I2C Lab 1: Master-Slave Sensor Reading

## Objective
Implement an I2C communication system where a Master Arduino requests sensor data from a Slave Arduino and displays it.

## System Architecture

### 1. Master (Arduino 1)
- **Role**: I2C Master.
- **Components**: Connected to an **I2C LCD Display (16x2)**.
- **Functionality**:
    - Periodically requests 1 byte of data from the Slave (Address 8).
    - Receives the byte (0-255).
    - Converts the received byte to a voltage value (0-5V).
    - Displays both the raw value and the calculated voltage on the LCD.

### 2. Slave (Arduino 2)
- **Role**: I2C Slave (Address 8).
- **Components**: Connected to a **Potentiometer** on pin A1.
- **Functionality**:
    - Reads the analog value from the potentiometer.
    - Maps the 10-bit value (0-1023) to an 8-bit value (0-255).
    - Sends the mapped value to the Master upon request.
