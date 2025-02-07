typedef struct {
    float b0, b1, b2;
    float a1, a2;
    float x1, x2;
    float y1, y2;
    float *input;
    float *output;
} BiquadFilter;

void reset_biquad(BiquadFilter* filter);
void init_lpf(BiquadFilter* filter, float* input, float* output, float cutoffFreq, float qFactor, float sampleRate);
void init_hpf(BiquadFilter* filter, float* input, float* output, float cutoffFreq, float qFactor, float sampleRate);
void init_preemphasis(BiquadFilter *biquad, float *input, float *output, float tau, float sample_rate);
void init_deemphasis(BiquadFilter *biquad, float *input, float *output, float tau, float sample_rate);
void apply_biquad(BiquadFilter* filter);