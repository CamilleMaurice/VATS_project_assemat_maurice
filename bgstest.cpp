#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <iostream>
#include <vector>
#define INPUT_VIDEO "pets2001_camera1_2.mpg"

using namespace cv;

// Usage
// download build.sh
// in a terminal : sh build.sh
// then the executable file is created and
// ./binary
int main(int, char**){

  VideoCapture cap(INPUT_VIDEO);
  if(!cap.isOpened()) // check if we succeeded
    return -1;

  Mat first_frame;
  Mat background_model;
  Mat foreground;
Mat counter; // for hot restart

  double alpha = 0.07; // for selective running average
  
  cap >> first_frame;
  

  cvtColor( first_frame, background_model, CV_BGR2GRAY );
  cvtColor( first_frame, first_frame, CV_BGR2GRAY );

  counter = Mat::zeros(first_frame.rows, first_frame.cols, CV_64F); // for hot restart
  //display the bg model
  //namedWindow("first_frame",1);
  //imshow("first_frame", background_model);
 
  
  for(;;)
    {
      Mat frame;
      
      cap >> frame; // get a new frame from camera
      cvtColor(frame, foreground, CV_BGR2GRAY); 
      cvtColor(frame, frame, CV_BGR2GRAY);
      namedWindow("frame",1);
      imshow("frame",frame);
      
      for(int i = 0; i < foreground.rows; i++){
	for(int j = 0; j < foreground.cols; j++){
	  
	  //simple difference between the current frame and the bg
	  if( abs(frame.at<uchar>(i,j) - background_model.at<uchar>(i,j)) < 45){ //pixel is characterized as BG
	    foreground.at<uchar>(i,j) = 255;
            counter.at<uchar>(i,j) = counter.at<uchar>(i,j) +1 ;  // for hot restart
	    
	    //background_model.at<uchar>(i,j) = alpha * frame.at<uchar>(i,j) + (1-alpha) * background_model.at<uchar>(i,j);

	  }else{ //pixel is characterized as FG
            foreground.at<uchar>(i,j) = 0;
            background_model.at<uchar>(i,j) = alpha * frame.at<uchar>(i,j) + (1-alpha) * background_model.at<uchar>(i,j);
            counter.at<uchar>(i,j) = 0 ;  // reset for hot restart
	  }
	  
	
	  if( counter.at<uchar>(i,j) < 20 ) { //for hot restart
           background_model.at<uchar>(i,j) = frame.at<uchar>(i,j);
	 }
	  
	}
      }

      //Noise reduction with median filter
      //medianBlur(foreground, foreground, 3);
      
      namedWindow("foreground",1);
      imshow("foreground", foreground);

      namedWindow("background_model",1);
      imshow("background_model", background_model);
      

      if(waitKey(30) >= 0) break;
   
    }
  // the camera will be deinitialized automatically in VideoCapture destructor
return 0; }
