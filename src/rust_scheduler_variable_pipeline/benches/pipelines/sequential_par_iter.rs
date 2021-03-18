use criterion::{black_box, criterion_group, criterion_main, BenchmarkId, Criterion, Throughput};

//use pprof::criterion::{Output, PProfProfiler};

use rayon::prelude::*;

fn sequential_par_iter_bench(
    data: &mut Vec<rust_scheduler::sequential::data::Data>,
    pipeline: usize,
    io: bool,
) -> i32 {
    let a: Vec<_> = data
        .into_par_iter()
        .map(|d| rust_scheduler::sequential::scheduler::scheduler(d, pipeline, io))
        .collect();

    a[0]
}

fn bench(c: &mut Criterion) {
    let mut group = c.benchmark_group("schedulers");
    for pipeline in [10, 20].iter() {
        for io in [true, false].iter() {
            for size in [32, 128, 512, 1024].iter() {
                for vector_size in [12, 240, 1200, 4800, 9600].iter() {
                    let parameter_string =
                        format!("{}-{}-{}-{}", *pipeline, *io, *size, *vector_size);
                    group.throughput(Throughput::Bytes(
                        (((std::mem::size_of::<i32>() * *size * *size * 3)
                            + (std::mem::size_of::<f32>() * *size * *size * 3))
                            * *vector_size) as u64,
                    ));
                    group.bench_with_input(
                        BenchmarkId::new("sequential_rayon", parameter_string),
                        &(*pipeline, *io, *size, *vector_size),
                        |b, (p, i, s, v)| {
                            let mut d: Vec<rust_scheduler::sequential::data::Data> = (0..*v)
                                .into_par_iter()
                                .map(|_| {
                                    rust_scheduler::sequential::data::Data::new(
                                        1000, *s as i32, 1000,
                                    )
                                })
                                .collect::<Vec<rust_scheduler::sequential::data::Data>>();

                            b.iter(|| black_box(sequential_par_iter_bench(&mut d, *p, *i)))
                        },
                    );
                }
            }
        }
    }
    group.finish();
}

criterion_group! {
    name = benches;
    config = Criterion::default().sample_size(10);//.with_profiler(PProfProfiler::new(10, Output::Flamegraph(None)));
    targets = bench
}
criterion_main!(benches);
