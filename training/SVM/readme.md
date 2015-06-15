#使用方法

SVM_training.py：

	python SVM_training.py <train feature file> <output file>

例子：

	python SVM_training.py imagefeatures_train.txt traindata.pkl

SVM_predict.py:

	python SVM_predict.py <test feature file> <train file> <output file>

例子：

	python SVM_predict.py imagefeatures_test.txt traindata.pkl result.txt