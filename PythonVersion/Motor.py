from __future__ import division
import time

import Adafruit_PCA9685


class Motor:
	def __init__(self):
		self.driver = Adafruit_PCA9685.PCA9685();
		self.driver.set_pwm_freq(60);
		self.allStop()

	def spin(self, n, speed):
		self.driver.set_pwm(n, 0, 355)
		
	def stop(self, n):
		self.driver.set_pwm(n, 0, 0)

	def allStop(self):
		for n in range(0, 16):
			self.driver.set_pwm(n, 0, 0)
