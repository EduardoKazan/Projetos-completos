# PID Temperature Control Project

This project implements a PID (Proportional-Integral-Derivative) controller for temperature regulation using an ESP32 microcontroller. The control algorithm reads temperature data from an analog sensor connected to an ADC pin and adjusts a PWM output to control a device accordingly.

## Features

- PID control algorithm implemented in Python
- Reads temperature from an ADC pin on the ESP32
- Outputs control signal via PWM pin
- Configurable PID parameters (kP, kI, kD)
- Simple loop with periodic sensor reading and control update

## Hardware

- ESP32 microcontroller
- Temperature sensor connected to ADC pin 34
- Controlled device connected to PWM pin 25

## Usage

Run the script on the ESP32 to continuously monitor temperature and adjust the control output to maintain the desired set point.

## License

This project is provided as-is without warranty.
