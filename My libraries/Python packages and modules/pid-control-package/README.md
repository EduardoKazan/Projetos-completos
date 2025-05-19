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

## Python Package Installation

You can install the `pid_control` package via pip:

```bash
pip install .
```

## Usage

Here is a basic example of how to use the `pid_control` package and the `PIDController` class:

```python
from pid_control import PIDController
import time

# Initialize PID controller with parameters kP, kI, kD
pid = PIDController(kP=1.0, kI=0.1, kD=0.05)

# Set desired set point
pid.set_set_point(25.0)  # Target temperature

while True:
    # Simulate reading a new sample (e.g., temperature sensor)
    current_temperature = 20.0  # Replace with actual sensor reading
    pid.add_new_sample(current_temperature)

    # Calculate control output
    control = pid.process()

    print(f"Control output: {control}")

    time.sleep(1)  # Wait before next sample
```

## License

This project is provided as-is without warranty.
