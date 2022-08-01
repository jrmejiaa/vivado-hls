#include <iostream>
#include <fstream>
#include <cstring>
#include <chrono>
#include <tapasco.hpp>

#include "../fpga/grayscale.cpp"

int main(int argc, char const *argv[])
{
    if(argc != 5) {
        std::cout << "Usage: ./grayscale-launch <red.data> <green.data> <blue.data> <gray.data>" << std::endl;
        return -1;
    }

    tapasco::Tapasco tapasco;

    unsigned char redArr[WIDTH * HEIGHT];
    unsigned char greenArr[WIDTH * HEIGHT];
    unsigned char blueArr[WIDTH * HEIGHT];
    unsigned char grayExpect[WIDTH * HEIGHT];

    std::ifstream redIn(argv[1]);
    std::ifstream greenIn(argv[2]);
    std::ifstream blueIn(argv[3]);
    std::ifstream grayIn(argv[4]);

    redIn.read((char*) redArr, WIDTH * HEIGHT);
    greenIn.read((char*) greenArr, WIDTH * HEIGHT);
    blueIn.read((char*) blueArr, WIDTH * HEIGHT);
    grayIn.read((char*) grayExpect, WIDTH * HEIGHT);

    redIn.close();
    greenIn.close();
    blueIn.close();
    grayIn.close();

    /* CPU */

    std::cout << "Start CPU Grayscale conversion..." << std::endl;

    unsigned char grayArr[WIDTH * HEIGHT];
    auto cpu_start = std::chrono::high_resolution_clock::now();
    grayscale(redArr, greenArr, blueArr, grayArr);
    auto cpu_stop = std::chrono::high_resolution_clock::now();

    int cpuGrayOk = memcmp(grayArr, grayExpect, WIDTH * HEIGHT);
    if (cpuGrayOk == 0) {
        std::cout << "CPU Grayscale conversion was successful." << std::endl;
        std::cout << "CPU time: " << std::chrono::duration_cast<std::chrono::microseconds>(cpu_stop - cpu_start).count() << " microsec." << std::endl;
    } else {
        std::cout << "CPU Grayscale conversion unsuccessful." << std::endl;
        return 1;
    }

    /* FPGA */

    std::cout << std::endl << "Start FPGA Grayscale conversion..." << std::endl;

    auto red_buffer_pointer = tapasco::makeWrappedPointer(redArr, WIDTH * HEIGHT * sizeof(unsigned char));
    auto green_buffer_pointer = tapasco::makeWrappedPointer(greenArr, WIDTH * HEIGHT * sizeof(unsigned char));
    auto blue_buffer_pointer = tapasco::makeWrappedPointer(blueArr, WIDTH * HEIGHT * sizeof(unsigned char));
    auto gray_buffer_pointer = tapasco::makeWrappedPointer(grayArr, WIDTH * HEIGHT * sizeof(unsigned char));

    auto red_buffer_pointer_in = tapasco::makeInOnly(red_buffer_pointer);
    auto green_buffer_pointer_in = tapasco::makeInOnly(green_buffer_pointer);
    auto blue_buffer_pointer_in = tapasco::makeInOnly(blue_buffer_pointer);
    auto gray_buffer_pointer_out = tapasco::makeOutOnly(gray_buffer_pointer);

    auto job = tapasco.launch(42, red_buffer_pointer_in, green_buffer_pointer_in, blue_buffer_pointer_in, gray_buffer_pointer_out);

    auto fpga_start = std::chrono::high_resolution_clock::now();
    job();
    auto fpga_stop = std::chrono::high_resolution_clock::now();

    int fpgaGrayOk = memcmp(gray_buffer_pointer_out.value.value, grayExpect, WIDTH * HEIGHT);
    if (fpgaGrayOk == 0) {
        std::cout << "FPGA Grayscale conversion was successful." << std::endl;
        std::cout << "FPGA time: " << std::chrono::duration_cast<std::chrono::microseconds>(fpga_stop - fpga_start).count() << " microsec." << std::endl;
    } else {
        std::cout << "FPGA Grayscale conversion unsuccessful." << std::endl;
        return 1;
    }

    std::cout << std::endl << "Passed!" << std::endl;

    return 0;
}
