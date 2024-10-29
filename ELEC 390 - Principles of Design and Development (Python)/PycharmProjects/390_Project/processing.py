import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

debug = 0 #For viewing/debugging function

# viewResults = 1 #For viewing before and after
#
# dataset = pd.read_csv('walking.csv')
#
# if viewResults == 1:
#     #Show combined plot:
#     fig, ax = plt.subplots(figsize=(10, 10))
#     # Can change text within [...] to adjust which original column you want to see:
#     dataset.plot(ax=ax, linewidth=1, legend=None)
#     plt.show()

#--Pre-processing:
def performProcessing(dataframe, type):
    if debug == 1:
        fig, ax = plt.subplots(figsize=(10, 10))
        # Can change text within [...] to adjust which original column you want to see:
        dataframe["Acceleration x (m/s^2)"].plot(ax=ax, linewidth=1, legend=None)
        plt.show()

    #Create copy (to not accidentally alter first one)
    dataset = dataframe

    #Decided to remove outliers before applying rolling average filter (as outliers are more pronounced)
    meanx = dataset["Acceleration x (m/s^2)"].mean(axis=0)
    meany = dataset["Acceleration y (m/s^2)"].mean(axis=0)
    meanz = dataset["Acceleration z (m/s^2)"].mean(axis=0)
    meanabs = dataset["Absolute acceleration (m/s^2)"].mean(axis=0)
    if debug == 1:
        print ("Mean of each acceleration axis:\n")
        print("\tx:",meanx)
        print("\ty:",meany)
        print("\tz:", meanz)
        print("\tabs:", meanabs)

    #Adjusting outlier trim parameters depending on type
    if type == 0:
        xDiff = 12
        yDiff = 12
        AbsDiff = 12
        zDiff = 20
    else:
        xDiff = 30
        yDiff = 30
        zDiff = 30
        AbsDiff = 30

    datasetx = dataset["Acceleration x (m/s^2)"]
    datasetx.mask(abs(datasetx-meanx) > xDiff, other=np.NaN, inplace=True) #Can adjust outlier condition here
    datasetx.interpolate(method='linear', inplace=True)

    datasety = dataset["Acceleration y (m/s^2)"]
    datasety.mask(abs(datasety-meany) > yDiff, other=np.NaN, inplace=True) #Can adjust outlier condition here
    datasety.interpolate(method='linear', inplace=True)

    datasetz = dataset["Acceleration z (m/s^2)"]
    datasetz.mask(abs(datasetz-meanz) > zDiff, other=np.NaN, inplace=True) #Can adjust outlier condition here
    datasetz.interpolate(method='linear', inplace=True)

    datasetabs = dataset["Absolute acceleration (m/s^2)"]
    datasetabs.mask(abs(datasetabs-meanabs) > AbsDiff, other=np.NaN, inplace=True) #Can adjust outlier condition here
    datasetabs.interpolate(method='linear', inplace=True)

    if debug == 1:
        fig, ax = plt.subplots(figsize=(10,10))
        #Can change dataframe variable to adjust which outlier removed column you want to see:
        datasetx.plot(ax=ax, linewidth = 1, legend=None)
        plt.show()

    #Applied moving average filter:
    window_size = 25
    datasetx25 = datasetx.rolling(window_size).mean()
    datasety25 = datasety.rolling(window_size).mean()
    datasetz25 = datasetz.rolling(window_size).mean()
    datasetabs25 = datasetabs.rolling(window_size).mean()

    if debug == 1:
        fig, ax = plt.subplots(figsize=(10,10))
        #Can change dataframe variable to adjust which outlier removed and average filter applied column you want to see:
        datasetx25.plot(ax=ax, linewidth = 1, legend=None)
        plt.show()

    #Combine back into one dataframe:
    dataset["Acceleration x (m/s^2)"] = datasetx25
    dataset["Acceleration y (m/s^2)"] = datasety25
    dataset["Acceleration z (m/s^2)"] = datasetz25
    dataset["Absolute acceleration (m/s^2)"] = datasetabs25

    return dataset

# dataNew = performProcessing(dataset)
#
# if viewResults == 1:
#     #Show combined plot
#     fig, ax = plt.subplots(figsize=(10, 10))
#     dataNew.plot(ax=ax, linewidth=1, legend=None)
#     plt.show()