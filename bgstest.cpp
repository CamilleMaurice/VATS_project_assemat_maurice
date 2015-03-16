#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <iostream>
#include <vector>
//#define INPUT_VIDEO "pets2001_camera1_2.mpg"
//#define INPUT_VIDEO "PETS06_S1-T1-C_3_abandoned_object_cif_mpeg.mpg"
#define INPUT_VIDEO "mh.mpg"
using namespace cv;
using namespace std;
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
  Mat previous_frame;
  Mat previous_background;
  Mat foreground;
  Mat counter_hot_restart; 
  Mat counter_stationary_objects;
  double alpha = 0.05; // for selective running average
  
  cap >> first_frame;
  

  cvtColor( first_frame, background_model, CV_BGR2GRAY );
  cvtColor( first_frame, previous_background, CV_BGR2GRAY );
  cvtColor( first_frame, first_frame, CV_BGR2GRAY );

  foreground = Mat :: zeros(first_frame.rows, first_frame.cols, CV_BGR2GRAY);
  //counter_hot_restart = Mat::zeros(first_frame.rows, first_frame.cols, CV_64F); // for hot restart
  previous_frame = first_frame;
  // previous_background = first_frame;
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
      
      for(int i = 0; i < frame.rows; i++){
	for(int j = 0; j < frame.cols; j++){
	 //part of the image not belonging to the previous foreground_mask
	  
	  // if( foreground.at<uchar>(i,j) == 1){ //PROBLEM ICI, FOREGROUND CONTIENT DES TRUCS DIFFERENTS DE 0 et 1!
	  //    background_model = previous_background; 
	     
	  // }
	  // if ( foreground.at<uchar>(i,j) == 0){
	  //   background_model.at<uchar>(i,j) = alpha * previous_frame.at<uchar>(i,j) + (1-alpha) * previous_background.at<uchar>(i,j);
	  // }

	  
	  //simple difference between the current frame and the bg
	  if( abs(frame.at<uchar>(i,j) - background_model.at<uchar>(i,j)) < 35){ //pixel is characterized as BG
	    foreground.at<uchar>(i,j) = 0;
            
	    //counter_hot_restart.at<uchar>(i,j) = counter_hot_restart.at<uchar>(i,j) +1 ;  // for hot restart
	    
	  }else{ //pixel is characterized as FG
            foreground.at<uchar>(i,j) = 1;
            
            //counter_hot_restart.at<uchar>(i,j) = 0 ;  // reset for hot restart
	    
	  }
	  
		    
	  
	  // if( counter_hot_restart.at<uchar>(i,j) < 5 ) { //for hot restart
	  //background_model.at<uchar>(i,j) = frame.at<uchar>(i,j);
	  //}
	  
	}
      }

      //Noise reduction with median filter
      //medianBlur(foreground, foreground, 3);

      namedWindow("background_model",1);
      imshow("background_model", background_model);
      
      namedWindow("foreground",1);
      imshow("foreground", foreground*255);


      previous_frame = frame;
      previous_background = background_model;

      if(waitKey(30) >= 0) break;
   
    }
  // the camera will be deinitialized automatically in VideoCapture destructor
return 0; }
