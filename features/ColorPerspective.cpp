#include "ColorPerspective.h"

using namespace cv;

void ColorPerspec::calc(Mat& im, Feature& res)
{
	Mat temp;
	//equalizeHist(gray, gray);
	resize(im, temp, Size(8, 8), 0, 0, INTER_AREA);
	res.clear();
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			for (int k = 0; k < 3; ++k)
				res.push_back(temp.at<Vec3b>(i, j)[k] / (double)255);
}
