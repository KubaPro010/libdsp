#define HILBERT_TAPS 95
typedef struct {
    float coeffs[HILBERT_TAPS];
    float delay[HILBERT_TAPS];
    int index;
    float *input;
    float *output_i;
    float *output_q;
} HilbertTransformer;

void init_hilbert(HilbertTransformer* filter, float* input, float* output_i, float* output_q);
void hilbert(HilbertTransformer* filter);
