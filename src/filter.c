#include "../include/filter.h"
#include "../include/common.h"

void reset_biquad(BiquadFilter* filter) {
    filter->y2 = 0;
    filter->y1 = 0;
    filter->x2 = 0;
    filter->x1 = 0;
}

void init_lpf(BiquadFilter* filter, float* input, float* output, float cutoffFreq, float qFactor, float sampleRate) {
    filter->input = input;
    filter->output = output;

    float x = (cutoffFreq * M_2PI) / sampleRate;
    float sinX = sin(x);
    float y = sinX / (qFactor*2.0f);
    float cosX = cos(x);
    float z = (1.0f-cosX)/2.0f;

    float _a0 = y + 1.0f;
    float _a1 = cosX * -2.0f;
    float _a2 = 1.0f - y;
    float _b0 = z;
    float _b1 = 1.0f - cosX;
    float _b2 = z;

    filter->b0 = _b0/_a0;
    filter->b1 = _b1/_a0;
    filter->b2 = _b2/_a0;
    filter->a1 = -_a1/_a0;
    filter->a2 = -_a2/_a0;


    reset_biquad(filter);
}

void init_hpf(BiquadFilter* filter, float* input, float* output, float cutoffFreq, float qFactor, float sampleRate) {
    filter->input = input;
    filter->output = output;

    float x = (cutoffFreq * M_2PI) / sampleRate;
    float sinX = sinf(x);
    float y = sinX / (qFactor*2.0f);
    float cosX = cosf(x);
    float z = (1.0f-cosX)/2.0f;

    float _a0 = y + 1.0f;
    float _a1 = cosX * -2.0f;
    float _a2 = 1.0f - y;
    float _b0 = 1.0f - z;
    float _b1 = cosX * -2.0f;
    float _b2 = 1.0f - z;

    filter->b0 = _b0/_a0;
    filter->b1 = _b1/_a0;
    filter->b2 = _b2/_a0;
    filter->a1 = -_a1/_a0;
    filter->a2 = -_a2/_a0;

    reset_biquad(filter);
}

void init_preemphasis(BiquadFilter *biquad, float *input, float *output, float tau, float sample_rate) {
    float A = 1.0 + 2.0 * tau * sample_rate;
    float B = 1.0 - 2.0 * tau * sample_rate;

    biquad->b0 = 1.0/A;
    biquad->b1 = 1.0/A;
    biquad->b2 = 0.0;
    biquad->a1 = B/A;
    biquad->a2 = 0.0;

    reset_biquad(biquad);

    biquad->input = input;
    biquad->output = output;
}

void apply_biquad(BiquadFilter* filter) {
    float out = filter->b0**filter->input + filter->b1*filter->x1 + filter->b2*filter->x2 + filter->y1*filter->a1 + filter->y2*filter->a2;
    filter->y2 = filter->y1;
    filter->y1 = out;
    filter->x2 = filter->x1;
    filter->x1 = *filter->input;
    *filter->output = out;
}