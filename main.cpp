#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <iostream>
#include <vector>
#include "fgseg.hpp"

//#define INPUT_VIDEO "pets2001_camera1_2.mpg"
//#define INPUT_VIDEO "PETS06_S1-T1-C_3_abandoned_object_cif_mpeg.mpg"
#define INPUT_VIDEO "mh.mpg"

int main(int, char**){
  VideoCapture cap(INPUT_VIDEO);
  if(!cap.isOpened()) // check if we succeeded
    return -1;

	
}
