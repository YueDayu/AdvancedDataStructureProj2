#ifndef __COMFEATURE_H__
#define __COMFEATURE_H__

#include "FeatureExtractor.h"

class ComFeature: public FeatureExtractor
{
public:
	void calc(cv::Mat&, Feature&);
	void addFeature(FeatureExtractor* val) { exts.push_back(val); }
private:
	std::vector<FeatureExtractor*> exts;
};

#endif
