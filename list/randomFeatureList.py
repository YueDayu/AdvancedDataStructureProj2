# Created by Yue Dayu

import sys
import random

def randomList(listFileName, num):
	listfile = open(listFileName, 'r')
	trainfile = open('./' + listFileName.split('.')[0] + '_train.txt', 'w')
	testfile = open('./' + listFileName.split('.')[0] + '_test.txt', 'w')
	temp = listfile.readlines()
	fileNum = len(temp)
	testfile.write(str(num) + '\n')
	trainfile.write(str(fileNum - num) + '\n')
	test = random.sample(range(1, fileNum), num)
	for x in test:
		testfile.write(temp[x])
	for x in range(1, fileNum):
		if x not in test:
			trainfile.write(temp[x])
	listfile.close()
	trainfile.close()
	testfile.close()

if __name__ == '__main__':
	randomList(sys.argv[1], int(sys.argv[2]))