import h5py
import matplotlib.pyplot as plt
from sklearn.datasets import make_classification
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split, learning_curve
from sklearn.metrics import accuracy_score, f1_score
from sklearn.pipeline import make_pipeline
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import roc_auc_score
from sklearn.metrics import recall_score
from sklearn.metrics import confusion_matrix, ConfusionMatrixDisplay
from processing import performProcessing
from tkinter import *
import tkinter as tk
import pandas as pd
from split import split5Sec
from ExtractData import getFeatures, getFeat
import matplotlib
from matplotlib.backends.backend_tkagg import (FigureCanvasTkAgg, NavigationToolbar2Tk)
from tkinter import filedialog
import csv
matplotlib.use("TkAgg")


# Import Dataset
# read in Tony's data
TonyWalking = pd.read_csv('tony_walking.csv')
TonyJumping = pd.read_csv('tony_jumping.csv')
# read in Annie's data
AnnieWalking = pd.read_csv('annie_walking.csv')
AnnieJumping = pd.read_csv('annie_jumping.csv')
# read in Nathan's data
NathanWalking = pd.read_csv('nathan_walking.csv')
NathanJumping = pd.read_csv('nathan_jumping.csv')

# Pre-Processing
# Note processing is handled by function in processing.py
processedTW = performProcessing(TonyWalking, 0)
processedTJ = performProcessing(TonyJumping, 1)
processedAW = performProcessing(AnnieWalking, 0)
processedAJ = performProcessing(AnnieJumping, 1)
processedNW = performProcessing(NathanWalking, 0)
processedNJ = performProcessing(NathanJumping, 1)

# Split into 5 second segments:
dataArrayTW = split5Sec(processedTW)
numberOfSectionsTW = len(dataArrayTW)

dataArrayTJ = split5Sec(processedTJ)
numberOfSectionsTJ = len(dataArrayTJ)

dataArrayAW = split5Sec(processedAW)
numberOfSectionsAW = len(dataArrayAW)

dataArrayAJ = split5Sec(processedAJ)
numberOfSectionsAJ = len(dataArrayAJ)

dataArrayNW = split5Sec(processedNW)
numberOfSectionsNW = len(dataArrayNW)

dataArrayNJ = split5Sec(processedNJ)
numberOfSectionsNJ = len(dataArrayNJ)

# Extract features from each 5 second segment of the array
# Create dataframe to hold feature elements
features = pd.DataFrame(columns=[
    "varianceX", "varianceY", "varianceZ", "varianceAbs",
    "maxX", "maxY", "maxZ", "maxAbs",
    "meanAbs",
    "stdAbs",
    "type"  # Type will be the column indicating whether the dataset is for jumping or walking
])

# Get feature data from every 5-second window and combine it into a single dataframe
for i in range(numberOfSectionsTW):
    features = pd.concat([features, getFeatures(dataArrayTW[i], 0)])

for j in range(numberOfSectionsTJ):
    features = pd.concat([features, getFeatures(dataArrayTJ[j], 1)])

for k in range(numberOfSectionsAW):
    features = pd.concat([features, getFeatures(dataArrayAW[k], 0)])

for l in range(numberOfSectionsAJ):
    features = pd.concat([features, getFeatures(dataArrayAJ[l], 1)])

for m in range(numberOfSectionsNW):
    features = pd.concat([features, getFeatures(dataArrayNW[m], 0)])

for n in range(numberOfSectionsNJ):
    features = pd.concat([features, getFeatures(dataArrayNJ[n], 1)])

# Train logistic regression model on data
data = features.iloc[:, :-1]  # Data = features - type indicator
labels = features.iloc[:, -1]  # Last column is label for whether its running or walking


# Split dataset into training and test
# assigned 10% of data to test set
X_train, X_test, Y_train, Y_test = \
    train_test_split(data, labels, test_size=0.1, shuffle=True, random_state=0)

# Train test model
l_reg = LogisticRegression(max_iter=10000)
clf = make_pipeline(StandardScaler(), l_reg)
clf.fit(X_train, Y_train)

#--Data Storing
# write into the HDF5 file
with h5py.File('390data.h', 'w') as hdf:
    # Tony's dataset
    Tony = hdf.create_group('/Tony')
    Tony.create_dataset('tony_walking_data', data=TonyWalking)
    Tony.create_dataset('tony_jumping_data', data=TonyJumping)

    # Annie's dataset
    Annie = hdf.create_group('/Annie')
    Annie.create_dataset('annie_walking_data', data=AnnieWalking)
    Annie.create_dataset('annie_jumping_data', data=AnnieJumping)

    # Nathan's dataset
    Nathan = hdf.create_group('/Nathan')
    Nathan.create_dataset('nathan_walking_data', data=NathanWalking)
    Nathan.create_dataset('nathan_jumping_data', data=NathanJumping)

    # train/ test datasets
    Train = hdf.create_group('dataset/Train')
    Test = hdf.create_group('dataset/Test')
    Train.create_dataset('x_train_data', data=X_train)
    Train.create_dataset('y_train_data', data=Y_train)
    Test.create_dataset('x_test_data', data=X_test)
    Test.create_dataset('y_test_data', data=Y_test)

