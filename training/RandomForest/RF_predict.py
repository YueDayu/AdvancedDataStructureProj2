__author__ = 'Yue Dayu'

from RF_training import *
from collections import Counter
from sklearn.neighbors import NearestNeighbors
import random
import numpy

random_number = 100

def random_forset_predict(filename, train_file, output):
    print "reading the file..."
    type_list, data = readfile(filename)
    print "done"
    with open(train_file, 'rb') as f:
        clf = cPickle.load(f)
    result = clf.predict(data)
    num = 0
    i = 0
    output_file = open(output, 'w')
    output_file.write("test data size: " + str(len(type_list)) + '\n')
    output_type_list = []
    output_type_size = []
    output_type_right = []
    output_typt_error_detail = []
    for x in type_list:
        if x not in output_type_list:
            output_type_list.append(x)
            output_type_size.append(0)
            output_type_right.append(0)
            output_typt_error_detail.append([])
        j = output_type_list.index(x)
        output_type_size[j] += 1
        if x == result[i]:
            num += 1
            output_type_right[j] += 1
        else:
            (output_typt_error_detail[j]).append(result[i])
        i += 1
    print num
    output_file.write("correct number: " + str(num) + '\n')
    print num / (float)(len(result))
    output_file.write("correct rate: " + str(num / (float)(len(result))) + '\n')
    i = 0
    for x in output_type_list:
        output_file.write(x + "\t")
        output_file.write(str(output_type_right[i]) + '/' + str(output_type_size[i]) + ':'
                          + str(float(output_type_right[i]) / output_type_size[i])[0:5] + '\t')
        c = Counter(output_typt_error_detail[i])
        for y in c:
            output_file.write(y + ":" + str(c[y]) + '\t')
            print(y + ":" + str(c[y]))
        # print c
        i += 1
        output_file.write('\n')
    output_file.close()

def readfile_real_name(filename):
    list_file = open(filename, 'r')
    _ = list_file.readline()
    lines = list_file.readlines()
    type_list = []
    feature_list = []
    for line in lines:
        current_line = line.split(' ')
        type_list.append(current_line[0])
        temp_list = map(float, current_line[1:])
        feature_list.append(temp_list)
    result = np.array(feature_list)
    return type_list, result

def readfile_real_name_group(filename, group, number):
    list_file = open(filename, 'r')
    _ = list_file.readline()
    lines = list_file.readlines()
    name_list = []
    feature_list = []
    name_result = []
    feature_result = []
    for x in group:
        name_list.append([])
        feature_list.append([])
    for line in lines:
        current_line = line.split(' ')
        type = (current_line[0].split('_'))[0]
        i = numpy.where(group == type)[0]
        name_list[i].append(current_line[0])
        temp_list = map(float, current_line[1:])
        feature_list[i].append(temp_list)
    for x in range(0, len(group)):
        sample_index = random.sample(range(0, len(name_list[x])), number[x])
        for k in sample_index:
            name_result.append(name_list[x][k])
            feature_result.append(feature_list[x][k])
    return name_result, feature_result

def get_num(num):
    return int(num * random_number)

def random_forest_single_predict(test_filename, name, feature_file, train_file, k):
    name_list, data = readfile_real_name(test_filename)
    print 'reading file...'
    test_data = data[name_list.index(name)]
    with open(train_file, 'rb') as f:
        clf = cPickle.load(f)
    print 'done'
    result_rate = (clf.predict_proba(test_data))[0]
    class_name = clf.classes_
    print name
    num = map(get_num, result_rate)
    name_list, feature_list = readfile_real_name_group(feature_file, class_name, num)
    neigh = NearestNeighbors()
    neigh.fit(feature_list)
    kneighbors_result_list = neigh.kneighbors(test_data, k, False)[0]
    print kneighbors_result_list
    for x in kneighbors_result_list:
        print name_list[x]
    classification_result = []
    average_list = []
    real_name = (name.split('_'))[0]
    counter = Counter(kneighbors_result_list)
    if real_name == name_list[counter.most_common(1)[0][0]].split('_')[0]:
        classification_result.append(1)
    else:
        classification_result.append(0)
    num = 0
    for i in kneighbors_result_list:
        if (name_list[i].split('_'))[0] == real_name:
            num += 1
    average_list.append((float)(num) / (float)(k))
    print classification_result, average_list
    return classification_result, average_list

def random_forset_predict_for_pr(filename, train_file, output):
    print "reading the file..."
    type_list, data = readfile(filename)
    print "done"
    with open(train_file, 'rb') as f:
        clf = cPickle.load(f)
    result = clf.predict(data)
    num = 0
    i = 0
    output_file = open(output, 'w')
    for x in result:
        output_file.write(type_list[i])
        output_file.write("\t")
        output_file.write(x)
        output_file.write('\n')
        i += 1
    output_file.close()

if __name__ == '__main__':
    # random_forset_predict(sys.argv[1], sys.argv[2], sys.argv[3])
    # random_forest_single_predict(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4], int(sys.argv[5]))
    random_forset_predict_for_pr(sys.argv[1], sys.argv[2], sys.argv[3])
