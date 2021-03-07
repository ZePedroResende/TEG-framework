use criterion::{black_box, criterion_group, criterion_main, BenchmarkId, Criterion, Throughput};

//use pprof::criterion::{Output, PProfProfiler};

use rayon::prelude::*;
use std::sync::{Arc, RwLock};

fn speculative_bench(data: Arc<RwLock<Vec<rust_scheduler::speculative::data::Data>>>) {
    rust_scheduler::speculative::scheduler::scheduler(data, true);
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
                let parameter_string = format!("{}-{}", *size, *vector_size);
                group.throughput(Throughput::Bytes((*size * *vector_size) as u64));
                group.bench_with_input(
                    BenchmarkId::new("speculative", parameter_string),
                    &(*size, *vector_size),
                    |b, (s, v)| {
                        let data: Vec<rust_scheduler::speculative::data::Data> = (0..*v)
                            .into_par_iter()
                            .map(|_| rust_scheduler::speculative::data::Data::new(1000, *s, 1000))
                            .collect::<Vec<rust_scheduler::speculative::data::Data>>();

                        let arc = Arc::new(RwLock::new(data));

                        b.iter(|| black_box(speculative_bench(arc.clone())))
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