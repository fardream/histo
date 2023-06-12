#include <benchmark/benchmark.h>
#include <math.h>

#include <cstdio>
#include <vector>

void doexp(const float *vals, float *outs) {
  for (int i = 0; i < 8; i++) {
    outs[i] = __builtin_expf(vals[i]);
  }
}

static void BM_expf(benchmark::State &state) {
  float out[8] = {};
  for (auto _ : state) {
    for (float num = -10; num < 10; num += 0.01) {
      float x[8] = {num,     num + 1, num + 2, num + 3,
                    num + 4, num + 5, num + 6, num + 7};
      doexp(x, out);
      if (out[0] != expf(num)) {
        state.SkipWithError("Failed to read data!");
      }
    }
  }
}

// Register the function as a benchmark
BENCHMARK(BM_expf);
// Run the benchmark
BENCHMARK_MAIN();
