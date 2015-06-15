__author__ = 'Yue Dayu'

import cPickle
import numpy as np
import sys
import random

name_table = ['n10247358', 'n01923025', 'n01613177', 'n07897438', 'n11669921', 'n03767203', 'n03877845', 'n02278980', 'n04515003', 'n04583620']
svm_rate = [0.508, 0.38, 0.225, 0.285, 0.787, 0.520, 0.512, 0.696, 0.478, 0.632]
random_rate = [0.578, 0.46, 0.475, 0.408, 0.833, 0.562, 0.538, 0.857, 0.630, 0.734]

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

def compare(filename0, filename1, svm_train_file, random_train_file, output):
    type_list0, data0 = readfile(filename0)
    type_list1, data1 = readfile(filename1)
    print "loading..."
    with open(svm_train_file, 'rb') as f:
        random_clf0 = cPickle.load(f)
    with open(random_train_file, 'rb') as f1:
        random_clf1 = cPickle.load(f1)
    outfile = open(output, 'w')
    num0 = 0
    num1 = 0
    num2 = 0
    num3 = 0
    num4 = 0
    num5 = 0
    print "start..."
    # svm_res = svm_clf.predict(data)
    # random_res = random_clf.predict(data)
    # random_res_rate = random_clf.predict_proba(data)
    random_0_res_rate = random_clf0.predict_proba(data0)
    random_0_res = random_clf0.predict(data0)
    random_1_res_rate = random_clf1.predict_proba(data1)
    random_1_res = random_clf1.predict(data1)
    for x in range(0, len(data0)):
        if max(random_0_res_rate[x]) > max(random_1_res_rate[x]):
            result = random_0_res[x][0]
            if result == type_list0[x]:
                num0 += 1
        else:
            result = random_1_res[x][0]
            if result == type_list1[x]:
                num0 += 1
        # if svm_res[x] == type_list[x] and max(random_res_rate[x]) < 0.158:
        #     num4 += 1
        # if random_res[x] != type_list[x] and max(random_res_rate[x]) > 0.3:
        #     num5 += 1
        # if svm_res[x] == type_list[x] and random_res[x] == type_list[x]:
        #     outfile.write("1\t")
        #     if max(random_res_rate[x]) < min:
        #         min = max(random_res_rate[x])
        #     num0 += 1
        # elif svm_res[x] == type_list[x] and random_res[x] != type_list[x]:
        #     outfile.write("2\t")
        #     num1 += 1
        # elif svm_res[x] != type_list[x] and random_res[x] == type_list[x]:
        #     outfile.write("3\t")
        #     if max(random_res_rate[x]) < min:
        #         min = max(random_res_rate[x])
        #     num2 += 1
        # else:
        #     outfile.write("4\t")
        #     num3 += 1
        # outfile.write(type_list[x] + '\t' + svm_res[x] + '\t' + random_res[x] + '\t' + str(max(random_res_rate[x])) + '\n')
    print num0
    # print num1
    # print num2
    # print num3
    # print num4
    # print num5
    # print min

if __name__ == '__main__':
    compare(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4], sys.argv[5])