#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "sobel.h"
#include "grayscale.h"

using namespace cv;

int main(int argc, char** argv) {

    if(argc != 3) {
        std::cout << "Expected Usage: ./sobel_cpu <inputfile> <outputfile>" << std::endl;
        return 1;
    }

    Mat src = imread(argv[1], IMREAD_COLOR);
    if( !src.data ){
        std::cout << "ERROR: Could not read input image!" << std::endl;
        return 2;
    }

    Mat bgr[3];   //destination array
    split(src,bgr);//split source
    Mat blue  = bgr[0];
    Mat green = bgr[1];
    Mat red   = bgr[2];
    if(!blue.isContinuous() || !green.isContinuous() || !red.isContinuous()){
        std::cout << "ERROR: Could not extract arrays from matrices!" << std::endl;
        return 3;
    }
    unsigned char * blueArr  = blue.data;
    unsigned char * greenArr = green.data;
    unsigned char * redArr   = red.data;
    unsigned char * grayArr  = (unsigned char*) malloc(WIDTH * HEIGHT * sizeof(unsigned char));
    grayscale(redArr, greenArr, blueArr, grayArr);
    Mat grayMat(HEIGHT, WIDTH, CV_8UC1, grayArr);

    unsigned char * dstArr = (unsigned char*) malloc((WIDTH-2)*(HEIGHT-2)*sizeof(unsigned char));
    sobel(grayArr, dstArr);

    Mat dstMat((HEIGHT-2), (WIDTH-2), CV_8UC1, dstArr);
    imwrite(argv[2], dstMat);
    free(dstArr);
    return 0;
}
