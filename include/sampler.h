typedef struct
{
    BiquadFilter lpf;
    int ratio;
    int i;
    float *output;
} Decimator;

void init_decimator(Decimator *filter, float *input, float *output, int ratio, float sampleRate);
void decimate(Decimator *filter);
