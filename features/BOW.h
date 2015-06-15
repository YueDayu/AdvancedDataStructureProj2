#ifndef __BOW_H__
#define __BOW_H__

#include "FeatureExtractor.h"
#include <opencv2/opencv.hpp>

class BOW: public FeatureExtractor
{
public:
    BOW();
    ~BOW();
    void calc(cv::Mat&, Feature&);
    void loadFromFile(const char* filename);
    void saveToFile(const char* filename);
    void train(const char* imagepath, const char* imagelists);

private:
    cv::Ptr<cv::BOWImgDescriptorExtractor> m_ext;
    cv::Ptr<cv::Feature2D> m_fd;
};

#endif
