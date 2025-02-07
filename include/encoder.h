typedef struct
{
    Oscillator pilot_osc;
    float *pilot;
    float *stereo_carrier;
    float *input_l;
    float *input_r;
    float *output;
} StereoEncoder;
