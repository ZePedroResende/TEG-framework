use criterion::{black_box, criterion_group, criterion_main, BenchmarkId, Criterion, Throughput};

//use pprof::criterion::{Output, PProfProfiler};

use rayon::prelude::*;
use std::sync::{Arc, RwLock};

fn speculative_bench(
    data: Arc<RwLock<Vec<rust_scheduler::sequential::data::Data>>>,
    n_threads: usize,
    pipeline: usize,
    io: bool,
) {
    rust_scheduler::speculative::scheduler::scheduler(data, n_threads, pipeline, io);
}

fn bench(c: &mut Criterion) {
    let mut group = c.benchmark_group("schedulers");
    for pipeline in [20, 10].iter() {
        for io in [false, true].iter() {
            for size in [32, 128, 512, 1024].iter() {
                for vector_size in [12, 240, 1200, 4800, 9600].iter() {
                    for thread in [2, 6, 12, 18, 24, 48].iter() {
                        //                    for thread in [6].iter() {
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
                            BenchmarkId::new("speculative", parameter_string),
                            &(*size, *vector_size, *thread, *pipeline, *io),
                            |b, (s, v, t, p, i)| {
                                let data: Vec<rust_scheduler::sequential::data::Data> = (0..*v)
                                    .into_par_iter()
                                    .map(|_| {
                                        rust_scheduler::sequential::data::Data::new(
                                            1000, *s as i32, 1000,
                                        )
                                    })
                                    .collect::<Vec<rust_scheduler::sequential::data::Data>>();

                                let arc = Arc::new(RwLock::new(data));

                                b.iter(|| black_box(speculative_bench(arc.clone(), *t, *p, *i)))
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
