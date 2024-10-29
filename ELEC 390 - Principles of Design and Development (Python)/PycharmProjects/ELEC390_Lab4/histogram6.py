# Question 6
import matplotlib.pyplot as plt
import pandas as pd

dataset = pd.read_csv('heart.csv')
data = dataset.iloc[:, :-1]
labels = dataset.iloc[:, -1]
fig, ax = plt.subplots(ncols=13, nrows=13, figsize=(30,30))

pd.plotting.scatter_matrix(data, ax=ax)

fig.tight_layout()
plt.show()