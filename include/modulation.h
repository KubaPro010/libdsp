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

typedef struct
{
    BiquadFilter lpf;
    float *input;
} AMDemodulator;

typedef struct
{
    complex *input;
    float *output_frequency;
    float prev_phase;
    float sample_rate;
} FMDemodulator;

void init_am_demod(AMDemodulator *am, float *input, float *output, float lpf_cutoff, float sample_rate);
void am_demod(AMDemodulator *am);
inline void exit_am_demod(AMDemodulator *am) {}

void init_fm_demod(FMDemodulator *fm, complex *input, float *output_frequency, float sample_rate);
void fm_demod(FMDemodulator *fm);
inline void exit_fm_demod(FMDemodulator *fm) {}