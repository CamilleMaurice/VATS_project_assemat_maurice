#ifndef FGSEG_HPP
#define FGSEG_HPP

#include <string>
#include <cstdlib>
#include <cstdio>
#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;

struct tForegroundSegmentationVATS {
  int cpt_hot_restart;
  char* video;
  cv::Mat first_frame;
  cv::Mat bg_model;
  int H;
  int W;
  int thres;
  int alpha;
  int shadows;
};

char VATS_Foreground_Segmentation_Start( tForegroundSegmentationVATS * desc);
char VATS_Foreground_Segmentation_BG_model( tForegroundSegmentationVATS * desc, VideoCapture cap);
void VATS_Foreground_Segmentation_Stop( tForegroundSegmentationVATS * desc);
char VATS_Foreground_Segmentation ( tForegroundSegmentationVATS * desc, Mat input, char shadows, Mat mask);

#endif
