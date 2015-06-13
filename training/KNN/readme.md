#KNN

测试命令：

	python k-neighbors.py <train feature file> <test feature file> <k>

例如：

	python k-neighbors.py colorfeatures.txt test.txt 10

输出：

	第一行：对某个测试数据的分类是否准确
	第二行：分类准确率
	第三行：对某个测试数据的正确率
	第四行：平均正确率

例如：

	[0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1]
	rate: 0.3
	[0.4, 0.5, 0.4, 0.0, 0.2, 0.6, 0.0, 0.1, 0.1, 0.6, 0.6, 0.4, 0.5, 0.3, 0.2, 0.0, 0.7, 0.2, 0.3, 0.5]
	average: 0.33