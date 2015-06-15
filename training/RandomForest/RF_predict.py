__author__ = 'Yue Dayu'

from RF_training import *

def random_forset_predict(filename, train_file, output):
    type_list, data = readfile(filename)
    with open(train_file, 'rb') as f:
        clf = cPickle.load(f)
    print clf.score(data, type_list)

if __name__ == '__main__':
    random_forset_predict(sys.argv[1], sys.argv[2], sys.argv[3])