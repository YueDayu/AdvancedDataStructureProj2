#ifndef __BOW_H__
#define __BOW_H__

#include "FeatureExtractor.h"

class BOW: public FeatureExtractor
{
public:
    void calc(Mat&, Feature&);
    void loadFromFile(const char* filename);
    void saveToFile(const char* filename);
    void train(const char* imagepath, const char* imagelists);
};

#endif
