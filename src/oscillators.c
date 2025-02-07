#include "../include/oscillators.h"
#include "../include/constants.h"

void init_sine_oscillator(Oscillator *osc, float *output, float frequency, float sample_rate) {
    osc->phase = 0.0f;
    osc->phase_increment = (M_2PI * frequency) / sample_rate;
    osc->sample_rate = sample_rate;
    osc->output = output;
}

void change_sine_oscillator_frequency(Oscillator *osc, float frequency) {
    osc->phase_increment = (M_2PI * frequency) / osc->sample_rate;
}

void compute_sine_oscillator_sin(Oscillator *osc) {
    *osc->output = sinf(osc->phase);
}

void compute_sine_oscillator_cos(Oscillator *osc) {
    *osc->output = cosf(osc->phase);
}

void compute_sine_oscillator_sin_multiplier(Oscillator *osc, float multiplier) {
    *osc->output = sinf(osc->phase*multiplier);
}

void compute_sine_oscillator_cos_multiplier(Oscillator *osc, float multiplier) {
    *osc->output = cosf(osc->phase*multiplier);
}

void advance_sine_oscillator(Oscillator *osc) {
    osc->phase = fmodf(osc->phase + osc->phase_increment, M_2PI);
}

void exit_sine_oscillator(Oscillator *osc) {
    
}

void init_table_oscillator(TableOscillator *osc, float *output_sin, float *output_cos, float frequency, float sample_rate) {
    osc->table_idx = 0;
    osc->frequency = frequency;
    osc->sample_rate = sample_rate;
    osc->output_sin = output_sin;
    osc->output_cos = output_cos;
    if (frequency <= 0.0f) frequency = 1.0f;
    osc->max_table_idx = sample_rate*(1/frequency);

    osc->sine_table = (float *)malloc(osc->max_table_idx * sizeof(float));
    osc->cosine_table = (float *)malloc(osc->max_table_idx * sizeof(float));
    
    float w = M_2PI * frequency;
    osc->sine_table[0] = 0.0f;
    osc->cosine_table[0] = 1.0f;
    
    for(int i = 1; i < osc->max_table_idx; i++) {
        osc->sine_table[i] = sinf(w*i/sample_rate);
        osc->cosine_table[i] = cosf(w*i/sample_rate);
    }
}

void compute_table_oscillator(TableOscillator *osc) {
    *osc->output_sin = osc->sine_table[osc->table_idx];
    *osc->output_cos = osc->cosine_table[osc->table_idx];
}

void advance_table_oscillator(TableOscillator *osc) {
    osc->table_idx = (osc->table_idx + 1) % osc->max_table_idx;
}

void exit_table_oscillator(TableOscillator *osc) {
    free(osc->sine_table);
    osc->sine_table = NULL;
    free(osc->cosine_table);
    osc->cosine_table = NULL;
}