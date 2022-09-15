#include "grayscale.h"

void grayscale(unsigned char red[WIDTH * HEIGHT], unsigned char green[WIDTH * HEIGHT],
               unsigned char blue[WIDTH * HEIGHT], unsigned char output[WIDTH * HEIGHT]){
    for(int i=0; i<WIDTH*HEIGHT; ++i){
		#pragma HLS unroll factor=2
		#pragma HLS pipeline II=1
        output[i] = convert_to_grayscale(red[i], green[i], blue[i]);
    }
}

unsigned char convert_to_grayscale(unsigned char red, unsigned char green, unsigned char blue){
	d_fct red_factor   = 0b00110101110000101000111;
	d_fct green_factor = 0b10111000010100011110101;
	d_fct blue_factor  = 0b00010001111010111000010;
	d_fct red_val   = ((d_fct) red);
	d_fct green_val = ((d_fct) green);
	d_fct blue_val  = ((d_fct) blue);

	d_pdt red_product = red_val * red_factor;
	d_pdt green_product = green_val * green_factor;
	d_pdt blue_product = blue_val * blue_factor;

	d_dflt sum = red_product + green_product + blue_product;

    return (sum >> 31) ? 255 : ((char) (sum >> 23));
}
