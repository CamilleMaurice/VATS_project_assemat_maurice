#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <iostream>
#include <vector>
#include "fgseg.hpp"


int going_on;
  
using namespace cv;
using namespace std;

char VATS_Foreground_Segmentation_Start( tForegroundSegmentationVATS * desc){
	going_on = 1;
	Mat frame, mask;
   
    Mat counter_hot_restart; 
	
	VideoCapture cap(desc->video);
	if(!cap.isOpened()) // check if we succeeded
		return -1;

	cap>>desc->first_frame;

	desc->H = desc->first_frame.rows;
	desc->W = desc->first_frame.cols;
	desc->bg_model = desc->first_frame;

	mask = Mat :: zeros(desc->H, desc->W, CV_8U);
	counter_hot_restart = Mat::zeros(desc->H, desc->W, CV_8U);

	desc->hot_restart = counter_hot_restart;
			
	//VATS_Foreground_Segmentation_BG_model(desc,cap);		 
	while(going_on==1){
		cap >> frame;
		VATS_Foreground_Segmentation(desc,frame,desc->shadows,mask);
		
	
		if(waitKey(30) >= 0)
			break;
	
	
		//Display      
		namedWindow("frame",1);
        imshow("frame",frame);
      
        namedWindow("mask",1);
        imshow("mask",mask*255);	
	
		namedWindow("bg_model",1);
		imshow("bg_model", desc->hot_restart);	
	}
		
	return 0;
	
}

void VATS_Foreground_Segmentation_Stop( tForegroundSegmentationVATS * desc){
	going_on=0;
	cout<<"stop!"<<endl;
}

char VATS_Foreground_Segmentation (tForegroundSegmentationVATS * desc, Mat input, char shadows, Mat FG_mask){
	Mat channels_input[3];
	Mat channels_bg[3];

	// We consider the input frame and the background model to be in the BGR space.
	split(input,channels_input);      //get the 3channels of frame
	split(desc->bg_model,channels_bg);//idem for bg model
	
	int alpha = desc->alpha;
	int block_size = desc->block_size;
	int sumI,sumBG;

		
		//~ if(shadows=='y'){	
		//~ Mat V,S,H;
		//~ int a,b,t_s,t_h;
		//~ 
		//~ channels_input[2] *= 1.0;//to force float
		//~ channels_bg[2]*=1.0;
		//~ //init of matrices we need to tell if shadows or not
		//~ V=channels_input[2]*1.0/(channels_bg[2]*1.0);
		//~ S=abs(channels_input[1]-channels_bg[1]);
		//~ H=abs(channels_input[0]-channels_bg[0]);
		//~ //init of parameters used to evaluate matrices
		//~ a=0.5;
		//~ b=0.9;
		//~ t_s=1;
		//~ t_h=1;
	//~ }
	
	
	//Compute the foreground mask with a color background and considering blocks or pixels
	for(int x = floor(block_size/2); x < desc->H-floor(block_size/2); x ++){
		for(int y = floor(block_size/2); y < desc->W-floor(block_size/2); y ++){
			int cpt = 0;
			for (int c =0;c<3;c++){
				sumI = 0;
				sumBG = 0;				
				//If we want to process at pixel level
				if (block_size == 1){
					sumI = channels_input[c].at<uchar>(x,y);
					sumBG = channels_bg[c].at<uchar>(x,y);
				}
				//We want to process at block level (usually 3 or 5)
				else{
					for (int i = -floor(block_size/2) ; i < floor(block_size/2) ; i ++){
						for (int j = -floor(block_size/2); j < floor(block_size/2); j ++){
							sumI = sumI + channels_input[c].at<uchar>(x+i,y+j);
							sumBG = sumBG + channels_bg[c].at<uchar>(x+i,y+j);
						}
					}
				}				
				if( abs(sumI - sumBG) < desc->thres){ 
					cpt = cpt +1;					
				}
			}
			//If the pixel color is below the threashold for all the 3 channels, then we set it as background.
			if(cpt > 0) { 
					FG_mask.at<uchar>(x,y) = 0;
					//Pixel is locked and remains locked
					if(desc->hot_restart.at<uchar>(x,y) == 255){
						desc->hot_restart.at<uchar>(x,y) = 255;
					}else{
						desc->hot_restart.at<uchar>(x,y) = desc->hot_restart.at<uchar>(x,y) +1;
						desc->bg_model.at<Vec3b>(x,y)=desc->alpha*input.at<Vec3b>(x,y)+(1-desc->alpha)*desc->bg_model.at<Vec3b>(x,y);
					}	
			//Foreground case
			}else{
					FG_mask.at<uchar>(x,y) = 1;
					desc->hot_restart.at<uchar>(x,y) = 0;					
			}			
			
			//Background is refreshed until the pixel is locked
			if( desc->hot_restart.at<uchar>(x,y) < desc->cpt_hot_restart) {
					desc->bg_model.at<Vec3b>(x,y) = input.at<Vec3b>(x,y);						
			}				
		}
	}
	return 0;	
}



