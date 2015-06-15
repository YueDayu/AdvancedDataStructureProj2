# Created by Yue Dayu

import sys
import random

def randomList(listFileName0, listFileName1, num):
	listfile0 = open(listFileName0, 'r')
	listfile1 = open(listFileName1, 'r')
	trainfile0 = open('./' + listFileName0.split('.')[0] + '_train.txt', 'w')
	testfile0 = open('./' + listFileName0.split('.')[0] + '_test.txt', 'w')
	trainfile1 = open('./' + listFileName1.split('.')[0] + '_train.txt', 'w')
	testfile1 = open('./' + listFileName1.split('.')[0] + '_test.txt', 'w')
	temp0 = listfile0.readlines()
	temp1 = listfile1.readlines()
	fileNum = len(temp0)
	testfile0.write(str(num) + '\n')
	trainfile0.write(str(fileNum - num) + '\n')
	testfile1.write(str(num) + '\n')
	trainfile1.write(str(fileNum - num) + '\n')
	test = random.sample(range(1, fileNum), num)
	for x in test:
		testfile0.write(temp0[x])
		testfile1.write(temp1[x])
	for x in range(1, fileNum):
		if x not in test:
			trainfile0.write(temp0[x])
			trainfile1.write(temp1[x])
	listfile0.close()
	trainfile0.close()
	testfile0.close()
	listfile1.close()
	trainfile1.close()
	testfile1.close()

if __name__ == '__main__':
	randomList(sys.argv[1], sys.argv[2], int(sys.argv[3]))