#include "ColorMean.h"

using namespace cv;

#include <cmath>

typedef unsigned char uchar;

void ColorMean::calc(Mat& im, Feature& res)
{
	Mat ras;
	resize(im, ras, Size(3, 3), 0, 0, INTER_AREA);
	res.clear();
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
		{
			Vec3b r = ras.at<Vec3b>(i, j);
			for (int k = 0; k < 3; ++k)
			{
				double t = r[k];
				t /= 256;
				res.push_back(t);
			}
		}
}
