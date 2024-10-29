import numpy
import pandas as pd
from math import floor
import numpy as np
import h5py
import matplotlib.pyplot as plt
#from sklearn.model_selection import train_test_split

def findRowTimeLessThan(dataframe, s):
    #Finds last row index in dataset (csv file) where time < s
    #*Note dataset does not include header row
    length = dataframe.shape[0] #Length of dataset

    for i in range (length):
        if dataframe.iloc[i,0] > s :
            return i
    print("Error: Failed to find row with given time")
    return -1


#-----Read Data-----
NathanWalking = pd.read_csv('Walking.csv')
NathanJumping = pd.read_csv('Nathan-Jumping.csv')

allData = pd.read_csv('all_data.csv')

allDataLength = allData.shape[0] #Number of rows in allData

timeOfNathanJumping = NathanJumping.iloc[-1,0] #timeOfNathanJumping = duration (s) of NathanJumping dataset
timeOfNathanWalking = NathanWalking.iloc[-1,0] #timeOfNathanWalking = duration (s) of NathanWalking dataset

poo = np.array_split(NathanJumping,floor(timeOfNathanJumping/5))

print(poo[0])

np.random.shuffle(poo)

newpoo = pd.concat(pd.read_excel(fl) for fl in path1)
newpoo.to_csv("H:\\test1.csv", index = False)

newPoo = []

for df in poo:
    newPoo.append(df)

newPoo.to_csv('poo.csv', index=False)


