__author__ = 'Yue Dayu'

from NN_training import *
from pybrain.tools.customxml import NetworkReader
from collections import Counter

def neural_predict(filename, train_file, output):
    testtag, testdata = readfile(filename)
    net = NetworkReader.readFrom(train_file)
    i = 0
    num = 0
    output_file = open(output, 'w')
    output_file.write("test data size: " + str(len(testtag)) + '\n')
    output_type_list = []
    output_type_size = []
    output_type_right = []
    output_typt_error_detail = []
    for k in testdata:
        res = net.activate(k)
        if testtag[i] not in output_type_list:
            output_type_list.append(testtag[i])
            output_type_size.append(0)
            output_type_right.append(0)
            output_typt_error_detail.append([])
        j = output_type_list.index(testtag[i])
        output_type_size[j] += 1
        if labals[max_index(res)] == testtag[i]:
            num += 1
            output_type_right[j] += 1
        else:
            (output_typt_error_detail[j]).append(labals[max_index(res)])
        i += 1
    # for k in testdata:
    #     res = net.activate(k)
    #     if labals[max_index(res)] == testtag[i]:
    #         num += 1
    #     i += 1
    output_file.write("correct number: " + str(num) + '\n')
    output_file.write("correct rate: " + str(num / (float)(len(testtag))) + '\n')
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
    print num
    output_file.close()

if __name__ == '__main__':
    neural_predict(sys.argv[1], sys.argv[2], sys.argv[3])