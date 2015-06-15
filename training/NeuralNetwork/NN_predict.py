__author__ = 'Yue Dayu'

from NN_training import *
from pybrain.tools.customxml import NetworkReader

def neural_predict(filename, train_file):
    testtag, testdata = readfile(filename)
    net = NetworkReader.readFrom(train_file)
    i = 0
    num = 0
    for k in testdata:
        res = net.activate(k)
        if labals[max_index(res)] == testtag[i]:
            num += 1
        i += 1
    print num

if __name__ == '__main__':
    neural_predict(sys.argv[1], sys.argv[2])