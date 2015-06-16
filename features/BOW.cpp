#include "BOW.h"
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/saliency.hpp>
#include "BGReplace.h"

using namespace cv;
using namespace cv::xfeatures2d;
using namespace saliency;
using namespace std;

void BOW::calc(cv::Mat & img, Feature & feat){
    Mat rimg;
    img.copyTo(rimg);
//    if (img.rows > 100 && img.cols > 100)
//        rimg = Mat(img, Range(img.rows/5, img.rows*4/5), Range(img.cols/5, img.cols*4/5));
//    else
//        rimg = img;
    if (rimg.cols > 300 || rimg.rows > 300)
    {
        double fr = min(300.0/rimg.rows, 300.0/rimg.cols);
        resize(rimg, rimg, Size(), fr, fr, INTER_AREA);
    }
    ImgBGReplace(rimg, rimg);
    //GaussianBlur(img, img, Size(5, 5), 1.5, 1.5, BORDER_REPLICATE);
    vector<KeyPoint> kps;
    m_fd->detect(rimg, kps);
    Mat res;
    m_ext->compute(rimg, kps, res);
    if (kps.size()) {
        feat.clear();
        for (int i = 0; i < m_ext->descriptorSize(); ++i)
            feat.push_back((double) res.at<uchar>(0, i) / max(kps.size(), 1U));
    }
    else {
        feat.clear();
        for (int i = 0; i < m_ext->descriptorSize(); ++i)
            feat.push_back(0);
    }
}

void BOW::loadFromFile(const char *filename) {
    printf("Reading vocabulary from file...");
    FILE *fs = fopen(filename, "r");
    int rows;
    float x;
    fscanf(fs, "%d", &rows);
    Mat voc(rows, 128, CV_32FC1);
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < voc.cols; ++j)
        {
            fscanf(fs, "%f ", &x);
            voc.at<float>(i, j) = x;
        }
    }
    fclose(fs);
    m_ext->setVocabulary(voc);
    printf("Complete\n");
}

void BOW::saveToFile(const char *filename) {
    printf("Saving vocabulary to file...");
    FILE *fs = fopen(filename, "w");
    const Mat& voc = m_ext->getVocabulary();
    fprintf(fs, "%d\n", voc.rows);
    for (int i = 0; i < voc.rows; ++i)
    {
        for (int j = 0; j < voc.cols; ++j)
            fprintf(fs, "%f ", voc.at<float>(i, j));
        fprintf(fs, "\n");
    }
    fclose(fs);
    printf("Complete\n");
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
//        if (img.rows > 100 && img.cols > 100)
//            img = Mat(img, Range(img.rows/5, img.rows*4/5), Range(img.cols/5, img.cols*4/5));
        if (img.cols > 300 || img.rows > 300)
        {
            double fr = min(300.0/img.rows, 300.0/img.cols);
            resize(img, img, Size(), fr, fr, INTER_AREA);
        }
        //GaussianBlur(img, img, Size(5, 5), 1.5, 1.5, BORDER_REPLICATE);
        ImgBGReplace(img, img);
        m_fd->detect(img, kps);
//        Mat show;
//        drawKeypoints(img, kps, show);
//        imshow("", show);
//        waitKey();
        desext->compute(img, kps, desp);
        static int idx[5000];
        for (int j = 0; j < desp.rows; ++j) idx[j] = j;
        int selectedkp = (int)(desp.rows * kpratio);
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
