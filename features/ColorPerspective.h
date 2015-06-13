#ifndef __COLORPERS_H__
#define __COLORPERS_H__

#include "FeatureExtractor.h"

class ColorPerspec: public FeatureExtractor
{
public:
	void calc(cv::Mat&, Feature&);	
};

#endif
