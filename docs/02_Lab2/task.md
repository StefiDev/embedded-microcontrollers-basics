# Lab 2: Running Lights and Inputs

## Task 1: Basic Running Light
Create a "running light" effect with 4 LEDs.
- **Behavior**: Each subsequent LED should light up with a delay of **0.8 seconds** relative to the previous one.
- **Hardware**:
    - 4x LEDs (Red/Green)
    - 4x Resistors (1 kΩ, 250 mW)

## Task 2: Advanced Control
Extend the functionality of Task 1 by adding 3 buttons to the Arduino.

### Functionality:
1.  **Button 1 (Speed Control)**:
    - On every press, increase the "speed" of the running light effect.
2.  **Button 2 (Direction Control)**:
    - On every press, invert the direction of the running light sequence (e.g., from left-to-right to right-to-left).
3.  **Button 3 (Brightness Control)**:
    - On every press, change the brightness intensity of the LEDs.
    - Cycle through 4 states: **50% -> 60% -> 75% -> 100%**.
