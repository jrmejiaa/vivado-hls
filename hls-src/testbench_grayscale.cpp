#include <iostream>
#include <fstream>
#include <cstring>

#include "grayscale.h"

int main(int argc, char** argv) {

    unsigned char blueArr[WIDTH * HEIGHT];
    unsigned char redArr[WIDTH * HEIGHT];
    unsigned char greenArr[WIDTH * HEIGHT];
    unsigned char grayExpect[WIDTH * HEIGHT];

    std::ifstream blueIn("./blue.data");
    std::ifstream redIn("./red.data");
    std::ifstream greenIn("./green.data");
    std::ifstream grayIn("./gray.data");

    blueIn.read((char*)blueArr, WIDTH * HEIGHT);
    redIn.read((char*)redArr, WIDTH * HEIGHT);
    greenIn.read((char*)greenArr, WIDTH * HEIGHT);
    grayIn.read((char*)grayExpect, WIDTH * HEIGHT);

    blueIn.close();
    redIn.close();
    greenIn.close();
    grayIn.close();

    unsigned char grayArr[WIDTH * HEIGHT];
    grayscale(redArr, greenArr, blueArr, grayArr);

    int grayOk = memcmp(grayArr, grayExpect, WIDTH * HEIGHT);
    if(grayOk == 0) {
        std::cout << "Grayscale conversion was successful." << std::endl;
    } else {
        std::cout << "Grayscale conversion was unsuccessful." << std::endl;
        return 1;
    }

    return 0;
}
