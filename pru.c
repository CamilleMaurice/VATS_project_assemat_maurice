#include <stdio.h>

#include "opencv2/core/core_c.h"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/highgui/highgui_c.h"

#define INPUT_VIDEO	"mh.mpg"
//#define INPUT_VIDEO "pets2001_camera1_1.mpg"

main()
{
	CvCapture* capture=NULL;
	IplImage *image=NULL, *output=NULL;
	IplImage *tmp=NULL;
	IplImage *tmp2=NULL;
	IplImage *firstFrame=NULL;
	CvVideoWriter *videowriter;
	
	// for timing double start=0,end=0,total=0;
	int i=0;
	int row, col;
	uchar *ppixel, *ppixel_o;

	if(!(capture = cvCaptureFromFile(INPUT_VIDEO)))
	{
		printf("Bad Video File\n");
		return -1;
	}
	

	firstFrame = cvQueryFrame(capture);
        
	
	cvNamedWindow("INPUT", 0);
	cvNamedWindow("OUTPUT", 0);
	

	image = cvQueryFrame( capture );
	output = cvCreateImage( cvGetSize(image), image->depth, image->nChannels );	
	tmp = cvCreateImage( cvGetSize(image), image->depth, 1 );	
	tmp2 = cvCreateImage( cvGetSize(image), image->depth, 1 );	
	cvCvtColor( firstFrame, tmp, CV_RGB2GRAY );
	
	videowriter = cvCreateVideoWriter("result.mpg", CV_FOURCC('P','I','M','1'), 25, cvGetSize(image), 1 );
	

	
	do
	{
		i++;
		//timing
		//start =((double)cvGetTickCount()/(cvGetTickFrequency()*1000.) );
		
		
		// Array processing
		cvCvtColor(image , tmp2, CV_RGB2GRAY );

				
		// Process individual pixels 
		for (row = 0; row < tmp->height; row++)
		for (col = 0; col < tmp->width; col++)
		{
			ppixel = cvPtr2D( tmp2, row, col, NULL );
			ppixel_o = cvPtr2D( tmp, row, col, NULL );

			//If the difference with the current pixel and the pixel from the first frame is < 25
			//We say this pixel is background and set it to white 255.
			if (abs(*ppixel -  *ppixel_o ) < 25)
			   *ppixel =  255;
		}
		
		//timing
		//end = ((double)cvGetTickCount()/(cvGetTickFrequency()*1000.) );
		//total=total + end-start;
				
		cvShowImage("INPUT", image);
		cvShowImage("OUTPUT", tmp2);
		
		cvWriteFrame( videowriter, output );

		//printf("Processing frame %d --> %.3g ms\n", i,end-start);
		
		cvWaitKey( 2 );


	} while (image=cvQueryFrame( capture ));
	
	
	cvReleaseImage( &tmp );
	cvReleaseImage( &tmp2 );
	cvReleaseImage( &output );
	cvReleaseImage( &firstFrame );

	cvReleaseCapture( &capture );
	cvReleaseVideoWriter( &videowriter );

}
