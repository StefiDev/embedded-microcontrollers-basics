# UART Lab 1: Basic Communication

## Objective
Create a simulation in Tinkercad with two Arduino boards determining a Master-Slave relationship via UART.

## Roles
1.  **Controller (Master)**: Sends commands.
2.  **Executor (Slave)**: Receives commands and executes actions.

## Requirements
- The **Executor** must be in "ECHO" mode.
- **ECHO Mode**: Every message received from the Controller must be sent back as a string, with your **class number** appended to the end.
- Both boards should communicate using the Serial interface (UART).
