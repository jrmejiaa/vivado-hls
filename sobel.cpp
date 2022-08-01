#include "sobel.h"

void sobel(unsigned char input[WIDTH * HEIGHT], unsigned char output[(WIDTH-2)*(HEIGHT-2)]){
    for(int y = 1; y < HEIGHT-1; ++y){
        for(int x = 1; x < WIDTH-1; ++x){
            int gx = input[(y-1)*WIDTH+x-1] - input[(y-1)*WIDTH+x+1] + 2*input[y*WIDTH+x-1]
                     - 2 * input[y*WIDTH+x+1] + input[(y+1)*WIDTH+x-1] - input[(y+1)*WIDTH+x+1];
            int gy = input[(y-1)*WIDTH+x-1] + 2*input[(y-1)*WIDTH+x] + input[(y-1)*WIDTH+x+1]
                     - input[(y+1)*WIDTH+x-1] - 2 * input[(y+1)*WIDTH+x] - input[(y+1)*WIDTH+x+1];
            int sum = ((gx < 0) ? -gx : gx) + ((gy < 0) ? -gy : gy);
            unsigned char result = (sum < 0) ? 0 : ((sum > 255) ? 255 : sum);
            output[(y-1)*(WIDTH-2)+(x-1)] = result;
        }
    }
}
