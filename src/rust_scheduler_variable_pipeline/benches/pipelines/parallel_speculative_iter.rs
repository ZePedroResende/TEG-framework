use criterion::{black_box, criterion_group, criterion_main, BenchmarkId, Criterion, Throughput};

//use pprof::criterion::{Output, PProfProfiler};

use rayon::prelude::*;
use std::sync::{Arc, RwLock};

fn parallel_speculative_iter_bench(
    data: &mut Vec<Arc<RwLock<rust_scheduler::sequential::data::Data>>>,
    n_threads: usize,
    pipeline: usize,
    io: bool,
) {
    let _a: Vec<_> = data
        .into_iter()
        .map(|d| {
            rust_scheduler::parallel_speculative::scheduler::scheduler(
                d, true, n_threads, pipeline, io,
            )
        })
        .collect();
}

fn bench(c: &mut Criterion) {
    let mut group = c.benchmark_group("schedulers");
    for pipeline in [10, 20].iter() {
        for io in [false, true].iter() {
            for size in [32, 128, 512, 1024].iter() {
                for vector_size in [12, 240, 1200, 4800, 9600].iter() {
                    for thread in [2, 6, 12, 18, 24, 48].iter() {
                        let parameter_string = format!(
                            "{}-{}-{}-{}-{}",
                            *pipeline, *io, *size, *vector_size, *thread
                        );
                        group.throughput(Throughput::Bytes(
                            (((std::mem::size_of::<i32>() * *size * *size * 3)
                                + (std::mem::size_of::<f32>() * *size * *size * 3))
                                * *vector_size) as u64,
                        ));
                        group.bench_with_input(
                            BenchmarkId::new("pipeline_parallel_speculative", parameter_string),
                            &(*pipeline, *io, *size, *vector_size, *thread),
                            |b, (p, i, s, v, t)| {
                                let mut d: Vec<
                                    Arc<RwLock<rust_scheduler::sequential::data::Data>>,
                                > = (0..*v)
                                    .into_par_iter()
                                    .map(|_| {
                                        Arc::new(RwLock::new(
                                            rust_scheduler::sequential::data::Data::new(
                                                1000, *s as i32, 1000,
                                            ),
                                        ))
                                    })
                                    .collect::<Vec<
                                        Arc<
                                            RwLock<
                                                rust_scheduler::sequential::data::Data,
                                            >,
                                        >,
                                    >>();

                                b.iter(|| {
                                    black_box(parallel_speculative_iter_bench(&mut d, *t, *p, *i))
                                })
                            },
                        );
                    }
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
