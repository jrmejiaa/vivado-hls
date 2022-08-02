#include "grayscale.h"
#include <stdint.h>

void grayscale(unsigned char red[WIDTH * HEIGHT], unsigned char green[WIDTH * HEIGHT],
               unsigned char blue[WIDTH * HEIGHT], unsigned char output[WIDTH * HEIGHT]){
    for(int i=0; i<WIDTH*HEIGHT; ++i){
        output[i] = convert_to_grayscale(red[i], green[i], blue[i]);
    }
}

// TEST


unsigned char convert_to_grayscale(unsigned char red, unsigned char green, unsigned char blue){
    uint32_t red_factor   = 0b00000000000110101110000101000111;
    uint32_t green_factor = 0b00000000010111000010100011110101;
    uint32_t blue_factor  = 0b00000000000010001111010111000010;
    uint32_t red_val   = ((uint32_t) red);
    uint32_t green_val = ((uint32_t) green);
    uint32_t blue_val  = ((uint32_t) blue);
    uint32_t sum = red_val * red_factor + green_val * green_factor + blue_val * blue_factor;
    return (sum >> 31) ? 255 : ((char) (sum >> 23));
}
