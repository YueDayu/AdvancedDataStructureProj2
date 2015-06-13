# Created by Yue Dayu

import os
import sys

def getNameList(path):
	print path
	f = open('./namelist.txt', 'w')
	tmp = os.popen('dir /B ' + path).readlines()
	print len(tmp)
	f.write(str(len(tmp)) + '\n')
	for x in tmp:
		f.write(x)
	f.close();

if __name__ == '__main__':
	getNameList(sys.argv[1])
