#include <math.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#define DSP_VERSION 1.1

typedef struct
{
    float inphase;
    float quadrature;
} complex;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_2PI
#define M_2PI (M_PI * 2.0)
#endif