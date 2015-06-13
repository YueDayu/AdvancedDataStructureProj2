#ifndef __COLORMEAN_H__
#define __COLORMEAN_H__

#include "FeatureExtractor.h"

class ColorMean: public FeatureExtractor
{
public:
	void calc(cv::Mat&, Feature&);
};

#endif