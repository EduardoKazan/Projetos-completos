import time


class PIDController:
    def __init__(self, kP, kI, kD):
        self.kP = kP
        self.kI = kI
        self.kD = kD
        self.error = 0
        self.sample = 0
        self.lastSample = 0
        self.proportional = 0
        self.integral = 0
        self.derivative = 0
        self.pid = 0
        self.setPoint = 0
        self.lastProcess = -1
        self.P = 0
        self.integral = 0
        self.D = 0

    def add_new_sample(self, sample):
        self.sample = sample

    def set_set_point(self, setPoint):
        self.setPoint = setPoint

    def process(self):
        if self.lastProcess == -1:
            self.lastSample = self.sample
            self.lastProcess = time.ticks_ms() if hasattr(
                time, "ticks_ms") else int(time.time() * 1000)

        # PID implementation
        self.error = self.setPoint - self.sample
        current_time = time.ticks_ms() if hasattr(
            time, "ticks_ms") else int(time.time() * 1000)
        deltaTime = (current_time - self.lastProcess) / 1000.0
        self.lastProcess = current_time

        # Check if deltaTime is zero
        if deltaTime <= 0:
            return self.pid  # Return current PID value without calculating

        # Proportional term
        self.P = self.error * self.kP

        # Integral term
        self.integral += (self.error * self.kI) * deltaTime

        # Derivative term
        self.D = (self.lastSample - self.sample) * self.kD / deltaTime
        self.lastSample = self.sample

        # Sum all terms
        self.pid = self.P + self.integral + self.D

        return self.pid
