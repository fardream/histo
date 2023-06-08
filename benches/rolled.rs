use criterion::{criterion_group, criterion_main, BenchmarkId, Criterion};
use pprof::criterion::{Output, PProfProfiler};

struct V {
    x: Vec<f32>,
    y: Vec<f32>,
}

fn setup(n: usize) -> V {
    V {
        x: vec![0.; n],
        y: vec![0.; n],
    }
}

fn histo_test(c: &mut Criterion) {
    let mut group = c.benchmark_group("roll");

    for n in [1_000_000, 10_000_000, 100_000_000] {
        let v = setup(n);
        group.bench_with_input(BenchmarkId::new("r1", n), &v, |b, p| {
            b.iter(|| {
                histo::dot(&p.x, &p.y, n);
            });
        });
        group.bench_with_input(BenchmarkId::new("r8", n), &v, |b, p| {
            b.iter(|| {
                histo::dot8(&p.x, &p.y, n);
            });
        });
        group.bench_with_input(BenchmarkId::new("c1", n), &v, |b, p| {
            b.iter(|| unsafe {
                histo::cimpl::dot(p.x.as_ptr(), p.y.as_ptr(), n);
            });
        });
        group.bench_with_input(BenchmarkId::new("c8", n), &v, |b, p| {
            b.iter(|| unsafe {
                histo::cimpl::dot8(p.x.as_ptr(), p.y.as_ptr(), n);
            });
        });
        group.bench_with_input(BenchmarkId::new("ct", n), &v, |b, p| {
            b.iter(|| unsafe {
                histo::cimpl::dott(p.x.as_ptr(), p.y.as_ptr(), n);
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
