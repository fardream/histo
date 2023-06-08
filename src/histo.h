#ifndef GITHUB_COM_FARDREAM_HISTO_HISTO_H
#define GITHUB_COM_FARDREAM_HISTO_HISTO_H

#include <stddef.h>
#include <stdint.h>

#include <cstddef>

#ifdef __cplusplus
extern "C" {
#endif
void histo(const uint8_t *x, const float *v, const size_t n_f, const size_t n_r,
           const size_t nb, float *out);

void histo_8(const uint8_t *x, const float *v, const size_t n_f,
             const size_t n_r, const size_t nb, float *out);

float dot(const float *x, const float *y, const size_t n);

float dot8(const float *x, const float *y, const size_t n);

float dott(const float *x, const float *y, const size_t n);

#ifdef __cplusplus
}
#endif

#endif
