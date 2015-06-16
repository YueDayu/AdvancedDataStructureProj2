//
// Created by CXY on 2015/6/16.
//

#include "ShapeDescriptor.h"
#include "RegionGrow.h"

const int numiter = 3;
const int numdim = 224;

void ShapeDescriptor::calc(cv::Mat &img, Feature &feat) {
    ZImage* pic = preprocessing(img);
    pic->HSVChange();
    pic->RegionGrowingOriginal();
    for (int i = 0; i < numiter; i++)
        pic->RegionGrowingIteration();
    pic->GetFeature();
    pic->OutputFeature(feat.m_data);
    if (feat.dim() > numdim) feat.m_data.resize(numdim);
    delete pic;
    int numadd = numdim - feat.dim();
    for (int i = 0; i < numadd; ++i) feat.push_back(0);
}

