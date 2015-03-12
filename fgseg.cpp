#include "fgseg.h"



int uu_display(string im){
    Mat image;
    image = imread(im);
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image);

    waitKey(0);
    }
