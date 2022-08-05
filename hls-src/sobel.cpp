#include "sobel.h"
#include "ap_axi_sdata.h"

void sobel(unsigned char input_r[WIDTH * HEIGHT], unsigned char output_r[(WIDTH-2)*(HEIGHT-2)]) {
#pragma HLS array_reshape variable=input_r block factor=256

    LOOP1: for (int y = 1; y < HEIGHT-1; ++y) {

        LOOP2: for (int x = 1; x < WIDTH-1; ++x) {
#pragma HLS pipeline II=3

        	// tmp variables to avoid double read
        	unsigned char tmp0_0 = input_r[(y-1)*WIDTH+x-1];
        	unsigned char tmp0_3 = input_r[(y-1)*WIDTH+x+1];
        	unsigned char tmp3_0 = input_r[(y+1)*WIDTH+x-1];
        	unsigned char tmp3_3 = input_r[(y+1)*WIDTH+x+1];

            int gx = tmp0_0 - tmp0_3 + 2*input_r[y*WIDTH+x-1]
                     - 2*input_r[y*WIDTH+x+1] + tmp3_0 - tmp3_3;

            int gy = tmp0_0 + 2*input_r[(y-1)*WIDTH+x] + tmp0_3
                     - tmp3_0 - 2*input_r[(y+1)*WIDTH+x] - tmp3_3;

            int sum = ((gx < 0) ? -gx : gx) + ((gy < 0) ? -gy : gy);

            unsigned char result = (sum < 0) ? 0 : ((sum > 255) ? 255 : sum);

            output_r[(y-1)*(WIDTH-2)+(x-1)] = result;

        }

    }

}
