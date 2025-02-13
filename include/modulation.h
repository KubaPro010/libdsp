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
    complex hilbert_out;
    float *carrier_i;
    float *carrier_q;
    float *output;
} SSBModulator;

void init_fm_modulator(FMModulator *fm, float *input, float *output, float frequency, float deviation, float sample_rate);
void modulate_fm(FMModulator *fm);
inline void exit_fm_modulator(FMModulator *fm) {}

void init_ssb_modulator(SSBModulator *ssb, float *input, float *output, float frequency, int usb, float sample_rate);
void modulate_ssb(SSBModulator *ssb);
inline void exit_ssb_modulator(SSBModulator *ssb) {}