typedef struct
{
    float alpha;
    float beta;
    float phase;
    float minPhase;
    float maxPhase;
    float phaseDelta;
    float freq;
    float minFreq;
    float maxFreq;
} PhaseControlLoop;

typedef struct
{
    PhaseControlLoop pcl;
    float bandwidth;
    float initPhase;
    float initFreq;
    float minFreq;
    float maxFreq;
    complex* input;
    complex* output;
} PhaseLockedLoop;


void init_pcl(PhaseControlLoop *pcl, float bandwidth, float phase, float minPhase, float maxPhase, float freq, float minFreq, float maxFreq);
void advance_pcl(PhaseControlLoop *pcl, float error);
inline void exit_pcl(PhaseControlLoop *pcl);
void init_pll(PhaseLockedLoop *pll, complex* input, complex* output, float bandwidth, float initPhase, float initFreq, float minFreq, float maxFreq);
void pll(PhaseLockedLoop *pll);
inline void exit_pll(PhaseLockedLoop *pll) {exit_pcl(&pll->pcl)}