#--Use Classifier
# Get model's prediction
Y_pred = clf.predict(X_test)
Y_clf_prob = clf.predict_proba(X_test)

# Check accuracy vs test data
acc = accuracy_score(Y_test, Y_pred)
print('\nAccuracy when using whole training set is: ', acc)
# classification recall
recall = recall_score(Y_test, Y_pred)
print('recall is: ', recall)

# plotting the confusion matrix
cm = confusion_matrix(Y_test, Y_pred)
cm_display = ConfusionMatrixDisplay(cm).plot()
plt.show()

# Check F1 Score
f1 = f1_score(Y_test, Y_pred)
print('F1 score is: ', f1)
# Calculate AUC
auc = roc_auc_score(Y_test, Y_clf_prob[:, 1])
print('The AUC is: ', auc, '\n')
# Calculate Learning Curve
data, labels = make_classification(n_samples=100, n_features=10, random_state=42)
train_size_abs, train_scores, test_scores = learning_curve(
    clf, data, labels, train_sizes=[0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9]
)


# Function for the app to use the trained model to distinguish between walking and jumping
def process():
    # open file in CSV format
    file_path = filedialog.askopenfilename()
    with open(file_path, 'r') as csv_file:
        input_data = pd.read_csv(file_path)

    filePathLabel = Label(root, text='File path:', font=('Times', 20))
    csvLabel = Label(root, text=file_path, font=('Times', 15))
    filePathLabel.pack()
    csvLabel.pack()

    # divide each file into 5-second windows
    split_data = split5Sec(input_data)
    numberOfSec = len(split_data)
    feat = pd.DataFrame(columns=[
        "varianceX", "varianceY", "varianceZ", "varianceAbs",
        "maxX", "maxY", "maxZ", "maxAbs",
        "meanAbs",
        "stdAbs"  # Type will be the column indicating whether the dataset is for jumping or walking
    ])
    numSec = []
    x = 0
    # for each window get the features
    for i in range(numberOfSec):
        feat = pd.concat([feat, getFeat(split_data[i])])
        numSec.append(x)
        x = x + 1

    # for each window test determine if it is walking or jumping
    prediction = clf.predict(feat)

    # make a dataframe with 2 columns
    output_data = pd.DataFrame(columns=["windowNumber", "Prediction", "Walk or Jump"])
    output_data["windowNumber"] = numSec
    output_data["Prediction"] = prediction

    for a in range(numberOfSec):
        if output_data.iloc[a, 1] == 1:
            output_data.loc[[a, 2], 'Walk or Jump'] = 'Jumping'
        else:
            output_data.loc[[a, 2], 'Walk or Jump'] = 'Walking'

    # plot output
    fig, ax = plt.subplots(2)
    ax[0].set_title('Input Data')
    ax[0].set_xlabel('Times (s)')
    ax[0].set_ylabel('Absolute Acceleration')
    ax[0].plot(input_data.iloc[:, 0], input_data.iloc[:, 4])
    ax[1].set_title('walking or jumping')
    ax[1].set_xlabel('Window Number')
    ax[1].set_ylabel('Jumping or walking\n [note: 1=Jumping, 0=Walking')
    ax[1].plot(output_data.iloc[:, 0], output_data.iloc[:, 1])
    fig.tight_layout()
    # plt.show()

    # creating the Tkinter canvas
    canvas = FigureCanvasTkAgg(fig, master=root)
    canvas.draw()
    canvas.get_tk_widget().pack(anchor=CENTER)
    toolbar = NavigationToolbar2Tk(canvas, root)
    toolbar.update()

    # placing the toolbar on the Tkinter window
    canvas.get_tk_widget().pack()

    # write output data to a csv file in the current directory
    with open("output.csv", 'w') as file:
        writer = csv.writer(file)
        header = ['Window Number', 'Prediction', 'Walking or Jumping']
        writer.writerow(header)

        for i in range(numberOfSec):
            writer.writerow(output_data.iloc[i, :])

    Label2 = Label(root, text='Saved output file to current directory', font=('Times', 15))
    Label2.pack()


def Exit():
    global root
    root.quit()


# main function for Tkinter app for model deployment
root = tk.Tk()
root.title("Walk vs Jumping")
# root.config(background='black')
root.attributes('-fullscreen', True)

label1 = Label(root, text='Walking vs Jumping Classifier', font=('Times', 34))
label1.pack()

label2 = Label(root, text='Group 09', font=('Times', 15))
label2.pack()

Button1 = tk.Button(root, text='Select input csv', command=process, font=('Times', 24), bg='blue', fg='white')
Button1.pack()

Button2 = tk.Button(root, text='Exit', command=Exit, font=('Times', 24), bg='blue', fg='white')
Button2.pack(side=BOTTOM)

root.mainloop()