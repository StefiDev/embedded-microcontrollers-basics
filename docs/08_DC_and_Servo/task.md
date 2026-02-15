# DC and Servo Motor Control System

## Objective
Build and program a system of two interacting boards for motor control, establishing a simple communication protocol.

**Note**: This project acts as the introduction to the **Second Term**.

## System Roles

### 1. Controller (Arduino 1)
- **Inputs**:
    - **Potentiometer**: Sets the target angle for the Servo motor (0-180 degrees).
    - **Button**: Cycles the state of the DC motor.
- **Functionality**:
    - Reads user inputs.
    - Sends commands to the Executor via Serial port.
    - **DC Motor States**: Forward -> Stop -> Backward -> Stop (Cyclical).

### 2. Executor (Arduino 2)
- **Outputs**:
    - **Servo Motor**
    - **DC Motor**
- **Functionality**:
    - Receives and interprets commands from the Controller.
    - Rotates the Servo to the requested angle.
    - Changes the DC motor's direction or stops it based on the received command.
