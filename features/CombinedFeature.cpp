#include "CombinedFeature.h"

using namespace cv;
using namespace std;

void ComFeature::calc(Mat& im, Feature& res)
{
	res.clear();
	Feature feat;
	for (int i = 0; i < exts.size(); ++i)
	{
		exts[i]->calc(im, feat);
		for (int j = 0; j < feat.dim(); ++j)
			res.push_back(feat[j]);
	}
}
