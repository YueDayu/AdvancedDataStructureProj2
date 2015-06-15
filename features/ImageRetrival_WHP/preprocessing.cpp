#include "preprocessing.h"
#include <opencv2/opencv.hpp>

ZImage* preprocessing(const Mat img)
{
	Mat src;
	img.copyTo(src);
	if (src.rows > 300 || src.cols > 300)
	{
		double fr = min(300.0/src.rows, 300.0/src.cols);
		resize(src, src, Size(), fr, fr, CV_INTER_AREA);
	}
	Mat s = src;
	int size = 5;
	double sigma = 1.5;
	GaussianBlur(s, src, Size(size, size), sigma, sigma , 4);//进行size=5,sigma=1.5的高斯滤波
	s = src;
	//imshow("原图像(已进行高斯模糊)", s);
	cvtColor(s, src, CV_BGR2HSV);
	ZImage* z = new ZImage(src);
	cvtColor(s, src, CV_HSV2BGR);
	return z;
}