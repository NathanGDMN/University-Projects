#Returns Array of 5 second dataframe objects
import math
from ExtractData import *

debug = 0

# if debug == 1:
#     dataset = pd.read_csv('walking.csv')

def split5Sec(dataframe):
    numberOfRows = dataframe.shape[0]
    maxTime = dataframe.loc[numberOfRows-1].at["Time (s)"]
    numberOfSections = maxTime/5
    lengthOf5Sec = round(numberOfRows / numberOfSections)

    if debug == 1:
        print("Number of rows in dataframe:", numberOfRows)
        print("Maximum time from dataframe:", maxTime)
        print("To split dataframe into 5 second segments:")
        print("\tThe dataframe was split into", numberOfSections, "sections")
        print("\tEach section of the dataframe has", lengthOf5Sec, "rows")

    #Create Array of 5 Second Dataframe Objects
    dataArray = []
    dataArray.append(dataframe.iloc[0:lengthOf5Sec, :])
    for i in range(math.floor(numberOfSections)):
        dataArray.append(dataframe.iloc[lengthOf5Sec*i:lengthOf5Sec*(i+1), :])
        if (debug == 1):
            print(dataArray[i])

    return dataArray

# if debug == 1:
#     print(split5Sec(dataset))