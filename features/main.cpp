#include "ColorHistogram.h"
#include "ColorMean.h"
#include "CombinedFeature.h"
#include "BOW.h"
#include "ShapeDescriptor.h"
#include "RegionGrow.h"

#include <opencv2/opencv.hpp>

#include <cstdio>
#include <cstring>

using namespace cv;

int main(int argc, char** argv )
{
    if ( argc != 3 )
    {
        printf("usage: genfeatures <Image_Path> <Image_namelist>\n");
        return -1;
    }

    char* imagelists = argv[2];
    char* imagepath = argv[1];
    const char outputfile[] = "output\\imagefeatures_out.txt";
    const char outputvoc[] = "output\\vocabulary.txt";

    char filename[100], fullpath[100];
	FeatureExtractor *ext = new ComFeature();
    BOW *bow = new BOW();
	dynamic_cast<ComFeature*>(ext)->addFeature(bow);
    dynamic_cast<ComFeature*>(ext)->addFeature(new ColorMean());
    dynamic_cast<ComFeature*>(ext)->addFeature(new ColorHist(6, 2, 2));
    //dynamic_cast<ComFeature*>(ext)->addFeature(new ShapeDescriptor);
    //bow->train(imagepath, imagelists);
    //bow->saveToFile(outputvoc);
    bow->loadFromFile(outputvoc);
    //FeatureExtractor *ext = new ColorPerspec;
    Feature feat;
    Mat im;
    int numimg;
    FILE *fin = fopen(imagelists, "r");
    FILE *fout = fopen(outputfile, "w");
    fscanf(fin, "%d", &numimg);
    fgets(filename, 100, fin);
    fprintf(fout, "%d\n", numimg);
    while (!feof(fin))
    {
        fgets(filename, 100, fin);
        int len = strlen(filename);
        if (feof(fin)) break;
        if (len <= 1) break;
        filename[len - 1] = '\0';
        printf("Processing %s...\n", filename);
        sprintf(fullpath, "%s%s", imagepath, filename);
        im = imread(fullpath, 1);
        ext->calc(im, feat);
        filename[len - 6] = '\0';
        fprintf(fout, "%s", filename);
        for (int i = 0; i < feat.dim(); ++i)
            fprintf(fout, " %f", (float)feat[i]);
        fprintf(fout, "\n");
    }
    fclose(fin);
    fclose(fout);

    return 0;
}
