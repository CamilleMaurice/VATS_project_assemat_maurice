#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <iostream>
#include <vector>
#include "fgseg.hpp"

using namespace cv;
using namespace std;


//I dont understand how we should use Start / Stop
char VATS_Foreground_Segmentation_Start( tForegroundSegmentationVATS * desc){

	
	
}


void VATS_Foreground_Segmentation_Stop( tForegroundSegmentationVATS * desc){
	
	
}

char VATS_Foreground_Segmentation (tForegroundSegmentationVATS * desc, Mat input, char shadows, Mat mask){
	Mat frame;
	
	Mat counter_hot_restart; 
	counter_hot_restart = Mat::zeros(desc->H, desc->W, CV_8U);
	
	int alpha = 0.95;
	cvtColor(input, frame, CV_BGR2GRAY); 	
		
	//Simple BG Substraction
		for(int i = 0; i < desc->H; i++){
			for(int j = 0; j < desc->W; j++){
				if( abs(frame.at<uchar>(i,j) - desc->background_model.at<uchar>(i,j)) < desc->thres){
					mask.at<uchar>(i,j) = 0;
								
					//Selective running average update of the background
					desc->background_model.at<uchar>(i,j) = alpha * frame.at<uchar>(i,j) + (1-alpha) * desc->background_model.at<uchar>(i,j);
					
					//
					counter_hot_restart.at<uchar>(i,j) = counter_hot_restart.at<uchar>(i,j) +1 ;
				
				}else{ // It is foreground
					mask.at<uchar>(i,j) = 1;
					
					counter_hot_restart.at<uchar>(i,j) = 0;
				}
				
				//Background is refreshed until the pixel is locked
				if( counter_hot_restart.at<uchar>(i,j) < 3 ) {
					desc->background_model.at<uchar>(i,j) = frame.at<uchar>(i,j);
				}
			}
		}
		
	
	//PostProcessing Chromaticity based method slide 80
		if (shadows == 255) {
		Mat channel[3];
		cvtColor(input, input, CV_BGR2HSV); 	
		
	//channel contains the Hue Mat, Saturation Mat, Value Mat
		split(input,channel); 
		
	}
	
	return 0;
}


 
