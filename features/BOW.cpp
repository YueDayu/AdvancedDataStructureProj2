#include "BOW.h"
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace cv::xfeatures2d;
using namespace std;

void BOW::calc(cv::Mat & img, Feature & feat){
    if (img.cols > 300 || img.rows > 300)
    {
        double fr = min(300.0/img.rows, 300.0/img.cols);
        resize(img, img, Size(), fr, fr, INTER_AREA);
    }
    vector<KeyPoint> kps;
    m_fd->detect(img, kps);
    Mat res;
    m_ext->compute(img, kps, res);
    feat.clear();
    for (int i = 0; i < m_ext->descriptorSize(); ++i)
        feat.push_back(res.at<uchar>(0, i));
}

void BOW::loadFromFile(const char *filename) {

}

void BOW::saveToFile(const char *filename) {

}

void BOW::train(const char *imagepath, const char *imagelists) {
    BOWKMeansTrainer trainer = BOWKMeansTrainer(200);
    Ptr<DescriptorExtractor> desext = SIFT::create();
    vector<KeyPoint> kps;
    Mat desp;
    Mat img;
    static char fullpath[100], filename[100];
    printf("Computing descriptors..\n");
    FILE* fin = fopen(imagelists, "r");
    int imgnum;
    fscanf(fin, "%d", &imgnum);
    int skipimg = 10;
    double kpratio = 0.3;
    for (int i = 0; i < imgnum; ++i)
    {
        fscanf(fin, "%s", filename);
        printf("%s, %d of %d..", filename, i+1, imgnum);
        if (i % skipimg)
        {
            printf("skipped\n");
            continue;
        }
        sprintf(fullpath, "%s%s", imagepath, filename);
        img = imread(fullpath);
        if (img.cols > 300 || img.rows > 300)
        {
            double fr = min(300.0/img.rows, 300.0/img.cols);
            resize(img, img, Size(), fr, fr, INTER_AREA);
        }
        m_fd->detect(img, kps);
        desext->compute(img, kps, desp);
        static int idx[5000];
        for (int j = 0; j < desp.rows; ++j) idx[j] = j;
        int selectedkp = (
                int)(desp.rows * kpratio);
        for (int j = 0; j < selectedkp; ++j)
        {
            int r = rand() % (desp.rows - j);
            swap(idx[j], idx[r]);
            trainer.add(desp.row(idx[j]));
        }
        printf("Complete\n");
    }
    fclose(fin);
    printf("Complete\n");
    printf("%d descriptors extracted.\n", trainer.descriptorsCount());

    printf("Clustering...");
    desp = trainer.cluster();
    m_ext->setVocabulary(desp);
    printf("Complete\n");
}


BOW::BOW() {
    m_fd = SIFT::create();
    m_ext = new BOWImgDescriptorExtractor(
            SIFT::create(),
            DescriptorMatcher::create("BruteForce")
    );
}

BOW::~BOW() {

}
