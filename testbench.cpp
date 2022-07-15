#include <iostream>
#include <fstream>
#include <cstring>

#include "sobel.h"
#include "grayscale.h"

int main(int argc, char** argv) {

    if(argc != 6) {
        std::cout << "Usage: ./sobel_tb <red.data> <green.data> <blue.data> <gray.data> <sobel.data>" << std::endl;
        return -1;
    }

    unsigned char blueArr[WIDTH * HEIGHT];
    unsigned char redArr[WIDTH * HEIGHT];
    unsigned char greenArr[WIDTH * HEIGHT];
    unsigned char grayExpect[WIDTH * HEIGHT];
    unsigned char sobelExpect[(WIDTH-2)*(HEIGHT-2)];

    std::ifstream blueIn(argv[3]);
    std::ifstream redIn(argv[1]);
    std::ifstream greenIn(argv[2]);
    std::ifstream grayIn(argv[4]);
    std::ifstream sobelIn(argv[5]);

    blueIn.read((char*)blueArr, WIDTH * HEIGHT);
    redIn.read((char*)redArr, WIDTH * HEIGHT);
    greenIn.read((char*)greenArr, WIDTH * HEIGHT);
    grayIn.read((char*)grayExpect, WIDTH * HEIGHT);
    sobelIn.read((char*)sobelExpect, (WIDTH-2)*(HEIGHT-2));

    blueIn.close();
    redIn.close();
    greenIn.close();
    grayIn.close();
    sobelIn.close();

    unsigned char grayArr[WIDTH * HEIGHT];
    grayscale(redArr, greenArr, blueArr, grayArr);

    int grayOk = memcmp(grayArr, grayExpect, WIDTH * HEIGHT);
    if(grayOk == 0) {
        std::cout << "Grayscale conversion was successful." << std::endl;
    } else {
        std::cout << "Grayscale conversion unsuccessful." << std::endl;
        return 1;
    }

    unsigned char dstArr[(WIDTH-2)*(HEIGHT-2)];
    sobel(grayArr, dstArr);

    int sobelOk = memcmp(dstArr, sobelExpect, (WIDTH - 2) * (HEIGHT - 2));
    if(sobelOk == 0) {
        std::cout << "Sobel Filter was successful." << std::endl;
    } else {
        std::cout << "Sobel Filter was unsuccessful." << std::endl;
        return 2;
    }

    return 0;
}
