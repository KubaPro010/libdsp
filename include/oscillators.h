typedef struct {
    float phase;
    float phase_increment;
    float sample_rate;
    float *output;
    float *output2;
} Oscillator;

typedef struct {
    float *sine_table;
    float *cosine_table;
    int table_idx;
    int max_table_idx;
    float frequency;
    float sample_rate;
    float *output_sin;
    float *output_cos;
} TableOscillator;

void init_sine_oscillator(Oscillator *osc, float *output, float *output2, float frequency, float sample_rate);
void change_sine_oscillator_frequency(Oscillator *osc, float frequency);
void compute_sine_oscillator_sin(Oscillator *osc);
void compute_sine_oscillator_cos(Oscillator *osc);
void compute_sine_oscillator_sin_multiplier(Oscillator *osc, float multiplier);
void compute_sine_oscillator_cos_multiplier(Oscillator *osc, float multiplier);
void advance_sine_oscillator(Oscillator *osc);
inline void exit_sine_oscillator(Oscillator *osc) {}

// Table Oscillator needs to properly exit
void init_table_oscillator(TableOscillator *osc, float *output_sin, float *output_cos, float frequency, float sample_rate);
void compute_table_oscillator(TableOscillator *osc);
void advance_table_oscillator(TableOscillator *osc);
void exit_table_oscillator(TableOscillator *osc);
