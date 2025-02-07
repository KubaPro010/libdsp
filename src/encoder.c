#include "../include/encoder.h"

void init_stereo_encoder(StereoEncoder *enc, float *input_l, float *input_r, float *output, float sample_rate){
    init_sine_oscillator(&enc->pilot_osc, &enc->pilot, 19000.0f, sample_rate);
    enc->input_l = input_l;
    enc->input_r = input_r;
    enc->output = output;
}

void stereo_encode(StereoEncoder *enc){
    compute_sine_oscillator_sin(&enc->pilot_osc);
    float pilot = *enc->pilot;
    compute_sine_oscillator_sin_multiplier(&enc->pilot_osc, 2.0f);
    float stereo_carrier = *enc->pilot;
    advance_sine_oscillator(&enc->pilot_osc);
    enc->output = ((*enc->input_l + *enc->input_r)/2)*0.45f;
    enc->output += enc->pilot * 0.09f;
    enc->output += (((*enc->input_l - *enc->input_r)/2)*stereo_carrier)*0.45f;
}