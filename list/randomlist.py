# Created by Yue Dayu

import sys
import random

def randomList(listFileName, num):
	listfile = open(listFileName, 'r')
	trainfile = open('./trainlist.txt', 'w')
	testfile = open('./testlist.txt', 'w')
	temp = listfile.readlines()
	fileNum = len(temp) - 1
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