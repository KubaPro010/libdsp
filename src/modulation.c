#include <stdlib.h>
#include "../include/oscillators.h"
#include "../include/common.h"
#include "../include/transformer.h"
#include "../include/filter.h"
#include "../include/modulation.h"

void init_fm_modulator(FMModulator *fm, float *input, float *output, float frequency, float deviation, float sample_rate) {
    init_sine_oscillator(&fm->osc, output, NULL, frequency, sample_rate);
    fm->input = input;
    fm->output = output;
    fm->frequency = frequency;
    fm->deviation = deviation;
}

void modulate_fm(FMModulator *fm) {
    float mod = *fm->input * fm->deviation;
    change_sine_oscillator_frequency(&fm->osc, fm->frequency + mod);
    compute_sine_oscillator_sin(&fm->osc);
    advance_sine_oscillator(&fm->osc);
}

void init_ssb_modulator(SSBModulator *ssb, float *input, float *output, float frequency, int usb, float sample_rate) {
    init_table_oscillator(&ssb->osc, ssb->carrier_i, ssb->carrier_q, frequency, sample_rate);
    init_hilbert(&ssb->hilbert, input, &ssb->hilbert_out);
    ssb->output = output;
    ssb->usb = usb;
}

void modulate_ssb(SSBModulator *ssb) {
    compute_table_oscillator(&ssb->osc);
    advance_table_oscillator(&ssb->osc);
    hilbert(&ssb->hilbert);

    *ssb->output = ssb->usb
        ? (*ssb->carrier_i * ssb->hilbert_out.inphase + *ssb->carrier_q * ssb->hilbert_out.quadrature)
        : (*ssb->carrier_i * ssb->hilbert_out.inphase - *ssb->carrier_q * ssb->hilbert_out.quadrature);
}


void init_am_demod(AMDemodulator *am, float *input, float *output, float lpf_cutoff, float sample_rate) {
    am->input = input;
    init_lpf(&am->lpf, NULL, output, lpf_cutoff, 10.0f, sample_rate);
}

void am_demod(AMDemodulator *am) {
    float lpf_in = fabsf(*am->input);
    am->lpf.input = &lpf_in;
    apply_biquad(&am->lpf);
}

void init_fm_demod(FMDemodulator *fm, complex *input, float *output_frequency, float sample_rate) {
    fm->input = input;
    fm->output_frequency = output_frequency;
    fm->prev_phase = 0.0f;
    fm->sample_rate = sample_rate;
}

void fm_demod(FMDemodulator *fm) {
    float phase = atan2f(fm->input->quadrature, fm->input->inphase);
    float phase_diff = phase - fm->prev_phase;

    if(phase_diff > M_PI) phase_diff -= M_2PI;
    if(phase_diff < -M_PI) phase_diff += M_2PI;

    *fm->output_frequency = (phase_diff / M_2PI)*fm->sample_rate;
    fm->prev_phase = phase;
}