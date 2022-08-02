#include <iostream>
#include <fstream>
#include <cstring>
#include <chrono>
#include <tapasco.hpp>

#include "../hls-src/sobel.cpp"

int main(int argc, char const *argv[])
{
    if(argc != 5) {
        std::cout << "Usage: ./sobel-launch <gray.data> <sobel.data>" << std::endl;
        return -1;
    }

    tapasco::Tapasco tapasco;

    unsigned char grayArr[WIDTH * HEIGHT];
    unsigned char sobelExpect[(WIDTH-2) * (HEIGHT-2)];

    std::ifstream grayIn(argv[1]);
    std::ifstream sobelIn(argv[2]);

    grayIn.read((char*) grayArr, WIDTH * HEIGHT);
    sobelIn.read((char*) sobelExpect, (WIDTH-2) * (HEIGHT-2));

    grayIn.close();
    sobelIn.close();

    /* CPU */

    std::cout << "Start CPU Sobel conversion..." << std::endl;

    unsigned char cpuSobelArr[(WIDTH-2) * (HEIGHT-2)];
    auto cpu_start = std::chrono::high_resolution_clock::now();
    sobel(grayArr, cpuSobelArr);
    auto cpu_stop = std::chrono::high_resolution_clock::now();

    int cpuSobelOk = memcmp(cpuSobelArr, sobelExpect, (WIDTH-2) * (HEIGHT-2));
    if (cpuSobelOk == 0) {
        std::cout << "CPU Sobel conversion was successful." << std::endl;
        std::cout << "CPU time: " << std::chrono::duration_cast<std::chrono::microseconds>(cpu_stop - cpu_start).count() << " microsec." << std::endl;
    } else {
        std::cout << "CPU Sobel conversion unsuccessful." << std::endl;
        return 1;
    }

    /* FPGA */

    std::cout << std::endl << "Start FPGA Sobel conversion..." << std::endl;

    unsigned char fpgaSobelArr[(WIDTH-2) * (HEIGHT-2)];

    auto gray_buffer_pointer = tapasco::makeWrappedPointer(grayArr, WIDTH * HEIGHT * sizeof(unsigned char));
    auto sobel_buffer_pointer = tapasco::makeWrappedPointer(fpgaSobelArr, (WIDTH-2) * (HEIGHT-2) * sizeof(unsigned char));

    auto gray_buffer_pointer_in = tapasco::makeInOnly(gray_buffer_pointer);
    auto sobel_buffer_pointer_out = tapasco::makeOutOnly(sobel_buffer_pointer);

    auto job = tapasco.launch(42, gray_buffer_pointer_in, sobel_buffer_pointer_out);

    auto fpga_start = std::chrono::high_resolution_clock::now();
    job();
    auto fpga_stop = std::chrono::high_resolution_clock::now();

    int fpgaGrayOk = memcmp(fpgaSobelArr, sobelExpect, (WIDTH-2) * (HEIGHT-2));
    if (fpgaGrayOk == 0) {
        std::cout << "FPGA Sobel conversion was successful." << std::endl;
        std::cout << "FPGA time: " << std::chrono::duration_cast<std::chrono::microseconds>(fpga_stop - fpga_start).count() << " microsec." << std::endl;
    } else {
        std::cout << "FPGA Sobel conversion unsuccessful." << std::endl;
        return 1;
    }

    std::cout << std::endl << "Passed!" << std::endl;

    return 0;
}
