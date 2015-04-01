#include <string>
#include <cstdlib>
#include <cstdio>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

struct tForegroundSegmentationVATS {
  Mat first_frame;
  Mat background_model;
  int H;
  int W;
  int thres;
};

char VATS_Foreground_Segmentation_Start( tForegroundSegmentationVATS * desc);
void VATS_Foreground_Segmentation_Stop( tForegroundSegmentationVATS * desc);
char VATS_Foreground_Segmentation ( tForegroundSegmentationVATS * desc, IplImage * input, char shadows, IplImage * mask);
