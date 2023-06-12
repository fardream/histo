#include <benchmark/benchmark.h>
#include <math.h>

#include <cstdio>
#include <vector>

void doexp(const float vals[8], float outs[8]) {
  outs[0] = __builtin_expf(vals[0]);
  outs[1] = __builtin_expf(vals[1]);
  outs[2] = __builtin_expf(vals[2]);
  outs[3] = __builtin_expf(vals[3]);
  outs[4] = __builtin_expf(vals[4]);
  outs[5] = __builtin_expf(vals[5]);
  outs[6] = __builtin_expf(vals[6]);
  outs[7] = __builtin_expf(vals[7]);
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
