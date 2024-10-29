import pandas as pd
import matplotlib.pyplot as plt
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score
from sklearn.pipeline import make_pipeline
from sklearn.linear_model import LogisticRegression
from sklearn.inspection import DecisionBoundaryDisplay
from sklearn.decomposition import PCA

#--Steps 1 to 5 from before:
#Read pandas dataframe:
dataset = pd.read_csv('winequalityN-lab6.csv')

#Change quality column:
dataset['quality'] = (dataset['quality']>=6).astype(int)

#Drop first column:
dataset = dataset.iloc[:, 1:]

#Assign last column to a variable:
data = dataset.iloc[:, :-1]  #Data = Dataset - lastColumn
labels = dataset.iloc[:, 11]
#print(labels)

#Split dataset into training and test
X_train, X_test, Y_train, Y_test = \
    train_test_split(data, labels, test_size=0.2, shuffle=True, random_state=0)
    #assigned 20% of data to test set

#--Initialize classes
scaler = StandardScaler()
l_reg = LogisticRegression(max_iter=10000)
pca = PCA(n_components=2)

#--Make pipeline
pca_pipe = make_pipeline(scaler, pca)

#--Apply pipeline
X_train_pca = pca_pipe.fit_transform(X_train)
X_test_pca = pca_pipe.fit_transform(X_test)

#--Make logistic regression pipeline:
clf = make_pipeline(scaler, l_reg)

#--Train logistic regression pipeline
clf.fit(X_train_pca, Y_train)

#--Obtain predictions for X_test_pca
Y_pred_pca = clf.predict(X_test_pca)

#--Create decision boundary
disp = DecisionBoundaryDisplay.from_estimator(
    clf, X_train_pca, response_method="predict",
    xlabel='X1', ylabel='X2',
    alpha = 0.5
)

#--Visualize sample
pca_component_1 = X_train_pca[:, 0]
pca_component_2 = X_train_pca[:, 1]
disp.ax_.scatter(pca_component_1, pca_component_2, c=Y_train)
plt.show()

#--Get accuracy
acc = accuracy_score(Y_test, Y_pred_pca)
print("accuracy score with PCA is: ", acc)

