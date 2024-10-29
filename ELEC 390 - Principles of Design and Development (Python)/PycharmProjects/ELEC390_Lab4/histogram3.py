# Question 3
import matplotlib.pyplot as plt
import pandas as pd

dataset = pd.read_csv('heart.csv')
data = dataset.iloc[:, 0:13]
labels = dataset.iloc[:, -1]
fig, ax = plt.subplots(ncols=4, nrows=4, figsize=(20,10))

for i in range(0, 13):
    ax.flatten()[i].hist(data.iloc[:, i])
    ax.flatten()[i].set_title(data.columns[i], fontsize = 15)

fig.tight_layout()
plt.show()