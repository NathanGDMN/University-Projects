import pandas as pd

# dataset = pd.read_csv('walking.csv')
# dataset = dataset.iloc[:, 4]

def extractFeatures(dataframe): #Extracts features using method from lab5, where values are calculated for each row
    features = pd.DataFrame(columns=["mean", "median", "max", "min", "std", "variance", #"pct_change",
                                     "skew", "kurt", "sum", "range"])
    window_size = 31
    features["mean"] = dataframe.rolling(window_size).mean().dropna()
    features["median"] = dataframe.rolling(window_size).median().dropna()
    features["max"] = dataframe.rolling(window_size).max().dropna()
    features["min"] = dataframe.rolling(window_size).min().dropna()
    features["std"] = dataframe.rolling(window_size).std().dropna()
    features["variance"] = dataframe.rolling(window_size).var().dropna()
    #features["pct_change"] = dataframe.rolling(window_size).pct_change().dropna()
    features["skew"] = dataframe.rolling(window_size).skew().dropna()
    features["kurt"] = dataframe.rolling(window_size).kurt().dropna()
    features["sum"] = dataframe.rolling(window_size).sum().dropna()
    features["range"] = dataframe.rolling(window_size).max().dropna() - dataframe.rolling(window_size).min().dropna()
    # Range = max - min

    return features

def getFeatures(dataframe, type):
    #Instead of calulating a feature value for each row, simply gathers aggregate features for whole columns of dataset
    #So there will be one feature entry(row) for each 5 second segment instead of a series of them
    features = pd.DataFrame(columns=[
        "varianceX",
        "varianceY",
        "varianceZ",
        "varianceAbs",
        "maxX",
        "maxY",
        "maxZ",
        "maxAbs",
        "meanAbs",
        "stdAbs",
        "type"
    ])

    varX = dataframe["Acceleration x (m/s^2)"].var(axis=0)
    varY = dataframe["Acceleration y (m/s^2)"].var(axis=0)
    varZ = dataframe["Acceleration z (m/s^2)"].var(axis=0)
    varAbs = dataframe["Absolute acceleration (m/s^2)"].var(axis=0)
    maxX = dataframe["Acceleration x (m/s^2)"].max(axis=0)
    maxY = dataframe["Acceleration y (m/s^2)"].max(axis=0)
    maxZ = dataframe["Acceleration z (m/s^2)"].max(axis=0)
    maxAbs = dataframe["Absolute acceleration (m/s^2)"].max(axis=0)
    meanAbs = dataframe["Absolute acceleration (m/s^2)"].mean(axis=0)
    stdAbs = dataframe["Acceleration x (m/s^2)"].std(axis=0)

    featureRow = [varX, varY, varZ, varAbs, maxX, maxY, maxZ, maxAbs, meanAbs, stdAbs, type]
    features.loc[len(features)] = featureRow

    return features

def getFeat(dataframe):
    # get features from the dataframe (similar to the function above but without a column for type)
    features = pd.DataFrame(columns=[
        "varianceX",
        "varianceY",
        "varianceZ",
        "varianceAbs",
        "maxX",
        "maxY",
        "maxZ",
        "maxAbs",
        "meanAbs",
        "stdAbs",
    ])

    varX = dataframe["Acceleration x (m/s^2)"].var(axis=0)
    varY = dataframe["Acceleration y (m/s^2)"].var(axis=0)
    varZ = dataframe["Acceleration z (m/s^2)"].var(axis=0)
    varAbs = dataframe["Absolute acceleration (m/s^2)"].var(axis=0)
    maxX = dataframe["Acceleration x (m/s^2)"].max(axis=0)
    maxY = dataframe["Acceleration y (m/s^2)"].max(axis=0)
    maxZ = dataframe["Acceleration z (m/s^2)"].max(axis=0)
    maxAbs = dataframe["Absolute acceleration (m/s^2)"].max(axis=0)
    meanAbs = dataframe["Absolute acceleration (m/s^2)"].mean(axis=0)
    stdAbs = dataframe["Acceleration x (m/s^2)"].std(axis=0)

    featureRow = [varX, varY, varZ, varAbs, maxX, maxY, maxZ, maxAbs, meanAbs, stdAbs]
    features.loc[len(features)] = featureRow

    return features

# print (extractFeatures(dataset))
# print (getFeatures(dataset, 0))



