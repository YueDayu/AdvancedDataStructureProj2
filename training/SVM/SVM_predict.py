__author__ = 'Yue Dayu'

from SVM_training import *

def svm_predict(filename, train_file, output):
    type_list, data = readfile(filename)
    clf = joblib.load(train_file)
    result = clf.predict(data)
    num = 0
    i = 0
    for x in type_list:
        if x == result[i]:
            num += 1
        i += 1
    print num
    print num / (float)(len(result))

if __name__ == '__main__':
    svm_predict(sys.argv[1], sys.argv[2], sys.argv[3])