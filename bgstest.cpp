#include "opencv2/opencv.hpp"
#define INPUT_VIDEO "mh.mpg"
using namespace cv;

int main(int, char**)
{
   VideoCapture cap(INPUT_VIDEO); 
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    
    Mat original;
    Mat original_g;
    cap >> original ;

    cvtColor( original, original_g, CV_BGR2GRAY );
    namedWindow("original",1);
    imshow("original",original_g);
    Mat foreground;
    namedWindow("edges",1);
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
        cvtColor(frame, foreground, CV_BGR2GRAY);
	for(int i = 0; i < foreground.rows; i++){
	  for(int j = 0; j < foreground.cols; j++){
	    if( abs(foreground.at<uchar>(i,j) - original_g.at<uchar>(i,j)) < 25){
	      foreground.at<uchar>(i,j) = 255;}
	  }
	}
	     
	      
	imshow("foreground", foreground);
	if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
