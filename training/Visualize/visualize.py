from time import time

import os
import sys
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import offsetbox
from matplotlib.colors import ListedColormap
from sklearn import (manifold, datasets, decomposition, ensemble, lda,
                     random_projection)


def load_feature(filename):
    fin = open(filename)
    _ = fin.readline()
    lines = fin.readlines()
    Xlst = []
    ylst = []
    lasttype = ""
    num = -1
    for line in lines:
        raw = line.split(" ")
        vec = map(float, raw[1:])
        imgtype = raw[0].split("_")[0]
        if (lasttype != imgtype):
            num += 1
            lasttype = imgtype
        Xlst.append(vec)
        ylst.append(num)

    X = np.array(Xlst)
    y = np.array(ylst)
    return X, y


def plot_embedding(X, y, title=None, shownum=False):
#    x_min, x_max = np.min(X, 0), np.max(X, 0)
#    X = (X - x_min) / (x_max - x_min)

    cm = plt.cm.Set1
    plt.figure()
    ax = plt.subplot(111)
    if shownum:
        for i in range(X.shape[0]):
            plt.text(X[i, 0], X[i, 1], str(y[i]),
                     color=plt.cm.Set1(y[i] / 10.),
                     fontdict={'weight': 'bold', 'size': 9})
    else:
        for i in range(0, 5):
            ax.scatter(X[i::5, 0], X[i::5, 1], marker='x', c=y[i::5], cmap=cm, alpha = 0.5)
    plt.xticks([]), plt.yticks([])
    if title is not None:
        plt.title(title)


def visualize(X, y):
    print("Computing LDA projection")
    X2 = X.copy()
    X2.flat[::X.shape[1] + 1] += 0.01  # Make X invertible
    t0 = time()
    X_lda = lda.LDA(n_components=2).fit_transform(X2, y)
    plot_embedding(X_lda, y,
                   "Linear Discriminant projection (time %.2fs)" %
                   (time() - t0))

    plt.show()

if __name__ == '__main__':
    X, y = load_feature(sys.argv[1])
    visualize(X, y)
