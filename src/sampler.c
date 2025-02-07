#include "../include/filter.h"
#include "../include/sampler.h"

void init_decimator(Decimator* filter, float* input, float* output, int ratio, float sampleRate) {
    filter->ratio = ratio;
    filter->lpf.input = input;
    filter->output = output;
    filter->i = 0;
    init_lpf(&filter->lpf, input, output, 0.5f/ratio, 0.05f, sampleRate);
}

void decimate(Decimator* filter) {
    apply_biquad(&filter->lpf);
    filter->i++;
    if (filter->i >= filter->ratio) {
        filter->i = 0;
        *filter->output = *filter->lpf.output;
    }
}