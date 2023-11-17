import numpy as np
import matplotlib.pyplot as plt

hall_outputs = [2700, 2580, 2340, 2280, 2460, 5040, 5160]
tachometer_outputs= [2624, 2618, 2349, 2273, 2410, 5003, 5225]

hall_effect_out = np.array(hall_outputs)
tachometer_out = np.array(tachometer_outputs)
expected_rpm = np.linspace(0, 7, 7)

#plt.plot(expected_rpm, hall_effect_out, label = "Hall Effect Sensor output")
#plt.plot(expected_rpm, tachometer_out, label = "Tachometer output")
plt.plot(expected_rpm, tachometer_out, marker='o', linestyle='-', color='b', label='Tachometer Reading')
plt.plot(expected_rpm, hall_effect_out, marker = 'o', linestyle = '-', color = 'r', label = 'STM32 Reading')

plt.xlabel("Expected RPM")
plt.ylabel("RPM Outputs")

plt.show()