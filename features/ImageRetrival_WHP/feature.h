#pragma once
#include <cv.h>
#include <highgui.h>
#include <cmath>
#include <memory>
#include <fstream>
#include <iostream>
using namespace cv;
using namespace std;

#define MaxFeature 500

struct Feature
{
	double c1, c2, c3, x, y, p, v, e;
};

#define sigma1 (1. / 9)
#define sigma2 (1. / 4)
#define sigma3 (1. / 9)
#define wp (1. / 3)
#define wv (1. / 3)
#define we (1. / 3)
#define w1 (1. / 3)
#define w2 (1. / 3)
#define w3 (1. / 3)

extern double PictureSimilarity(string file1, string file2);//·µ»ØÁ½¸öÍ¼Ïñ¾àÀë
extern double FeatureSimilarity(Feature &f1, Feature &f2);