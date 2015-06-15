#include<iostream>
#include<fstream>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include"hsv.h"
#include"preprocessing.h"
#include"feature.h"

#define numiter 3

int N;

#if 1

#if 1

int main()
{
	//ZImage* pic = preprocessing("C:\\Users\\Zhou Bowei\\Pictures\\Windows フォト ビューアー壁紙.jpg");

	ifstream fin("D:\\950623\\proj2\\AdvancedDataStructureProj2\\list\\namelist.txt");
	ofstream fout("allfeat.txt");
	fin >> N;
	for (int o = 0; o < N; o++)
	{
		string name;
		fin >> name;
	//	if (o < 5482) continue;
		cout <<o<<"        "<< name<<endl;
		ZImage* pic = preprocessing("D:\\950623\\course_algorithms\\feature\\image\\"+name);
		pic->HSVChange();
		pic->RegionGrowingOriginal();
		for (int i = 0; i < numiter; i++)
		{
			pic->RegionGrowingIteration();
		}
#if 1
		Mat src = Mat(pic->h, pic->w, CV_8UC3);
		for (int i = 0; i < pic->h; i++)
		{
			for (int j = 0; j < pic->w; j++)
			{
				int h0 = int(atan2(pic->objectaveragecolor[pic->object[i][j]].y, pic->objectaveragecolor[pic->object[i][j]].x) * 90 / pi);
				int s0 = int(sqrt(pic->objectaveragecolor[pic->object[i][j]].x*pic->objectaveragecolor[pic->object[i][j]].x + pic->objectaveragecolor[pic->object[i][j]].y*pic->objectaveragecolor[pic->object[i][j]].y) * 255);
				int v0 = int(pic->objectaveragecolor[pic->object[i][j]].z * 255);
				if (h0 < 0) h0 += 180;
				if (h0 > 180) h0 = 180;
				if (s0 > 255) s0 = 255;
				if (v0 > 255) v0 = 255;
				src _1 = h0;
				src _2 = s0;
				src _3 = v0;
			}
		}
		Mat s = src;
		cvtColor(s, src, CV_HSV2BGR);
		string name1;
		int t = 0;
		while (name[t] != '.')
		{
			name1 += name[t];
			t++;
		}
		name1 += ".PNG";
		imwrite("p\\"+name1, src);
		//imshow("迭代3次", src);
		//cvWaitKey();
		
		s.release();
		src.release();
#endif
		pic->GetFeature();
		fout << name << " ";
		pic->OutputFeature(fout);
		delete pic;
	}
	fout.close();
	return 0;
}
#else

int main()
{
	ZImage* pic = preprocessing("C:\\Users\\Zhou Bowei\\Pictures\\Doge-label..png");
	//ZImage* pic = preprocessing("A:\\Downloads\\大二下_课件\\数算后八周作业1\\DS&Alg-Project1-Release\\data\\image\\n01613177_1793.JPEG");
	pic->HSVChange();
	pic->RegionGrowingOriginal();
	for (int i = 0; i < 迭代次数; i++)
	{
		pic->RegionGrowingIteration();
	}
	Mat src = Mat(pic->h, pic->w, CV_8UC3);
	for (int i = 0; i < pic->h; i++)
	{ 
		for (int j = 0; j < pic->w; j++)
		{
			int h0 = int(atan2(pic->objectaveragecolor[pic->object[i][j]].y, pic->objectaveragecolor[pic->object[i][j]].x) * 90 / pi);
			int s0 = int(sqrt(pic->objectaveragecolor[pic->object[i][j]].x*pic->objectaveragecolor[pic->object[i][j]].x + pic->objectaveragecolor[pic->object[i][j]].y*pic->objectaveragecolor[pic->object[i][j]].y) * 255);
			int v0 = int(pic->objectaveragecolor[pic->object[i][j]].z * 255);
			if (h0 < 0) h0 += 180;
			if (h0 > 180) h0 = 180;
			if (s0 > 255) s0 = 255;
			if (v0 > 255) v0 = 255;
			src _1 = h0;
			src _2 = s0;
			src _3 = v0;
		}
	}
	Mat s = src;
	cvtColor(s, src, CV_HSV2BGR);
	//imwrite("p\\" + name1, src);
	imshow("迭代3次", src);
	cvWaitKey();
	return 0;
}

#endif


#else
#define FEATURE_PATH string("A:\\vs\\ImageRetrival_WHP\\ImageRetrival_WHP\\p\\")
int main()
{
	ifstream filenames("A:\\filenames.txt");
	string names[N];
	int i;
	for (i = 0; i < N; i++)
	{
		filenames >> names[i];
		names[i] = FEATURE_PATH + names[i] + ".txt";
	}
	int j;
	double dis[N][N];
	int mint[N];
	for (i = 0; i < N; i++)
	{
		double min = 1e30;
		for (j = 0; j < N; j++)
		{
			if (i == j)
				dis[i][j] = 1e30;
			else
				dis[i][j] = 1 - PictureSimilarity(names[i], names[j]);
			if (dis[i][j] < min)
			{
				mint[i] = j;
				min = dis[i][j];
			}
		}
		cout << names[i] << '\t' << names[mint[i]] << endl;
	}
	ofstream fout("分类结果.txt");
	for (i = 0; i < N; i++)
	{
		fout << names[i] <<'\t'<<names[mint[i]]<< endl;
	}
	
}

#endif