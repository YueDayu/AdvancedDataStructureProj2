#ifndef __FEATUREEXTRACTOR_H__
#define __FEATUREEXTRACTOR_H__

typedef double Elemtype;

#include <opencv2/opencv.hpp>

#include <vector>

class Feature
{
public:
	Elemtype& operator[] (int x) { return m_data[x]; }
	int dim() const { return m_data.size(); }
	void clear() { m_data.clear(); }
	void push_back(Elemtype x) { m_data.push_back(x); }
private:
	std::vector<Elemtype> m_data;
};

class FeatureExtractor
{
public:
	virtual void calc(cv::Mat&, Feature&) = 0;
	void operator () (cv::Mat& im, Feature& fea) { calc(im, fea); }
};

#endif
