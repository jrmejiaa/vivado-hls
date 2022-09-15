#ifndef WIDTH
#define WIDTH 512
#endif

#ifndef HEIGHT
#define HEIGHT 512
#endif

#include <ap_int.h>

typedef ap_uint<32> d_dflt;
typedef ap_uint<23> d_fct;
typedef ap_uint<31> d_pdt;

void grayscale(unsigned char red[WIDTH * HEIGHT], unsigned char green[WIDTH * HEIGHT],
               unsigned char blue[WIDTH * HEIGHT], unsigned char output[WIDTH * HEIGHT]);

unsigned char convert_to_grayscale(unsigned char red, unsigned char green, unsigned char blue);
