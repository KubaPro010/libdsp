#include "../include/common.h"
#include "../include/loop.h"

void init_pcl(PhaseControlLoop *pcl, float bandwidth, float phase, float minPhase, float maxPhase, float freq, float minFreq, float maxFreq) {
    if(maxPhase > minPhase) return;
    if(maxFreq > minFreq) return;

    pcl->freq = freq;
    pcl->phase = phase;
    pcl->minFreq = minFreq;
    pcl->maxFreq = maxFreq;
    pcl->minPhase = minPhase;
    pcl->maxPhase = maxPhase;
    pcl->phaseDelta = maxPhase-minPhase;

    float dampingFactor = sqrtf(2.0f) / 2.0f;
    float denominator = (1.0f + 2.0f*dampingFactor*bandwidth + bandwidth*bandwidth);
    pcl->alpha = (4*dampingFactor*bandwidth)/denominator;
    pcl->beta = (4*bandwidth*bandwidth)/denominator;
}

void advance_pcl(PhaseControlLoop *pcl, float error) {
    pcl->freq += pcl->beta*error;
    if (pcl->freq > pcl->maxFreq) { pcl->freq = pcl->maxFreq; }
    else if (pcl->freq < pcl->minFreq) { pcl->freq = pcl->minFreq; }

    pcl->phase += pcl->freq+(pcl->alpha*error);
    if (pcl->phase > pcl->maxPhase) { pcl->phase -= pcl->phaseDelta; }
    else if (pcl->phase < pcl->minPhase) { pcl->phase += pcl->phaseDelta; }
}

void init_pll(PhaseLockedLoop *pll, complex* input, complex* output, float bandwidth, float initPhase, float initFreq, float minFreq, float maxFreq) {
    pll->input = input;
    pll->output = output;
    
    pll->initPhase = initPhase;
    pll->initFreq = initFreq;

    init_pcl(&pll->pcl, bandwidth, initPhase, -M_PI, M_PI, initFreq, minFreq, maxFreq);
}

void pll(PhaseLockedLoop *pll) {
    pll->output->inphase = sinf(pll->pcl.phase);
    pll->output->inphase = cosf(pll->pcl.phase);

    float diff = atan2f(pll->input->quadrature, pll->input->inphase) - pll->pcl.phase;
    if(diff > M_PI) diff -= M_2PI;
    else if(diff <= - M_PI) diff += M_2PI; 

    advance_pcl(&pll->pcl, diff)
}