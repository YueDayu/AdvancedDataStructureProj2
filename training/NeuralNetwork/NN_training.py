__author__ = 'Yue Dayu'

from pybrain.tools.shortcuts import buildNetwork
from pybrain.datasets import ClassificationDataSet
from pybrain.tools.customxml import NetworkWriter
from pybrain.supervised.trainers import BackpropTrainer
import numpy as np
import sys

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

def neural_train(filename, output):
    tag, data = readfile(filename)
    net = buildNetwork(len(data[0]), 3, 1)
    ds = ClassificationDataSet(len(data[0]), 10, labals)
    for x in range(0, len(data[0])):
        ds.addSample(data[x], [labals.index(tag[x])])
    trainer = BackpropTrainer(net)
    trainer.setData(ds)
    print "training..."
    trainer.train()
    print "done"
    NetworkWriter.writeToFile(net, 'testNet.xml')

if __name__ == '__main__':
    neural_train(sys.argv[1], sys.argv[2])