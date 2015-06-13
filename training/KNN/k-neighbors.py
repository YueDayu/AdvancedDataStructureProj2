__author__ = 'Yue Dayu'

import numpy as np
from sklearn.neighbors import NearestNeighbors
import sys
from collections import Counter

def readfile(filename):
    list_file = open(filename, 'r')
    temp = list_file.readlines()
    list_num = int(temp[0]) + 1
    namelist = []
    feature_list = []
    for x in range(1, list_num):
        current_line = temp[x].split(' ')
        namelist.append(current_line[0])
        temp_list = []
        for i in range(1, len(current_line)):
            temp_list.append(float(current_line[i]))
        feature_list.append(temp_list)
    result = np.array(feature_list)
    return namelist, result

def k_neighbors_analysis(train_filename, test_filename, k):
    train_name_list, train_feature_list = readfile(train_filename)
    test_name_list, test_feature_list = readfile(test_filename)
    neigh = NearestNeighbors()
    neigh.fit(train_feature_list)
    kneighbors_result_list = neigh.kneighbors(test_feature_list, k, False)
    classification_result = []
    average_list = []
    for x in range(0, len(kneighbors_result_list)):
        real_name = (test_name_list[x].split('_'))[0]
        counter = Counter(kneighbors_result_list[x])
        if real_name == train_name_list[counter.most_common(1)[0][0]].split('_')[0]:
            classification_result.append(1)
        else:
            classification_result.append(0)
        num = 0
        for i in kneighbors_result_list[x]:
            if (train_name_list[i].split('_'))[0] == real_name:
                num += 1
        average_list.append((float)(num) / (float)(k))
    return classification_result, average_list

if __name__ == '__main__':
    list1, list2 = k_neighbors_analysis(sys.argv[1], sys.argv[2], int(sys.argv[3]))
    print list1
    num = 0
    for x in list1:
        if x == 1:
            num += 1
    print "rate: " + str((float)(num) / len(list1))
    print list2
    print "average: " + str(sum(list2) / float(len(list2)))