use criterion::{black_box, criterion_group, criterion_main, BenchmarkId, Criterion, Throughput};

//use pprof::criterion::{Output, PProfProfiler};

use rayon::prelude::*;

fn sequential_par_iter_bench(data: &mut Vec<rust_scheduler::sequential::data::Data>) -> i32 {
    let a: Vec<_> = data
        .into_par_iter()
        .map(|d| rust_scheduler::sequential::io_scheduler::io_scheduler(d))
        .collect();

    a[0]
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
                    BenchmarkId::new("io_sequential_par_iter", parameter_string),
                    &(*size, *vector_size),
                    |b, (s, v)| {
                        let mut data: Vec<rust_scheduler::sequential::data::Data> = (0..*v)
                            .into_par_iter()
                            .map(|_| {
                                rust_scheduler::sequential::data::Data::new(1000, *s as i32, 1000)
                            })
                            .collect::<Vec<rust_scheduler::sequential::data::Data>>();

                        b.iter(|| black_box(sequential_par_iter_bench(&mut data)))
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
