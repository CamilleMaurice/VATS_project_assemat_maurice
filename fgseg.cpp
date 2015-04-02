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
	for(int i = 0; i < desc->H; i++){
		for(int j = 0; j < desc->W; j++){
			if( abs(input.at<uchar>(i,j) - desc->background_model.at<uchar>(i,j)) < desc->thres){
				mask.at<uchar>(i,j) = 0;			
			}else{
				mask.at<uchar>(i,j) = 1;
			}
		}
	}
	return 0;
}


 
