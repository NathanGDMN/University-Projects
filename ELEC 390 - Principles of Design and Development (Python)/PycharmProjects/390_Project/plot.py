import matplotlib.pyplot as plt
import pandas as pd

dataset = pd.read_csv('tony_walking.csv')

#Time
#dataset = dataset.iloc[:, 0];
#Acceleration x
dataset = dataset.iloc[:, 1];
#Acceleration y
#dataset = dataset.iloc[:, 2];
#Aceleration z
#dataset = dataset.iloc[:, 3];
#Absolute Acceleration
#dataset = dataset.iloc[:, 4];

fig, ax = plt.subplots(figsize=(10,10))
dataset.plot(ax=ax, linewidth = 1, legend=None)
plt.show()