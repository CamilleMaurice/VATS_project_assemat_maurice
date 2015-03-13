#include "opencv2/opencv.hpp"
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

    
    Mat original;
    Mat original_g;
    cap >> original ;

    cvtColor( original, original_g, CV_BGR2GRAY );
    namedWindow("original",1);
    imshow("original",original_g);
    Mat foreground;
    namedWindow("foreground",1);
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
        cvtColor(frame, foreground, CV_BGR2GRAY);
	for(int i = 0; i < foreground.rows; i++){
	  for(int j = 0; j < foreground.cols; j++){
	    //simple difference between the current frame and the bg
	    if( abs(foreground.at<uchar>(i,j) - original_g.at<uchar>(i,j)) < 35){
	      foreground.at<uchar>(i,j) = 255;}
	  }
	}
	
	//Noise reduction with median filter
	medianBlur(foreground, foreground, 3);     
	imshow("foreground", foreground);
	if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}