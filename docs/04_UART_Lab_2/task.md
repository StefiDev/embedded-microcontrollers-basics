# UART Lab 2: Advanced Control System

## Objective
Create a UART-based system in Tinkercad where two microcontrollers communicate to control peripherals.

## Requirements

### System Overview
- **Arduino 1**: Has a Potentiometer and an LED (LED 1).
- **Arduino 2**: Has a Button and an LED (LED 2).

### Functionality
1.  **Remote Brightness Control**:
    - The **Potentiometer** on **Arduino 1** controls the brightness of **LED 2** on **Arduino 2**.
2.  **Remote Switch**:
    - The **Button** on **Arduino 2** toggles the ON/OFF state of **LED 1** on **Arduino 1**.
3.  **Data Logging**:
    - **Arduino 2** must print the received ADC values (from the pot) to its Serial Terminal.
    - **Arduino 1** must print the state of LED 1 [ON or OFF] to its Serial Terminal.
