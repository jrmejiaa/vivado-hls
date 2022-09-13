#include "sobel.h"

void sobel(unsigned char input_r[WIDTH * HEIGHT], unsigned char output_r[(WIDTH-2)*(HEIGHT-2)]) {
//#pragma HLS array_reshape variable=input_r block factor=2
//#pragma HLS array_partition variable=input_r block factor=32

    LOOP1: for (d_loidx y = 1; y < HEIGHT-1; ++y) {

        LOOP2: for (d_loidx x = 1; x < WIDTH-1; ++x) {
// #pragma HLS pipeline II=1

        	// tmp variables to avoid double read
        	d_arval tmp0_0 = input_r[(y-1)*WIDTH+x-1];
        	d_arval tmp0_3 = input_r[(y-1)*WIDTH+x+1];
        	d_arval tmp3_0 = input_r[(y+1)*WIDTH+x-1];
        	d_arval tmp3_3 = input_r[(y+1)*WIDTH+x+1];
			d_arval tmp2_0 = input_r[y*WIDTH+x-1];
			d_arval tmp2_3 = input_r[y*WIDTH+x+1];
			d_arval tmp0_2 = input_r[(y-1)*WIDTH+x];
			d_arval tmp3_2 = input_r[(y+1)*WIDTH+x];

			d_sub tmp_a = tmp0_0 - tmp3_3;
			d_sub tmp_b = tmp0_3 - tmp3_0;

        	d_g gx = tmp_a - tmp_b + 2*(tmp2_0 - tmp2_3);
        	d_g gy = tmp_a + tmp_b + 2*(tmp0_2 - tmp3_2);

        	d_sum sum = ((gx < 0) ? d_g(-gx) : gx) + ((gy < 0) ? d_g(-gy) : gy);

        	d_io result = (sum > 255) ? d_sum(255) : sum;

            output_r[(y-1)*(WIDTH-2)+(x-1)] = result;

        }

    }

}
