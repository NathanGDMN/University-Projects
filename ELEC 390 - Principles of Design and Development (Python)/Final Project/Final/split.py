# Returns Array of 5 second dataframe objects
import math


def split5Sec(dataframe):
    numberOfRows = dataframe.shape[0]
    maxTime = dataframe.loc[numberOfRows-1].at["Time (s)"]
    numberOfSections = maxTime/5
    lengthOf5Sec = round(numberOfRows / numberOfSections)

    # Create Array of 5 Second Dataframe Objects
    dataArray = [dataframe.iloc[0:lengthOf5Sec, :]]
    for i in range(math.floor(numberOfSections)):
        dataArray.append(dataframe.iloc[lengthOf5Sec*i:lengthOf5Sec*(i+1), :])

    return dataArray
