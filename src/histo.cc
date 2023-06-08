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
