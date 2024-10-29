import numpy as np
import matplotlib.pyplot as plt


# Pre-Processing
def performProcessing(dataframe, type):
    # plot the original dataframe
    fig, ax = plt.subplots(3)
    ax[0].set_title('Acceleration x')
    ax[0].set_xlabel('Time (s)')
    ax[0].set_ylabel('Acceleration x (m/s^2)')
    ax[0].plot(dataframe.iloc[1:, 0], dataframe.iloc[1:, 1], color='blue', label="pre filter")
    ax[1].set_title('Acceleration y')
    ax[1].set_xlabel('Time (s)')
    ax[1].set_ylabel('Acceleration y (m/s^2)')
    ax[1].plot(dataframe.iloc[1:, 0], dataframe.iloc[1:, 2], color='blue', label="pre filter")
    ax[2].set_title('Acceleration z')
    ax[2].set_xlabel('Time (s)')
    ax[2].set_ylabel('Acceleration z (m/s^2)')
    ax[2].plot(dataframe.iloc[1:, 0], dataframe.iloc[1:, 3], color='blue', label="pre filter")

    # Create copy (to not accidentally alter first one)
    dataset = dataframe

    # Decided to remove outliers before applying rolling average filter (as outliers are more pronounced)
    meanx = dataset["Acceleration x (m/s^2)"].mean(axis=0)
    meany = dataset["Acceleration y (m/s^2)"].mean(axis=0)
    meanz = dataset["Acceleration z (m/s^2)"].mean(axis=0)
    meanabs = dataset["Absolute acceleration (m/s^2)"].mean(axis=0)

    # Adjusting outlier trim parameters depending on type
    if type == 1:
        xDiff = 30
        yDiff = 30
        zDiff = 30
        AbsDiff = 30
    else:
        xDiff = 12
        yDiff = 12
        AbsDiff = 12
        zDiff = 20

    datasetx = dataset["Acceleration x (m/s^2)"]
    datasetx.mask(abs(datasetx - meanx) > xDiff, other=np.NaN, inplace=True)  # Can adjust outlier condition here
    datasetx.interpolate(method='linear', inplace=True)

    datasety = dataset["Acceleration y (m/s^2)"]
    datasety.mask(abs(datasety - meany) > yDiff, other=np.NaN, inplace=True)  # Can adjust outlier condition here
    datasety.interpolate(method='linear', inplace=True)

    datasetz = dataset["Acceleration z (m/s^2)"]
    datasetz.mask(abs(datasetz - meanz) > zDiff, other=np.NaN, inplace=True)  # Can adjust outlier condition here
    datasetz.interpolate(method='linear', inplace=True)

    datasetabs = dataset["Absolute acceleration (m/s^2)"]
    datasetabs.mask(abs(datasetabs - meanabs) > AbsDiff, other=np.NaN,
                    inplace=True)  # Can adjust outlier condition here
    datasetabs.interpolate(method='linear', inplace=True)

    # Applied moving average filter:
    window_size = 25
    datasetx25 = datasetx.rolling(window_size).mean()
    datasety25 = datasety.rolling(window_size).mean()
    datasetz25 = datasetz.rolling(window_size).mean()
    datasetabs25 = datasetabs.rolling(window_size).mean()

    # Combine back into one dataframe:
    dataset["Acceleration x (m/s^2)"] = datasetx25
    dataset["Acceleration y (m/s^2)"] = datasety25
    dataset["Acceleration z (m/s^2)"] = datasetz25
    dataset["Absolute acceleration (m/s^2)"] = datasetabs25

    ax[0].plot(dataset.iloc[1:, 0], dataset.iloc[1:, 1], color='green', label="post filter")
    ax[1].plot(dataframe.iloc[1:, 0], dataframe.iloc[1:, 2], color='green', label="post filter")
    ax[2].plot(dataframe.iloc[1:, 0], dataframe.iloc[1:, 3], color='green', label="post filter")

    fig.tight_layout()
    # plt.show()

    return dataset
