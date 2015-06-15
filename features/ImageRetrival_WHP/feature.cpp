#include "feature.h"

double PictureSimilarity(string file1, string file2)
{
	double result = 0;
	ifstream q, i;
	q.open(file1);
	i.open(file2);
	ShapeFeature qfeature[MaxFeature], ifeature[MaxFeature];
	int qcount = 0, icount = 0;
	double s[MaxFeature][MaxFeature];
	bool quse[MaxFeature], iuse[MaxFeature];
//	memset(&qfeature, 0, sizeof(qfeature));
//	memset(&ifeature, 0, sizeof(ifeature));
//	memset(s, 0, sizeof(s));
	memset(quse, 0, sizeof(quse));
	memset(iuse, 0, sizeof(iuse));
	string temp;
	while (!q.eof())
	{
		qcount++;
		q >> qfeature[qcount].c1 >> qfeature[qcount].c2 >> qfeature[qcount].c3 >>
			qfeature[qcount].x >> qfeature[qcount].y >> qfeature[qcount].p >> qfeature[qcount].v >> qfeature[qcount].e;
		getline(q, temp);
	}
	while (!i.eof())
	{
		icount++;
		i >> ifeature[icount].c1 >> ifeature[icount].c2 >> ifeature[icount].c3 >>
			ifeature[icount].x >> ifeature[icount].y >> ifeature[icount].p >> ifeature[icount].v >> ifeature[icount].e;
		getline(i, temp);
	}
	qcount--;
	icount--;
	for (int i = 1; i <= qcount; i++)
	{
		for (int j = 1; j <= icount; j++)
		{
			s[i][j] = FeatureSimilarity(qfeature[i], ifeature[j]);
		}
	}
	int qusecount = qcount, iusecount = icount, maxq, maxi;
	double maxs;
	while (qusecount > 0 && iusecount > 0)
	{
		maxs = 0;
		for (int i = 1; i <= qcount; i++)
		{
			for (int j = 1; j <= icount; j++)
			{
				if (!quse[i] && !iuse[j])
				{
					if (maxs < s[i][j])
					{
						maxs = s[i][j];
						maxq = i;
						maxi = j;
					}
				}
			}
		}
		result += maxs * (qfeature[maxq].p + ifeature[maxi].p) / 2;
		quse[maxq] = true;
		iuse[maxi] = true;
		qusecount--;
		iusecount--;
	}
	q.clear();
	q.sync();
	q.close();
	i.clear();
	i.sync();
	i.close();
	return result;
}

double FeatureSimilarity(ShapeFeature &f1, ShapeFeature &f2)
{
	double s1, s2, s3;
	s1 = exp(-((f1.c1 - f2.c1) * (f1.c1 - f2.c1) + (f1.c2 - f2.c2) * (f1.c2 - f2.c2) + (f1.c3 - f2.c3) * (f1.c3 - f2.c3)) / 3 / sigma1);
	s2 = exp(-((f1.x - f2.x) * (f1.x - f2.x) + (f1.y - f2.y) * (f1.y - f2.y)) / 2 / sigma2);
	s3 = exp(-(wp * (f1.p - f2.p) * (f1.p - f2.p) + wv * (f1.v - f2.v) * (f1.v - f2.v) + we * (f1.e - f2.e) * (f1.e - f2.e)) / sigma3);
	return(s1 * w1 + s2 * w2 + s3 * w3);
}