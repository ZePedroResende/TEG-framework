use criterion::{black_box, criterion_group, criterion_main, BenchmarkId, Criterion, Throughput};

//use pprof::criterion::{Output, PProfProfiler};

use rayon::prelude::*;
use std::sync::{Arc, RwLock};

fn parallel_speculative_iter_bench(
    data: &mut Vec<Arc<RwLock<rust_scheduler::parallel_speculative::data::Data>>>,
) {
    let _a: Vec<_> = data
        .into_iter()
        .map(|d| rust_scheduler::parallel_speculative::scheduler::scheduler(d, true))
        .collect();
}

fn bench(c: &mut Criterion) {
    let mut group = c.benchmark_group("schedulers");
    for size in [32, 64, 128, 256, 512, 1024].iter() {
        for vector_size in [
            12, 24, 48, 96, 120, 240, 360, 600, 800, 1200, 2400, 4800, 9600, 12000,
        ]
        .iter()
        {
            if !(*size >= 512 && *vector_size >= 1200) {
                let parameter_string = format!("{}-{}", *size, *vector_size);
                group.throughput(Throughput::Bytes(
                    (((std::mem::size_of::<i32>() * *size * *size * 3)
                        + (std::mem::size_of::<f32>() * *size * *size * 3))
                        * *vector_size) as u64,
                ));
                group.bench_with_input(
                        BenchmarkId::new("parallel_speculative_iter", parameter_string),
                        &(*size, *vector_size),
                        |b, (s, v)| {
                            let mut d: Vec<Arc<RwLock<rust_scheduler::parallel_speculative::data::Data>>> = (0..*v)
                                .into_par_iter()
                                .map(|_| {
                                    Arc::new(RwLock::new(
                                            rust_scheduler::parallel_speculative::data::Data::new(1000, *s as i32, 1000),
                                            ))
                                })
                            .collect::<Vec<Arc<RwLock<rust_scheduler::parallel_speculative::data::Data>>>>();

                            b.iter(|| black_box(parallel_speculative_iter_bench(&mut d)))
                        },
                        );
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
