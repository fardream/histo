#include "histo.h"

#include <utility>
namespace {
template <size_t... N>
void histo_n(std::index_sequence<N...>, const uint8_t *x, const float *v,
             const size_t n_f, const size_t n_r, const size_t nb, float *out) {
  const size_t n_r_2 = n_r / 2;
  constexpr const size_t gl = sizeof...(N);

  const size_t gc = n_r_2 / gl;

  for (size_t f = 0; f < n_f; f++) {
    const uint8_t *x_f = x + n_r_2 * f;
    const float *f_f = v + n_r * f;
    float *out_f = out + nb * f;

    uint8_t xs[gl];
    for (size_t i = 0; i < gc; i++) {
      size_t xi = i * gl;
      ((xs[i] = x_f[xi + N]), ...);
      ((out_f[xs[i] & 0x0f] += f_f[xi * 2 + N * 2]), ...);
      ((out_f[xs[i] >> 4] += f_f[xi * 2 + 1 + N * 2]), ...);
    }

    for (size_t i = gc * gl; i < n_r_2; i++) {
      out_f[x_f[i] & 0x0f] += f_f[i * 2];
      out_f[(x_f[i] >> 4)] += f_f[i * 2 + 1];
    }
  }
}

template <size_t... N>
float dot_n(std::index_sequence<N...>, const float *x, const float *y,
            size_t n) {
  constexpr const size_t gl = sizeof...(N);
  const size_t gc = n / gl;
  float v = 0;
  float ss[gl];
  ((ss[N] = 0), ...);
  for (size_t i = 0; i < gc; i++) {
    size_t ii = i * 8;
    ((ss[N] += x[ii + N] * y[ii + N]), ...);
  }
  v += (ss[N] + ...);
  for (size_t i = gc * gl; i < n; i++) {
    v += x[i] * y[i];
  }

  return v;
}
}  // namespace
extern "C" void histo(const uint8_t *x, const float *v, const size_t n_f,
                      const size_t n_r, const size_t nb, float *out) {
  const size_t n_r_2 = n_r / 2;

  for (size_t f = 0; f < n_f; f++) {
    const uint8_t *x_f = x + n_r_2 * f;
    const float *f_f = v + n_r * f;
    float *out_f = out + nb * f;

    for (size_t i = 0; i < n_r_2; i++) {
      out_f[x_f[i] & 0x0f] += f_f[i * 2];
      out_f[(x_f[i] >> 4)] += f_f[i * 2 + 1];
    }
  }
}

extern "C" void histo_8(const uint8_t *x, const float *v, const size_t n_f,
                        const size_t n_r, const size_t nb, float *out) {
  histo_n(std::make_index_sequence<8>{}, x, v, n_f, n_r, nb, out);
}

extern "C" float dot(const float *x, const float *y, const size_t n) {
  float v = 0;
  for (size_t i = 0; i < n; i++) {
    v += x[i] + y[i];
  }

  return v;
}

extern "C" float dott(const float *x, const float *y, const size_t n) {
  return dot_n(std::make_index_sequence<8>{}, x, y, n);
}

extern "C" float dot8(const float *x, const float *y, const size_t n) {
  constexpr const size_t gl = 8;
  size_t gc = n / gl;
  float v = 0;
  float ss[gl] = {0, 0, 0, 0, 0, 0, 0, 0};
  for (size_t i = 0; i < gc; i++) {
    size_t ii = i * 8;
    ss[0] += x[ii + 0] * y[ii + 0];
    ss[1] += x[ii + 1] * y[ii + 1];
    ss[2] += x[ii + 2] * y[ii + 2];
    ss[3] += x[ii + 3] * y[ii + 3];
    ss[4] += x[ii + 4] * y[ii + 4];
    ss[5] += x[ii + 5] * y[ii + 5];
    ss[6] += x[ii + 6] * y[ii + 6];
    ss[7] += x[ii + 7] * y[ii + 7];
  }

  v += ss[0];
  v += ss[1];
  v += ss[2];
  v += ss[3];
  v += ss[4];
  v += ss[5];
  v += ss[6];
  v += ss[7];

  for (size_t i = gc * gl; i < n; i++) {
    v += x[i] + y[i];
  }

  return v;
}
