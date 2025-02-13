#define HILBERT_TAPS 95
typedef struct {
    float coeffs[HILBERT_TAPS];
    float delay[HILBERT_TAPS];
    int index;
    float *input;
    complex *output;
} HilbertTransformer;

void init_hilbert(HilbertTransformer* filter, float* input, complex* output);
void hilbert(HilbertTransformer* filter);
inline void exit_hilbert(HilbertTransformer* filter) {}