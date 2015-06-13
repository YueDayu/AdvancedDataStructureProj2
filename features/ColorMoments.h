#ifndef __COLORMOMENTS_H__
#define __COLORMOMENTS_H__

#include "FeatureExtractor.h"

class ColorMoments: public FeatureExtractor
{
public:
	void calc(cv::Mat&, Feature&);
};

#endif
