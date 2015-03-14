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
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    //Create a list to store n gaussian matrices
    std::vector<cv::Mat> listOfMatrices;

    Mat original;
    Mat original_g;
    cap >> original;
    
    
    //2 channels floating point matrix to store for each pixel a mean and a variance
    Mat gaussian( original.rows, original.cols, CV_32FC2 );

    
    cvtColor( original, original_g, CV_BGR2GRAY );
    //display the bg model
    //namedWindow("original",1);
    //imshow("original",original_g);
    Mat foreground;
    namedWindow("foreground",1);
    
    for(;;)
      {
        Mat frame;
	//Mat test;
        cap >> frame; // get a new frame from camera
        
	
	//Gaussian model for each pixel (= one mean, one std)
	//
	//

	//listOfMatrices.push_back(gaussian);

	cvtColor(frame, foreground, CV_BGR2GRAY);
	namedWindow("frame",1);
	imshow("frame",frame);
	for(int i = 0; i < foreground.rows; i++){
	  for(int j = 0; j < foreground.cols; j++){
	   
	    //simple difference between the current frame and the bg
	    if( abs(foreground.at<uchar>(i,j) - original_g.at<uchar>(i,j)) < 35){
	      foreground.at<uchar>(i,j) = 255;}
	  }
	}
	
	//test = abs(original_g - foreground);

	//Noise reduction with median filter
	medianBlur(foreground, foreground, 3);     
	imshow("foreground", foreground);
	if(waitKey(30) >= 0) break;
      }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
