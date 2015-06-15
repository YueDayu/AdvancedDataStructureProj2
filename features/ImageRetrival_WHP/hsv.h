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
HSV��ɫ�࣬�洢��һ��HSV��ɫ���䷶ΧΪH(0,360)S(0,1)V(0,1)
�����и���ɫ��Ӧ��ֱ�������µ�XYZ����
��ʼ��: HSV t=HSV(h,s,v);
//h,s,v������OpenCV��RGBͼ��תΪHSV��ĳһ���HSV��ֵ,��ΧΪH(0,180)S(0,255)V(0,255)
//ת������: (srcΪԭ����RGBͼ��ת���Դ洢������)
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
ͼ��洢���ͣ��洢һ����ά��HSV���飬ÿ��Ԫ�ر�ʾ�����ص�HSVֵ
��ʼ��: ZImage(400,300);//�õ�һ����400��300�Ŀհ�ͼ��
	or	ZImage(img);//imgΪOpenCV��ʹ�õ�Mat��ʽ��ͼƬ������һ��ZImage
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
