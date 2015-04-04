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
  
	VideoCapture cap(desc->video);
	if(!cap.isOpened()) // check if we succeeded
		return -1;

	cap>>desc->first_frame;

	desc->H = desc->first_frame.rows;
	desc->W = desc->first_frame.cols;
	desc->bg_model=desc->first_frame;

	VATS_Foreground_Segmentation_BG_model(desc,cap);		 
	
	return 0;
	
}

char VATS_Foreground_Segmentation_BG_model(tForegroundSegmentationVATS * desc, VideoCapture cap){

	Mat mask,frame;	
	mask = Mat :: zeros(desc->H, desc->W, CV_8U);
	Mat counter_hot_restart; 
	counter_hot_restart = Mat::zeros(desc->H, desc->W, CV_8U);
		
	while(going_on==1){
	  
      //get a new frame
		cap >> frame; 
      
      //compute the BG model
		for(int i = 0; i < desc->H; i++){
			for(int j = 0; j < desc->W; j++){
				if(mask.at<uchar>(i,j)==1){
					desc->bg_model.at<Vec3b>(i,j)=desc->alpha*frame.at<Vec3b>(i,j)+(1-desc->alpha)*desc->bg_model.at<Vec3b>(i,j);	
					counter_hot_restart.at<uchar>(i,j) = counter_hot_restart.at<uchar>(i,j) +1 ;
					}
				else{
					counter_hot_restart.at<uchar>(i,j) = 0;
				}	
			
				if( counter_hot_restart.at<uchar>(i,j) < desc->cpt_hot_restart ) {
					desc->bg_model.at<uchar>(i,j) = frame.at<uchar>(i,j);
				}	
			}
		}  
		// Get the FG binary mask
		VATS_Foreground_Segmentation(desc,frame,'y',mask);
      
		//Display      
		namedWindow("frame",1);
        imshow("frame",frame);
      
        namedWindow("mask",1);
        imshow("mask",mask*255);	
	
		namedWindow("bg_model",1);
		imshow("bg_model", desc->bg_model);

		if(waitKey(30) >= 0)
			break;
	}
}
void VATS_Foreground_Segmentation_Stop( tForegroundSegmentationVATS * desc){
	going_on=0;
	cout<<"stop!"<<endl;
}

char VATS_Foreground_Segmentation (tForegroundSegmentationVATS * desc, Mat input, char shadows, Mat FG_mask){
	Mat Im, Bkg;
	float a, b, t_s, t_h;
	cvtColor(input,Im,CV_BGR2GRAY);
	cvtColor(desc->bg_model,Bkg,CV_BGR2GRAY);
	Mat H,S,V;//for shadow detect
	Mat im_c[3];
	Mat bg_c[3];
	split(input,im_c);//get the 3channels of frame
	split(desc->bg_model,bg_c);//idem for bg model

	if(shadows=='y'){	
		im_c[2] *= 1.0;//to force float
		bg_c[2]*=1.0;
		//init of matrices we need to tell if shadows or not
		V=im_c[2]*1.0/(bg_c[2]*1.0);
		S=abs(im_c[1]-bg_c[1]);
		H=abs(im_c[0]-bg_c[0]);
		//init of parameters used to evaluate matrices
		a=0.5;
		b=0.9;
		t_s=1;
		t_h=1;
	}	
	Mat abs_dist = abs(Im-Bkg);
	/*Mat abs_dist[3];
	
	for(int i=0;i++;i<3){
		abs_dist[i] = abs(im_c[i] - bg_c[i]);
	}
	cout<<im_c[2].at<uchar>(52,52)<<endl;
	cout<<"laaaaaa"<<endl;
*/
	for(int i = 0; i < desc->H; i++){
		for(int j = 0; j < desc->W; j++){
			if(abs_dist.at<uchar>(i,j) < desc->thres){
				//point(j,i) is BG
			//	cout<<"laaaaaa"<<endl;
				FG_mask.at<uchar>(i,j) = 0;			
			}
			else{
				//point(j,i) is FG
				FG_mask.at<uchar>(i,j) = 1;
				if(shadows=='y'){
					H.at<uchar>(i,j)=min(H.at<uchar>(i,j), ((unsigned char)(360-H.at<uchar>(i,j))));
					if(V.at<uchar>(i,j)>=a && V.at<uchar>(i,j)<=b && S.at<uchar>(i,j)<t_s && H.at<uchar>(i,j)<t_h){
						//this is a shadow, so it shouldn't be part of FG mask
						FG_mask.at<uchar>(i,j)=0;
					}
				}
			}			
		}
	}
	return 0;
}
