#include <string>
#include <cstdlib>
#include <cstdio>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

struct tForegroundSegmentationVATS {
  Mat first_frame;
  Mat background_model;
};

