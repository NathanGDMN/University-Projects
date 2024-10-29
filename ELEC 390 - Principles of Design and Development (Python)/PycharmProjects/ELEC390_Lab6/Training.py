import pandas as pd
import matplotlib.pyplot as plt
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, f1_score
from sklearn.pipeline import make_pipeline
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import confusion_matrix, ConfusionMatrixDisplay
from sklearn.metrics import roc_curve, RocCurveDisplay, roc_auc_score

#--Read pandas dataframe:
dataset = pd.read_csv('winequalityN-lab6.csv')

#--Change quality column:
dataset['quality'] = (dataset['quality']>=6).astype(int)

#--Drop first column:
dataset = dataset.iloc[:, 1:]

#--Assign last column to a variable:
data = dataset.iloc[:, :-1]  #Data = Dataset - lastColumn
labels = dataset.iloc[:, 11]
#print(labels)

#--Split dataset into training and test
X_train, X_test, Y_train, Y_test = \
    train_test_split(data, labels, test_size=0.2, shuffle=True, random_state=0)
    #assigned 20% of data to test set

#--Train test model
l_reg =LogisticRegression(max_iter=10000)
clf = make_pipeline(StandardScaler(), l_reg)

clf.fit(X_train, Y_train)

#Get model's prediction
Y_pred = clf.predict(X_test)

#Check accuracy vs test data
acc = accuracy_score(Y_test, Y_pred)
print('accuracy is: ', acc)

#Plot confusion matrix
cm = confusion_matrix(Y_test, Y_pred)
cm_display = ConfusionMatrixDisplay(cm).plot()
plt.show()

#Check F1 Score
f1 = f1_score(Y_test, Y_pred)
print('F1 score is: ', f1)

#Plot the ROC curve
Y_clf_prob = clf.predict_proba(X_test)
fpr, tpr, _ = roc_curve(Y_test, Y_clf_prob[:, 1], pos_label=clf.classes_[1])
roc_display = RocCurveDisplay(fpr=fpr, tpr=tpr).plot()
plt.show()

#Calculate AUC
auc = roc_auc_score(Y_test, Y_clf_prob[:, 1])
print('the AUC is: ', auc)

