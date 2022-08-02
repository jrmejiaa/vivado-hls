#include <iostream>
#include <fstream>
#include <cstring>

#include "sobel.h"

int main(int argc, char** argv) {

    unsigned char grayArr[WIDTH * HEIGHT];
    unsigned char sobelExpect[(WIDTH-2)*(HEIGHT-2)];

    std::ifstream grayIn("./gray.data");
    std::ifstream sobelIn("./sobel.data");

    grayIn.read((char*)grayArr, WIDTH * HEIGHT);
    sobelIn.read((char*)sobelExpect, (WIDTH-2)*(HEIGHT-2));

    grayIn.close();
    sobelIn.close();

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
