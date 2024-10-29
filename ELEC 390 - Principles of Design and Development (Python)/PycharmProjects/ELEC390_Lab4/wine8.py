#Question 8
import matplotlib.pyplot as plt
import pandas as pd
from sklearn.decomposition import PCA
from sklearn.manifold import TSNE
from sklearn.preprocessing import StandardScaler

#--Step 1:
dataset = pd.read_csv('winequalityN.csv')

#--Step 2:
dataset = dataset.iloc[:, 1:]

#--Step 3:
dataset['quality'] = (dataset['quality']>=8).astype(int)

#--Step 4:
X = dataset.iloc[:, :-1]
Y = dataset.iloc[:, -1]

stdScalar = StandardScaler()
X = stdScalar.fit_transform(X)

#PCA
pca = PCA(n_components = 2)
PCA_X = pca.fit_transform(X)

fig, ax = plt.subplots(figsize = (10,20))
legend = ['low-quality','high-quality']

ax.scatter(PCA_X[Y==0, 0], PCA_X[Y==0, 1], c = 'pink', s=60) #Low-quality
ax.scatter(PCA_X[Y==1, 0], PCA_X[Y==1, 1], c = 'red', s=60) #High-quality

ax.set_title('PCA of Wine Quality Dataset', fontsize=25)
ax.set_xlabel('Principal Component 1', fontsize = 20)
ax.set_ylabel('Principal Component 2', fontsize = 20)
ax.legend(legend, fontsize = 15)
plt.show()

#TSNE
tsne = TSNE(n_components = 2, perplexity=30, learning_rate='auto', init='pca')
TSNE_X = tsne.fit_transform(X)

fig, ax = plt.subplots(figsize = (10,20))
#Don't need to define legend again, will use same as PCA

ax.scatter(TSNE_X[Y==0, 0], TSNE_X[Y==0, 1], c = 'pink', s=60) #Low-quality
ax.scatter(TSNE_X[Y==1, 0], TSNE_X[Y==1, 1], c = 'red', s=60) #High-quality

ax.set_title('TSNE of Wine Quality Dataset', fontsize=25)
ax.legend(legend, fontsize = 15)
plt.show()


