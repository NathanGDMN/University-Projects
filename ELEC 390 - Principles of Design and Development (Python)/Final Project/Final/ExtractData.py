import pandas as pd


def getFeatures(dataframe, type):
    # gathers aggregate features for whole columns of dataset
    # So there will be one feature entry(row) for each 5 second segment
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
