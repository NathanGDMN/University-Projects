# Question 4
import matplotlib.pyplot as plt
import pandas as pd

dataset = pd.read_csv('heart.csv')
data = dataset.iloc[:, 0:13]
labels = dataset.iloc[:, -1]
fig, ax = plt.subplots(ncols=4, nrows=4, figsize=(20,10))

data.plot(ax=ax.flatten()[0:13], kind='density', subplots=True, sharex=False)

fig.tight_layout()
plt.show()