#ifndef __HSV__H__
#define __HSV__H__
#include <cv.h>
#include <highgui.h>
#include <cmath>
#include <memory>
#include <fstream>
#include <iostream>
using namespace cv;
using namespace std;

#define pi double(3.1415926535897932384626)

#define MaxObjects 20000

#define _3 .at<Vec3b>(i,j)[2]//V
#define _2 .at<Vec3b>(i,j)[1]//S
#define _1 .at<Vec3b>(i,j)[0]//H

class HSV
{
/*
HSV颜色类，存储了一个HSV颜色，其范围为H(0,360)S(0,1)V(0,1)
并且有该颜色对应的直角坐标下的XYZ坐标
初始化: HSV t=HSV(h,s,v);
//h,s,v是利用OpenCV将RGB图像转为HSV后，某一点的HSV数值,范围为H(0,180)S(0,255)V(0,255)
//转换方法: (src为原来的RGB图像，转完仍存储在这里)
			Mat s = src;
			cv::cvtColor(s, src, CV_BGR2HSV);
*/
public:
	HSV(double hh = 0, double ss = 0, double vv = 0)
	{
		h = hh*2*pi / 180; 
		s = ss / 255; 
		v = vv / 255; 
		x = s*cos(h); 
		y = s*sin(h); 
		z = v;
	}
	double dis2(HSV& t)
	{
		return ((x - t.x) * (x - t.x) + (y - t.y) * (y - t.y) + (z - t.z) * (z - t.z));
	}
public:
	double h, s, v;//h:0~2pi s:0~1 v:0~1
	double x, y, z;
};

class ZImage
{
/*
图像存储类型，存储一个二维的HSV数组，每个元素表示该像素的HSV值
初始化: ZImage(400,300);//得到一个宽400高300的空白图像
	or	ZImage(img);//img为OpenCV中使用的Mat格式的图片或是另一个ZImage
*/
public:
	ZImage(int w0, int h0)
	{
		w = w0;
		h = h0;
		int i;
		img = new HSV*[h];
		object = new int*[h];
		for (i = 0; i < h; i++)
		{
			img[i] = new HSV[w];
			object[i] = new int[w];
			memset(img[i], 0, w*sizeof(HSV));
			memset(object[i], 0, w*sizeof(int));
		}
	}
	ZImage(Mat& src)
	{
		w = src.cols;
		h = src.rows;
		int i, j;
		img = new HSV*[h];
		object = new int*[h];
		for (i = 0; i < h; i++)
		{
			img[i] = new HSV[w];
			object[i] = new int[w];
			memset(img[i], 0, w*sizeof(HSV));
			memset(object[i], 0, w*sizeof(int));
		}
		for (i = 0; i < h; i++)
		{
			for (j = 0; j < w; j++)
			{
				img[i][j] = HSV(src _1, src _2, src _3);
			}
		}
	}
	ZImage(ZImage& z)
	{
		w = z.w;
		h = z.h;
		int i;
		img = new HSV*[h];
		object = new int*[h];
		for (i = 0; i < h; i++)
		{
			img[i] = new HSV[w];
			object[i] = new int[w];
			memset(object[i], 0, w*sizeof(int));
		}
		memcpy(img, z.img, sizeof(z.img));
	}
	~ZImage()
	{
		for (int i = 0; i < h; i++)
		{
			delete[]img[i];
			delete[]object[i];
		}
		delete[]img;
		delete[]object;
	}
public:
	int w, h, pixel, objectcount;
	HSV** img;
	int** object;
	HSV objectaveragecolor[MaxObjects];
	int objectarea[MaxObjects];
	int objectcenterx[MaxObjects], objectcentery[MaxObjects];
	double objectx2[MaxObjects], objecty2[MaxObjects], objectxy[MaxObjects];

public:
	void HSVChange();
	void RegionGrowingOriginal();
	void RegionGrowingIteration();
	void RegionGrowingDFS(int x, int y, int &id);
	void GetFeature();
	void OutputFeature(ofstream&);
	void OutputFeature(vector<double>&);
};

#endif
