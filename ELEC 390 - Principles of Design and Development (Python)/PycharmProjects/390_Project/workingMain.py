import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from ExtractData import extractFeatures, getFeatures
from split import split5Sec
from processing import performProcessing

debug = 1

#--Import Dataset:
dataset = pd.read_csv('walking.csv')
if debug == 1:
    print("First column of dataset:\n",dataset.iloc[1,:],"\n")
    print("Last column of dataset:\n",dataset.iloc[-1, :],"\n")

#--Pre-processing:
#Note processing is handled by function in processing.py
processedTW = performProcessing(TonyWalking)
processedTJ = performProcessing(TonyJumping)
processedAW = performProcessing(AnnieWalking)
processedAJ = performProcessing(AnnieJumping)
processedNW = performProcessing(NathanWalking)
processedNJ = performProcessing(NathanJumping)

processedDataset = performProcessing(dataset)

#--Split into 5 second segments:
print (processedDataset)
dataArray = split5Sec(processedDataset)
if debug == 1:
    print("First element of dataArray:\n", dataArray[0],"\n")
    print("Last element of dataArray:\n", dataArray[-1],"\n")

numberOfSections = len(dataArray)
if debug == 1:
    print(numberOfSections)

#--Extract features from each 5 second segment of the array
#Create dataframe to hold feature elements
features = pd.DataFrame(columns=[
    "varianceX","varianceY","varianceZ","varianceAbs",
    "maxX","maxY","maxZ","maxAbs",
    "meanAbs",
    "stdAbs",
    "type"       #Type will be the column indicating whether the dataset is for jumping or walking
])
if debug == 1:
    print("Dataframe to hold features:\n",features)

#Get feature data from every 5 second window and combine it into a single dataframe
for i in range(numberOfSections):
     features = pd.concat([features,getFeatures(dataArray[i], 0)])
if debug == 1:
    print("Dataframe to hold features filled in:")
    print("First entry of features dataframe:\n", features.iloc[0,:],"\n")
    print("Last entry of features dataframe:\n", features.iloc[-1, :], "\n")
    print(features.iloc[67, :])