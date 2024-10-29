#Question 5
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

dataset = pd.read_csv('noisy-sine.csv')

#Apply moving average
window_size = 5
dataset5 = dataset.rolling(window_size).mean()
window_size = 31
dataset31 = dataset.rolling(window_size).mean()
window_size = 51
dataset51 = dataset.rolling(window_size).mean()

#Plot all of them
#print(dataset.shape[0])
x_input = np.arange(dataset.shape[0])
fig, ax = plt.subplots(figsize=(10,10))
ax.plot(x_input, dataset)
ax.plot(x_input, dataset5,linewidth=5)
ax.plot(x_input, dataset31,linewidth=5)
ax.plot(x_input, dataset51,linewidth=5)

ax.legend(['Noisy Data', 'SMA 5', 'SMA 31', 'SMA 51'])
ax.set_xlabel('x')
ax.set_ylabel('y')
plt.show()