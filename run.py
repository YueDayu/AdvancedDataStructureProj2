# Created by Yue Dayu

import os
import sys

def createList(path):
	print 'creating the filename list...'
	os.system('python ./list/createNameList.py ' + path)

def getFeature(path):
	print 'getting features...'
	os.system('genfeatures.exe ' + path + ' ./namelist.txt')

def test(test_featre_file):
	print '--------------SVM test--------------'
	os.system('python ./training/SVM/SVM_predict.py ' + test_featre_file + ' class.pkl svm_result.txt')
	print '--------------NN test--------------'
	os.system('python ./training/NeuralNetwork/NN_predict.py ' + test_featre_file + ' class.pkl NN_result.txt')
	print '--------------Random Forest test--------------'
	os.system('python ./training/RandomForest/RF_predict.py ' + test_featre_file + ' class.pkl Random_forest_result.txt')

if __name__ == '__main__':
	path = sys.argv[1]
	createList(path)
	getFeature(path)
	test('./output/imagefeatures_out.txt')
