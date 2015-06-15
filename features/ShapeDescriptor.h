//
// Created by CXY on 2015/6/16.
//

#ifndef GENFEATURES_SHAPEDESCRIPTOR_H
#define GENFEATURES_SHAPEDESCRIPTOR_H

#include "FeatureExtractor.h"

class ShapeDescriptor: public FeatureExtractor
{
public:
    virtual void calc(cv::Mat& img, Feature& feat);
};

#endif //GENFEATURES_SHAPEDESCRIPTOR_H
