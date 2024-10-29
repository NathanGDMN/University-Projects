#Question 9
import matplotlib.pyplot as plt
import pandas as pd
from sklearn.decomposition import PCA
from sklearn.manifold import TSNE
from sklearn.preprocessing import StandardScaler

dataset = pd.read_csv('winequalityN.csv')

dataset = dataset.iloc[:, 1:]

dataset['quality'] = (dataset['quality']>=8).astype(int)

X = dataset.iloc[:, :-1]
Y = dataset.iloc[:, -1]

stdScalar = StandardScaler()
X = stdScalar.fit_transform(X)

#PCA
pca = PCA(n_components = 9)
PCA_X = pca.fit_transform(X)

fig, ax = plt.subplots(figsize = (10,20))
legend = ['low-quality','high-quality']

ax.scatter(PCA_X[Y==0, 7], PCA_X[Y==0, 8], c = 'pink', s=60) #Low-quality
ax.scatter(PCA_X[Y==1, 7], PCA_X[Y==1, 8], c = 'red', s=60) #High-quality

ax.set_title('PCA of Wine Quality Dataset', fontsize=25)
ax.set_xlabel('Principal Component 8', fontsize = 20)
ax.set_ylabel('Principal Component 9', fontsize = 20)
ax.legend(legend, fontsize = 15)
plt.show()