#include "ColorHistogram.h"
#include "ColorMean.h"
#include "CombinedFeature.h"
#include "ColorPerspective.h"

#include <opencv2/opencv.hpp>

#include <cstdio>
#include <cstring>

using namespace cv;

const char imagelists[] = "imagelists.txt";
const char outputfile[] = "imagefeatures.txt";
const char path[] = ".\\image\\";

int main()
{
	FILE *fin = fopen(imagelists, "r");
	FILE *fout = fopen(outputfile, "w");
	char filename[100], fullpath[100];
/*	FeatureExtractor *ext = new ComFeature();
	dynamic_cast<ComFeature*>(ext)->addFeature(new ColorHist(6, 2, 2));
	dynamic_cast<ComFeature*>(ext)->addFeature(new ColorMean());*/
	FeatureExtractor *ext = new ColorPerspec;
	Feature feat;
	Mat im;
	while (!feof(fin))
	{
		fgets(filename, 100, fin);
		int len = strlen(filename);
		if (feof(fin)) break;
		if (len <= 1) break;
		filename[len - 1] = '\0';
		printf("Processing %s...\n", filename);
		sprintf(fullpath, "%s%s", path, filename);
		im = imread(fullpath, 1);
		ext->calc(im, feat);
		filename[len - 6] = '\0';
		fprintf(fout, "%s", filename);
		for (int i = 0; i < feat.dim(); ++i) fprintf(fout, " %.5lf", feat[i]);
		fprintf(fout, "\n");
	}
	fclose(fin);
	fclose(fout);

	return 0;
}
