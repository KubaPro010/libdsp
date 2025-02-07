typedef struct {
    Oscillator osc;
    float frequency;
    float deviation;
    float *input;
    float *output;
} FMModulator;

typedef struct {
    TableOscillator osc;
    HilbertTransformer hilbert;
    int usb;
    float *signal_i;
    float *signal_q;
    float *carrier_i;
    float *carrier_q;
    float *output;
} SSBModulator;

void init_fm_modulator(FMModulator *fm, float *input, float *output, float frequency, float deviation, float sample_rate);
void modulate_fm(FMModulator *fm);
inline void exit_fm_modulator(FMModulator *fm) {}