//
// Created by CXY on 2015/6/16.
//

#include "BGReplace.h"
#include "RegionGrow.h"

using namespace cv;
using namespace std;

const int numiter = 3;

void ImgBGReplace(cv::Mat src, cv::Mat& dest)
{
    ZImage* pic = preprocessing(src);
    pic->HSVChange();
    pic->RegionGrowingOriginal();
    for (int i = 0; i < numiter; i++)
        pic->RegionGrowingIteration();

    static bool isbg[MaxObjects];
    for (int i = 0; i < MaxObjects; ++i) isbg[i] = false;
    for (int i = 0; i < pic->h; ++i)
        isbg[pic->object[i][0]] = isbg[pic->object[i][pic->w-1]] = true;
    for (int i = 0; i < pic->w; ++i)
        isbg[pic->object[0][i]] = isbg[pic->object[pic->h-1][i]] = true;
    dest = Mat(pic->h, pic->w, CV_8UC3);
    if (src.rows > 300 || src.cols > 300)
    {
        double fr = min(300.0/src.rows, 300.0/src.cols);
        resize(src, src, Size(), fr, fr, CV_INTER_AREA);
    }
    for (int i = 0; i < pic->h; ++i)
        for (int j = 0; j < pic->w; ++j)
        {
            if (isbg[pic->object[i][j]]) dest.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
            else dest.at<Vec3b>(i, j) = src.at<Vec3b>(i, j);
        }
//    imshow("", dest);
//    waitKey();
    delete pic;
}
