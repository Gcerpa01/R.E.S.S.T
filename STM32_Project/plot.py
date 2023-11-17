import numpy as np
import matplotlib.pyplot as plt
import math

hall_outputs = [2700, 2580, 2340, 2280, 2460, 5040, 5160]
tachometer_outputs= [2624, 2618, 2349, 2273, 2410, 5003, 5225]
percent_error = []

for i in range(0, 7):
    error = abs(tachometer_outputs[i] - hall_outputs[i])/ tachometer_outputs[i]
    percent_error.append(error)

hall_effect_out = np.array(hall_outputs)
tachometer_out = np.array(tachometer_outputs)
expected_rpm = np.linspace(0, 7, 7)

print(percent_error)
plt.plot(expected_rpm, tachometer_out, marker='o', linestyle='-', color='b', label='Tachometer Reading')
plt.plot(expected_rpm, hall_effect_out, marker = 'o', linestyle = '-', color = 'r', label = 'STM32 Reading')
plt.plot(expected_rpm, percent_error, marker = 'o', linestyle = '-', color = 'r', label = 'Percent Error')

plt.xlabel("Expected RPM")
plt.ylabel("RPM Outputs")
plt.legend()

plt.show()