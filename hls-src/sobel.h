#ifndef WIDTH
    #define WIDTH 512
#endif

#ifndef HEIGHT
    #define HEIGHT 512
#endif

#include "ap_int.h"

typedef ap_uint<8> d_io;
typedef ap_uint<9> d_loidx;
typedef ap_uint<8> d_arval;
typedef ap_int<9>  d_sub;
typedef ap_int<11> d_g;
typedef ap_uint<11> d_sum;

void sobel(unsigned char input[WIDTH * HEIGHT], unsigned char output[(WIDTH - 2) * (HEIGHT - 2)]);
