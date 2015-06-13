#ifndef __COLORHIST_H__
#define __COLORHIST_H__

#include "FeatureExtractor.h"

class ColorHist: public FeatureExtractor
{
public:
	ColorHist(int _hbin = 6, int _sbin = 4, int _vbin = 4);
	void calc(cv::Mat&, Feature&);
private:
	int hbin, sbin, vbin;
};

#endif
