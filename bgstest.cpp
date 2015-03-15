#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <iostream>
#include <vector>
#define INPUT_VIDEO "mh.mpg"
using namespace cv;
// Usage
// download build.sh
// in a terminal : sh build.sh
// then the executable file is created and
// ./binary
int main(int, char**)
{

  VideoCapture cap(INPUT_VIDEO);
  if(!cap.isOpened()) // check if we succeeded
    return -1;

  Mat original;
  Mat background;
  Mat foreground;

  double alpha = 0.05; //for selective running average
  cap >> original;
  

  cvtColor( original, background, CV_BGR2GRAY );
  //display the bg model
  //namedWindow("original",1);
  //imshow("original", background);
 
  
  for(;;)
    {
      Mat frame;
      
      cap >> frame; // get a new frame from camera
      cvtColor(frame, foreground, CV_BGR2GRAY);
      
      namedWindow("frame",1);
      imshow("frame",frame);
      
      for(int i = 0; i < foreground.rows; i++){
	for(int j = 0; j < foreground.cols; j++){
	  
	  //simple difference between the current frame and the bg
	  if( abs(foreground.at<uchar>(i,j) - background.at<uchar>(i,j)) < 35){ //pixel is characterized as BG
	    foreground.at<uchar>(i,j) = 255;
	  }else{ //pixel is characterized as FG
	    foreground.at<uchar>(i,j) = 0;}
	
	}
      }

      //Noise reduction with median filter
      medianBlur(foreground, foreground, 3);
      
      namedWindow("foreground",1);
      imshow("foreground", foreground);

      if(waitKey(30) >= 0) break;
   
    }
  // the camera will be deinitialized automatically in VideoCapture destructor
  return 0;
}
