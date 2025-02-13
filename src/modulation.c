#include <stdlib.h>
#include "../include/oscillators.h"
#include "../include/common.h"
#include "../include/transformer.h"
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
    if(ssb->usb) {
        *ssb->output = *ssb->carrier_i * ssb->hilbert_out.inphase + *ssb->carrier_q * ssb->hilbert_out.quadrature;
    } else {
        *ssb->output = *ssb->carrier_i * ssb->hilbert_out.inphase - *ssb->carrier_q * ssb->hilbert_out.quadrature;
    }
}