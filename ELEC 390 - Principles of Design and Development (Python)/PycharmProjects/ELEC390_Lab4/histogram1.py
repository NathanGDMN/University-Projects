# Question 1
import matplotlib.pyplot as plt
import pandas as pd

dataset = pd.read_csv('heart.csv')

data = dataset.iloc[:, 0:13]
labels = dataset.iloc[:, -1]

fig, ax = plt.subplots(ncols=4, nrows=4, figsize=(20,10))

data.hist(ax=ax.flatten()[:13])

fig.tight_layout()
plt.show()