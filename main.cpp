#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <iostream>
#include <vector>
#include "fgseg.hpp" 

//#define INPUT_VIDEO "mh.mpg"

int main(int argc, char** argv){
	
	
	if (argc != 2){
		cout<<"usage: main <video_name>"<<endl;
		return EXIT_FAILURE;
	}
	
	
	tForegroundSegmentationVATS * desc = new tForegroundSegmentationVATS;
	
	//Initializing descriptor with wanted parameters
	desc->cpt_hot_restart = 100;
	desc->video = argv[1];
	desc->shadows = 0;
	desc->thres = 80;
	desc->alpha = 0;
	desc->block_size = 3;
	
	
	VATS_Foreground_Segmentation_Start(desc);
	VATS_Foreground_Segmentation_Stop(desc);
	
	return EXIT_SUCCESS;
}
