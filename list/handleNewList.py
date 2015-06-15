# created by Yue Dayu

import sys

def handle_new_list(filename, new_filename):
	infile = open(filename, 'r')
	head = infile.readline()
	lines = infile.readlines()
	maxnum = 0
	linenum = len(lines)
	newlines = []
	for x in lines:
		newlines.append((x.split(' '))[0:-1])
		if len((x.split(' '))[0:-1]) > maxnum:
			maxnum = len((x.split(' '))[0:-1])
	infile.close()
	outfile = open(new_filename, 'w')
	outfile.write(head)
	for x in range(0, linenum):
		for k in xrange(0, maxnum):
			if k < len(newlines[x]):
				outfile.write(newlines[x][k])
			else:
				outfile.write('0')
			if k == (maxnum - 1):
				outfile.write('\n')
			else:
				outfile.write(' ')

if __name__ == '__main__':
	handle_new_list(sys.argv[1], sys.argv[2])