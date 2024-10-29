#-----Question 1-----
import pandas as pd
import numpy as np

#--Load dataset and remove first and last columns:
dataset = pd.read_csv('unclean-wine-quality.csv')
dataset = dataset.iloc[:, 1:-1] #Drop first and last columns
#print(dataset)

#--Find NaN values
nanIndices = np.where(dataset.isna())
#print(nanIndices)
nanSum = dataset.isna().sum()
#print(nanSum)

#--Find '-' values
dashIndices = np.where(dataset == '-')
#print(dashIndices)
numberOfDashes = dashIndices[0].size
#print(numberOfDashes)

#--Replace dashes with NaN values
dataset.mask(dataset == '-', other=np.nan, inplace=True)
#print(dataset)

#--Change values in dataset to numerical type
dataset = dataset.astype('float64')

#-----Question 2-----

#--Fill NaN values in dataset
filling_values = {'fixed acidity':0, 'volatile acidity':0, 'citric acid':0, 'residual sugar':0, 'chlorides':1,
                  'free sulfur dioxide':0, 'total sulfur dioxide':0, 'density':0, 'pH':0, 'sulphates':1, 'alcohol':0}
dataset.fillna(value= filling_values, inplace=True)
print(dataset)
print(dataset.isna().sum())

#-----Question 3-----
#dataset.fillna(method='ffill', inplace=True)
#print(dataset.iloc[16,0])
#print(dataset.iloc[17,0])

#-----Question 4-----
#print(dataset.iloc[17,0])
#dataset.interpolate(method='linear', inplace=True)
#print(dataset.iloc[17,0])



