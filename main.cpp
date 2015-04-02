#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <iostream>
#include <vector>
#include "fgseg.hpp" 

#define INPUT_VIDEO "mh.mpg"
//#define INPUT_VIDEO "Backyard1/%05d.jpg"
int main(int, char**){
//Open video and check if succeeded
 
  VideoCapture cap(INPUT_VIDEO);
  if(!cap.isOpened()) 
    return -1;


//Allocation of the descriptor
tForegroundSegmentationVATS * desc = new tForegroundSegmentationVATS;

Mat tmp,mask;
cap >> tmp;

//Calling process should initialize the descriptor
cvtColor( tmp, desc->first_frame,  CV_BGR2GRAY );     
cvtColor( tmp, desc->background_model, CV_BGR2GRAY ); 

desc->H = desc->first_frame.rows;
desc->W = desc->first_frame.cols;
desc->thres = 35;

//Mask initialization
mask = Mat :: zeros(desc->H, desc->W, CV_8U);

for(;;){
	  Mat frame;
	  cap >> frame; 
      		  
      VATS_Foreground_Segmentation(desc,frame,0,mask);
      
      
      //Display      
        namedWindow("frame",1);
        imshow("frame",frame);
      
        namedWindow("mask",1);
        imshow("mask",mask*255);	
      	
      	namedWindow("bg",1);
        imshow("bg",desc->background_model);	

if(waitKey(30) >= 0) break;
}
return 0;

}
