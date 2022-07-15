#ifndef WIDTH
#define WIDTH 512
#endif

#ifndef HEIGHT
#define HEIGHT 512
#endif

void grayscale(unsigned char red[WIDTH * HEIGHT], unsigned char green[WIDTH * HEIGHT],
               unsigned char blue[WIDTH * HEIGHT], unsigned char output[WIDTH * HEIGHT]);

unsigned char convert_to_grayscale(unsigned char red, unsigned char green, unsigned char blue);