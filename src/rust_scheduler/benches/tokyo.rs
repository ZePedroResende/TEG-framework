use criterion::{black_box, criterion_group, criterion_main, BenchmarkId, Criterion, Throughput};

//use pprof::criterion::{Output, PProfProfiler};

use rayon::prelude::*;
use rust_scheduler::native::data::Data;
use rust_scheduler::native::scheduler::scheduler;
use std::sync::mpsc::channel;
//
fn tokio_bench(data: &mut Vec<Data>, threads: usize) -> i32 {
    let (sender, receiver) = channel();
    let result = tokio::runtime::Builder::new_multi_thread()
        .worker_threads(threads)
        .enable_all()
        .build()
        .unwrap()
        .block_on(async {
            let _a: Vec<_> = data
                .into_par_iter()
                .map_with(sender, |s, d| s.send(scheduler(d)))
                .collect();

            let b: Vec<_> = receiver.iter().collect();
            b[0]
        });
    result
}

fn bench(c: &mut Criterion) {
    let mut group = c.benchmark_group("schedulers");
    for size in [32, 64, 128, 256, 512, 1024].iter() {
        for vector_size in [
            12, 24, 48, 96, 120, 240, 360, 600, 800, 1200, 2400, 4800, 9600, 12000,
        ]
        .iter()
        {
            if !(*size == 1024 && *vector_size > 1200) || !(*size == 512 && *vector_size > 2400) {
                for thread in [2, 3, 6, 12, 24, 36, 48, 60, 72, 84].iter() {
                    if !(*size == 512 && *vector_size > 800 && *thread < 6)
                        || !(*size >= 256 && *vector_size > 600 && *thread < 6)
                    {
                        let parameter_string = format!("{}-{}-{}", *size, *vector_size, *thread);
                        group.throughput(Throughput::Bytes(
                            (((std::mem::size_of::<i32>() * *size * *size * 3)
                                + (std::mem::size_of::<f32>() * *size * *size * 3))
                                * *vector_size) as u64,
                        ));
                        group.bench_with_input(
                            BenchmarkId::new("tokio", parameter_string),
                            &(*size, *vector_size, *thread),
                            |b, (s, v, t)| {
                                let mut data: Vec<Data> = (0..*v)
                                    .into_par_iter()
                                    .map(|_| Data::new(1000, *s as i32, 1000))
                                    .collect::<Vec<Data>>();

                                b.iter(|| black_box(tokio_bench(&mut data, *t as usize)))
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
