import numpy as np
import matplotlib.pyplot as plt
import math

hall_outputs = [2700, 2580, 2340, 2280, 2460, 5040, 5160]
tachometer_outputs =[2280, 2340, 2460, 2580, 2700, 4040, 5040, 5160]
expected_rpm = [2250, 2339, 2422, 2592, 2682, 5022, 5170]
percent_error2 = [0.3, 0.38, 2.03, 1.87, 2.8, 1.68, 0.73, 1.28]

percent_error = []
for i in range(0, 7):
    error = abs(expected_rpm[i] - tachometer_outputs[i])/ expected_rpm[i]
    error = error * 100
    percent_error.append(error)

hall_effect_out = np.array(hall_outputs)
tachometer_out = np.array(tachometer_outputs)
duty_cycle = np.array([9.438, 9.120, 8.802, 8.7, 8.488, 8.175, 8.062])

#print(percent_error)
plt.figure(1)
plt.plot(tachometer_out, percent_error2 , marker='o', linestyle='-', color='r', label='%Error')
#plt.plot(duty_cycle, hall_effect_out, marker = 'o', linestyle = '-', color = 'r', label = 'STM32 Reading')
#plt.plot(duty_cycle, expected_rpm, marker = 'o', linestyle = '-', color = 'r', label = 'STM32 Reading')
plt.xlabel("Tachometer RPM")
plt.ylabel("%Error: Between Tachometer & STM32 measured RPM")
plt.title("Tachometer RPM vs. %Error: Between Tachometer RPM & STM32 RPM")
plt.grid(True)
plt.legend()

plt.figure(2)
plt.plot(duty_cycle, percent_error, marker='o', linestyle='-', color='y', label='% error')
plt.xlabel("STM32 Duty Cycle Output (%)")
plt.ylabel("%Error: Expected RPM vs. Tachometer RPM")
#plt.title("Actual (STM32) vs. Expected (Tachometer) Percent Error")
plt.title("STM32 Duty Cycle vs. %Error: Expected RPM vs. Tachometer RPM")
plt.grid(True)
plt.legend()

plt.show()