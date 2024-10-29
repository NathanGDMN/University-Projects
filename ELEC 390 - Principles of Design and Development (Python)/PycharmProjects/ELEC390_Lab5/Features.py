#-----Question 6-----
import matplotlib.pyplot as plt
import pandas as pd

dataset = pd.read_csv('ECG-sample.csv')

#Plot dataset
fig, ax = plt.subplots(figsize=(10,10))
dataset.plot(ax=ax, linewidth = 1, legend=None)
plt.show()

#Extract features
features = pd.DataFrame(columns=["mean", "std", "max", "min"])
window_size = 31
features["mean"] = dataset.rolling(window_size).mean().dropna()
features["std"] = dataset.rolling(window_size).std().dropna()
features["max"] = dataset.rolling(window_size).max().dropna()
features["min"] = dataset.rolling(window_size).min().dropna()

print(features)

#Plot Features
fig2, ax2 = plt.subplots(figsize=(10,10))
ax2.set_xlabel("Number of the window")
ax2.set_ylabel("Value of the std")
features["std"].plot(ax=ax2, linewidth=1, legend=None)
plt.show()


