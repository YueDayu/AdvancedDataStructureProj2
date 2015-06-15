__author__ = 'Yue Dayu'

from pybrain.tools.shortcuts import buildNetwork
from pybrain.datasets import SupervisedDataSet
from pybrain.tools.customxml import NetworkWriter
from pybrain.supervised.trainers import BackpropTrainer
import numpy as np
import sys

# from pybrain.datasets import SupervisedDataSet
#
# dataModel = [
#     [(0,0), (0,0)],
#     [(0,1), (0,1)],
#     [(1,0), (1,0)],
#     [(1,1), (1,1)],
# ]
#
# ds = SupervisedDataSet(2, 2)
# for input, target in dataModel:
#     ds.addSample(input, target)
#
# # create a large random data set
# import random
# random.seed()
# trainingSet = SupervisedDataSet(2, 2);
# for ri in range(0,1000):
#     input,target = dataModel[random.getrandbits(2)];
#     trainingSet.addSample(input, target)
#
# from pybrain.tools.shortcuts import buildNetwork
# net = buildNetwork(2, 2, 2, bias=True)
#
# from pybrain.supervised.trainers import BackpropTrainer
# trainer = BackpropTrainer(net, ds, learningrate = 0.001, momentum = 0.99)
# trainer.trainUntilConvergence(verbose=True,
#                               trainingData=trainingSet,
#                               validationData=ds,
#                               maxEpochs=10)
#
# print '0,0->', net.activate([0,0])
# print '0,1->', net.activate([0,1])
# print '1,0->', net.activate([1,0])
# print '1,1->', net.activate([1,1])

labals = ['n03877845', 'n04515003', 'n01923025', 'n03767203', 'n11669921', 'n07897438', 'n10247358', 'n01613177', 'n04583620', 'n02278980']

def readfile(filename):
    list_file = open(filename, 'r')
    _ = list_file.readline()
    lines = list_file.readlines()
    type_list = []
    feature_list = []
    for line in lines:
        current_line = line.split(' ')
        type_list.append((current_line[0]).split('_')[0])
        temp_list = map(float, current_line[1:])
        feature_list.append(temp_list)
    result = np.array(feature_list)
    return type_list, result

def trans(name):
    res = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    res[labals.index(name)] = 1
    return res

def max_index(list):
    max = list[0]
    index = 0
    i = 0
    for x in list:
        if x > max:
            max = x
            index = i
        i += 1
    return index

def neural_train(filename, testfile, output):
    tag, data = readfile(filename)
    testtag, testdata = readfile(testfile)
    net = buildNetwork(len(data[0]), 80, 10)
    ds = SupervisedDataSet(len(data[0]), 10)
    for x in range(0, len(data)):
        ds.addSample(data[x], trans(tag[x]))
    testds = SupervisedDataSet(len(data[0]), 10)
    for x in range(0, len(testdata)):
        testds.addSample(testdata[x], trans(testtag[x]))
    trainer = BackpropTrainer(net, ds, learningrate = 0.001, momentum = 0.99)
    print "training..."
    trainer.trainUntilConvergence(verbose=True,
                              trainingData=ds,
                              validationData=testds,
                              maxEpochs=500)
    print "done"
    NetworkWriter.writeToFile(net, output)


if __name__ == '__main__':
    neural_train(sys.argv[1], sys.argv[2], sys.argv[3])

