use criterion::{criterion_group, criterion_main, BenchmarkId, Criterion};
use pprof::criterion::{Output, PProfProfiler};

struct V {
    x: Vec<u8>,
    f: Vec<f32>,
}
fn setup(n_f: usize, n_r: usize) -> V {
    let x = vec![0; n_f * n_r / 2];
    let f = vec![0.; n_f * n_r];

    V { x, f }
}

fn histo_test(c: &mut Criterion) {
    let mut group = c.benchmark_group("histo");

    let n_f = 30;
    let nb = 16;

    for n_r in [1_000_000, 10_000_000, 100_000_000] {
        let v = setup(n_f, n_r);
        group.bench_with_input(BenchmarkId::new("r1", n_r), &v, |b, p| {
            b.iter(|| {
                let mut out = vec![0.; nb * n_f];
                histo::histo(&p.x, &p.f, n_f, n_r, nb, &mut out);
            });
        });
        group.bench_with_input(BenchmarkId::new("r8", n_r), &v, |b, p| {
            b.iter(|| {
                let mut out = vec![0.; nb * n_f];
                histo::histo8(&p.x, &p.f, n_f, n_r, nb, &mut out);
            });
        });

        group.bench_with_input(BenchmarkId::new("c1", n_r), &v, |b, p| {
            b.iter(|| {
                let mut out = vec![0.; nb * n_f];
                unsafe {
                    histo::cimpl::histo(p.x.as_ptr(), p.f.as_ptr(), n_f, n_r, nb, out.as_mut_ptr());
                }
            });
        });
        group.bench_with_input(BenchmarkId::new("c8", n_r), &v, |b, p| {
            b.iter(|| {
                let mut out = vec![0.; nb * n_f];
                unsafe {
                    histo::cimpl::histo_8(
                        p.x.as_ptr(),
                        p.f.as_ptr(),
                        n_f,
                        n_r,
                        nb,
                        out.as_mut_ptr(),
                    );
                }
            });
        });
    }
}

criterion_group! {
    name = benches;
    config = Criterion::default().with_profiler(PProfProfiler::new(10000, Output::Protobuf));
    targets = histo_test
}

criterion_main!(benches);
