#ifndef WIDTH
    #define WIDTH 512
#endif

#ifndef HEIGHT
    #define HEIGHT 512
#endif

void sobel(unsigned char input[WIDTH * HEIGHT], unsigned char output[(WIDTH - 2) * (HEIGHT - 2)]);
