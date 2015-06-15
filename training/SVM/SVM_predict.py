__author__ = 'Yue Dayu'

from SVM_training import *
from collections import Counter

def svm_predict(filename, train_file, output):
    type_list, data = readfile(filename)
    clf = joblib.load(train_file)
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

if __name__ == '__main__':
    svm_predict(sys.argv[1], sys.argv[2], sys.argv[3])