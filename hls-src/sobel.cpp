#include "sobel.h"
#include <iostream>


void sobel(unsigned char input_r[WIDTH * HEIGHT], unsigned char output_r[(WIDTH-2)*(HEIGHT-2)]) {

	d_arval val_buffer[1024];
	#pragma HLS array_partition variable=val_buffer complete dim=0
	bool val_buffer_vld[1024];
	#pragma HLS array_partition variable=val_buffer_vld complete

	d_arval val_buffer_ext[3];
	#pragma HLS array_partition variable=val_buffer complete dim=0
	bool val_buffer_vld_ext[3];
	#pragma HLS array_partition variable=val_buffer_vld complete

	for (int i = 0; i < 1024; ++i) {
		#pragma HLS unroll
		val_buffer_vld[i] = 0;
	}
	for (int i = 0; i < 3; ++i) {
		#pragma HLS unroll
		val_buffer_vld_ext[i] = 0;
	}

	val_buffer[1] = input_r[2*WIDTH+1];
	val_buffer_vld[1] = 1;
	val_buffer[2] = input_r[2*WIDTH];
	val_buffer_vld[2] = 1;

	val_buffer_ext[1] = input_r[1];
	val_buffer_vld_ext[1] = 1;
	val_buffer_ext[2] = input_r[0];
	val_buffer_vld_ext[2] = 1;

	WARMUP_LOOP: for (d_loidx x = 1; x < WIDTH-1; ++x) {
		#pragma HLS pipeline II=2

		if (!val_buffer_vld[0]) {
			val_buffer[0] = input_r[2*WIDTH+x+1];
			val_buffer_vld[0] = 1;
		}

		if (!val_buffer_vld[512]) {
			val_buffer[512] = input_r[1*WIDTH+x+1];
			val_buffer_vld[512] = 1;
		}
		if (!val_buffer_vld[514]) {
			val_buffer[514] = input_r[1*WIDTH+x-1];
			val_buffer_vld[514] = 1;
		}

		if (!val_buffer_vld_ext[0]) {
			val_buffer_ext[0] = input_r[x+1];
			val_buffer_vld_ext[0] = 1;
		}

		d_arval val2_2 = val_buffer[0];
		d_arval val2_1 = val_buffer[1];
		d_arval val2_0 = val_buffer[2];

		d_arval val1_2 = val_buffer[512];
		d_arval val1_0 = val_buffer[514];

		d_arval val0_2 = val_buffer_ext[0];
		d_arval val0_1 = val_buffer_ext[1];
		d_arval val0_0 = val_buffer_ext[2];

		d_sub tmp_a = val0_0 - val2_2;
		d_sub tmp_b = val0_2 - val2_0;

		d_g gx = tmp_a - tmp_b + 2*(val1_0 - val1_2);
		d_g gy = tmp_a + tmp_b + 2*(val0_1 - val2_1);

		d_sum sum = ((gx < 0) ? d_g(-gx) : gx) + ((gy < 0) ? d_g(-gy) : gy);

		d_io result = (sum > 255) ? d_sum(255) : sum;

		output_r[x-1] = result;

		// Buffer shifting
		if (x < WIDTH-2) {
			for (int i = 1; i >= 0; --i) {
				#pragma HLS unroll
				val_buffer_ext[i+1] = val_buffer_ext[i];
				val_buffer_vld_ext[i+1] = val_buffer_vld_ext[i];
			}
			val_buffer_ext[0] = val_buffer[1023];
			val_buffer_vld_ext[0] = val_buffer_vld[1023];
			for (int i = 1022; i >= 0; --i) {
				#pragma HLS unroll
				val_buffer[i+1] = val_buffer[i];
				val_buffer_vld[i+1] = val_buffer_vld[i];
			}
			val_buffer_vld[0] = 0;
		}
	}

    LOOP1: for (d_loidx y = 2; y < HEIGHT-1; ++y) {

		// Buffer shifting end of row
		val_buffer_ext[0] = val_buffer[1021];
		val_buffer_vld_ext[0] = val_buffer_vld[1021];
		val_buffer_ext[1] = val_buffer[1022];
		val_buffer_vld_ext[1] = val_buffer_vld[1022];
		val_buffer_ext[2] = val_buffer[1023];
		val_buffer_vld_ext[2] = val_buffer_vld[1023];
		for (int i = 1020; i >= 0; --i) {
			#pragma HLS unroll
			val_buffer[i+3] = val_buffer[i];
			val_buffer_vld[i+3] = val_buffer_vld[i];
		}
		val_buffer_vld[0] = 0;
		val_buffer_vld[1] = 0;
		val_buffer_vld[2] = 0;

		val_buffer[2] = input_r[(y+1)*WIDTH];
		val_buffer_vld[2] = 1;

        LOOP2: for (d_loidx x = 1; x < WIDTH-1; ++x) {
			#pragma HLS pipeline II=1

			if (!val_buffer_vld[0]) {
				val_buffer[0] = input_r[(y+1)*WIDTH+x+1];
				val_buffer_vld[0] = 1;
			}
			if (!val_buffer_vld[1]) {
				val_buffer[1] = input_r[(y+1)*WIDTH+x];
				val_buffer_vld[1] = 1;
			}

        	d_arval val2_2 = val_buffer[0];
			d_arval val2_1 = val_buffer[1];
        	d_arval val2_0 = val_buffer[2];

			d_arval val1_2 = val_buffer[512];
			d_arval val1_0 = val_buffer[514];

        	d_arval val0_2 = val_buffer_ext[0];
			d_arval val0_1 = val_buffer_ext[1];
        	d_arval val0_0 = val_buffer_ext[2];

			d_sub tmp_a = val0_0 - val2_2;
			d_sub tmp_b = val0_2 - val2_0;

        	d_g gx = tmp_a - tmp_b + 2*(val1_0 - val1_2);
        	d_g gy = tmp_a + tmp_b + 2*(val0_1 - val2_1);

        	d_sum sum = ((gx < 0) ? d_g(-gx) : gx) + ((gy < 0) ? d_g(-gy) : gy);

        	d_io result = (sum > 255) ? d_sum(255) : sum;

            output_r[(y-1)*(WIDTH-2)+(x-1)] = result;

			// Buffer shifting
			if (x < WIDTH-2) {
				for (int i = 1; i >= 0; --i) {
					#pragma HLS unroll
					val_buffer_ext[i+1] = val_buffer_ext[i];
					val_buffer_vld_ext[i+1] = val_buffer_vld_ext[i];
				}
				val_buffer_ext[0] = val_buffer[1023];
				val_buffer_vld_ext[0] = val_buffer_vld[1023];
				for (int i = 1022; i >= 0; --i) {
					#pragma HLS unroll
					val_buffer[i+1] = val_buffer[i];
					val_buffer_vld[i+1] = val_buffer_vld[i];
				}
				val_buffer_vld[0] = 0;
			}
        }
    }

}
