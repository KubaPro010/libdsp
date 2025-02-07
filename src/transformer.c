#include "../include/constants.h"
#include "../include/transformer.h"

void compute_hilbert_coeffs(float* coeffs, int taps) {
    int mid = taps / 2;
    for (int i = 0; i < taps; i++) {
        if ((i - mid) % 2 == 0) {
            coeffs[i] = 0.0f;
        } else {
            coeffs[i] = 2.0f / (M_PI * (i - mid));
        }
    }
}

void init_hilbert(HilbertTransformer* filter, float* input, float* output_i, float* output_q) {
    compute_hilbert_coeffs(filter->coeffs, HILBERT_TAPS);
    memset(filter->delay, 0, sizeof(filter->delay));
    filter->index = 0;
    filter->input = input;
    filter->output_i = output_i;
    filter->output_q = output_q;
}

void hilbert(HilbertTransformer* filter) {
    filter->delay[filter->index] = *filter->input;

    float i_sum = 0.0f;
    float q_sum = 0.0f;

    int coeff_index = 0;
    for (int i = filter->index; coeff_index < HILBERT_TAPS; coeff_index++) {
        i_sum += filter->delay[i] * (coeff_index == HILBERT_TAPS / 2 ? 1.0f : 0.0f);
        q_sum += filter->delay[i] * filter->coeffs[coeff_index];

        i = (i > 0) ? i - 1 : HILBERT_TAPS - 1;
    }

    filter->index = (filter->index + 1) % HILBERT_TAPS;

    *filter->output_i = i_sum;
    *filter->output_q = q_sum;
}