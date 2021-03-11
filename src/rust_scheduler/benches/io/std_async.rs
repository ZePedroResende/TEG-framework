use criterion::{black_box, criterion_group, criterion_main, BenchmarkId, Criterion, Throughput};

//use pprof::criterion::{Output, PProfProfiler};

use rayon::prelude::*;
use rust_scheduler::native::data::Data;
use rust_scheduler::native::pipeline_async::pipeline_async;
use std::sync::mpsc::channel;

fn async_bench(data: &mut Vec<Data>) -> i32 {
    async_std::task::block_on(async {
        let (sender, receiver) = channel();
        //scheduler(d.first().unwrap().clone());

        let _a: Vec<_> = data
            .into_par_iter()
            .map_with(sender, |s, d| s.send(pipeline_async(d)))
            .collect();

        let mut b: Vec<_> = Vec::new();
        for a in receiver.iter() {
            b.push(a.await);
        }
        b[0]
    })
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
                    BenchmarkId::new("io_async", parameter_string),
                    &(*size, *vector_size),
                    |b, (s, v)| {
                        let mut data: Vec<Data> = (0..*v)
                            .into_par_iter()
                            .map(|_| Data::new(1000, *s as i32, 1000))
                            .collect::<Vec<Data>>();

                        b.iter(|| black_box(async_bench(&mut data)))
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
