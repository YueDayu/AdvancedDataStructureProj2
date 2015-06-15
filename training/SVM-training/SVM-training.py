__author__ = 'Yue Dayu'

from sklearn import svm
from sklearn.externals import joblib

# X = [[0, 0], [1, 1]]
# y = ['0', '1']
# clf = svm.SVC()
# clf.fit(X, y)
# joblib.dump(clf, 'filename.pkl')
clf = joblib.load('filename.pkl')
print clf
print clf.predict([[2., 2.], [-1, -1]])
