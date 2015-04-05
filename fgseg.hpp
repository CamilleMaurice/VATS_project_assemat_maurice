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
  cv::Mat hot_restart;
  int H;
  int W;
  int thres;
  int alpha;
  int block_size;
  int shadows;
};

char VATS_Foreground_Segmentation_Start( tForegroundSegmentationVATS * desc);
void VATS_Foreground_Segmentation_Stop( tForegroundSegmentationVATS * desc);
char VATS_Foreground_Segmentation ( tForegroundSegmentationVATS * desc, Mat input, char shadows, Mat mask);

#endif
