#include "ColorHistogram.h"

#include <opencv2/opencv.hpp>

using namespace cv;

ColorHist::ColorHist(int _hbin, int _sbin, int _vbin) :
	hbin(_hbin), vbin(_vbin), sbin(_sbin) {}

void ColorHist::calc(Mat& im, Feature& res)
{
	Mat hsv = im;
	cvtColor(im, hsv, COLOR_BGR2HSV);
	int histsize[] = {hbin, sbin, vbin};
	const float hrange[] = {0, 180};
	const float srange[] = {0, 256};
	const float vrange[] = {0, 256};
	const float *ranges[] = {hrange, srange, vrange};
	int channels[] = {0, 1, 2};
	MatND hist;
	calcHist(&hsv, 1, channels, Mat(), hist, 3, histsize, ranges);

	MatND normhist;
	normalize(hist, normhist, 1, 0, NORM_L1);

	res.clear();
	for (int i = 0; i < hbin; ++i)
		for (int j = 0; j < sbin; ++j)
			for (int k = 0; k < vbin; ++k)
				res.push_back(normhist.at<float>(i, j, k));
}
