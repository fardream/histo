#include <benchmark/benchmark.h>
#include <math.h>

#include <cstdio>
#include <vector>

thread_local std::vector<float> vs;

constexpr const int N = 1000000000;

void doexp(const float *vals, float *outs) {
  for (int i = 0; i < 8; i++) {
    outs[i] = expf(vals[i]);
  }
}

static void DoSetup(const benchmark::State &state) {
  vs.resize(N, 0);
  for (int i = 0; i < N; i++) {
    vs[i] = -(float)(i);
    vs[i] = vs[i] < 0 ? -vs[i] : vs[i];
  }
}

static void BM_expf(benchmark::State &state) {
  std::vector<float> out(8);
  for (auto _ : state) {
    float num = -10;
    for (float num = -10; num < 10; num += 0.01) {
      std::vector<float> x{num,     num + 1, num + 2, num + 3,
                           num + 4, num + 5, num + 6, num + 7};
      doexp(x.data(), out.data());
      if (out[0] != expf(num)) {
        state.SkipWithError("Failed to read data!");
      }
    }
  }
}

// Register the function as a benchmark
BENCHMARK(BM_expf)->Setup(DoSetup);
// Run the benchmark
BENCHMARK_MAIN();
