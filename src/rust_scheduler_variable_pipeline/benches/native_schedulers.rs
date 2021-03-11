use criterion::{black_box, criterion_group, criterion_main, BenchmarkId, Criterion, Throughput};
use criterion_papi::PapiMeasurement;

use pprof::criterion::{Output, PProfProfiler};

use rayon::prelude::*;
use rust_scheduler::native::data::Data;
use rust_scheduler::native::scheduler::scheduler;
use std::sync::mpsc::channel;
use std::sync::{Arc, RwLock};

// Thanks to the example provided by @jebbow in his article
// https://www.jibbow.com/posts/criterion-flamegraphs/
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

fn tokio_sequential_bench(data: &mut Vec<Data>, threads: usize) -> i32 {
    let (sender, receiver) = channel();
    let result = tokio::runtime::Builder::new_multi_thread()
        .worker_threads(threads)
        .enable_all()
        .build()
        .unwrap()
        .block_on(async {
            let _a: Vec<_> = data.into_iter().map(|mut d| scheduler(&mut d)).collect();

            let b: Vec<_> = receiver.iter().collect();
            b[0]
        });
    result
}

fn sequential_iter_bench(data: &mut Vec<rust_scheduler::sequential::data::Data>) -> i32 {
    let a: Vec<_> = data
        .into_iter()
        .map(|d| rust_scheduler::sequential::scheduler::scheduler(d))
        .collect();

    a[0]
}
fn sequential_par_iter_bench(data: &mut Vec<rust_scheduler::sequential::data::Data>) -> i32 {
    let a: Vec<_> = data
        .into_par_iter()
        .map(|d| rust_scheduler::sequential::scheduler::scheduler(d))
        .collect();

    a[0]
}

fn speculative_bench(data: Arc<RwLock<Vec<rust_scheduler::speculative::data::Data>>>) {
    rust_scheduler::speculative::scheduler::scheduler(data, true);
}

fn parallel_speculative_iter_bench(
    data: &mut Vec<Arc<RwLock<rust_scheduler::parallel_speculative::data::Data>>>,
) {
    let _a: Vec<_> = data
        .into_iter()
        .map(|d| rust_scheduler::parallel_speculative::scheduler::scheduler(d, true))
        .collect();
}
fn parallel_speculative_par_iter_bench(
    data: &mut Vec<Arc<RwLock<rust_scheduler::parallel_speculative::data::Data>>>,
) {
    let _a: Vec<_> = data
        .into_par_iter()
        .map(|d| rust_scheduler::parallel_speculative::scheduler::scheduler(d, true))
        .collect();
}

fn size_of_struct(size: usize) -> usize {
    ((std::mem::size_of::<i32>() * size * size * 3)
        + (std::mem::size_of::<f32>() * size * size * 3))
        * 500
}

fn async_bench(data: &mut Vec<Data>) -> i32 {
    let (sender, receiver) = channel();
    //scheduler(d.first().unwrap().clone());

    let _a: Vec<_> = data
        .into_par_iter()
        .map_with(sender, |s, d| s.send(scheduler(d)))
        .collect();

    let b: Vec<_> = receiver.iter().collect();
    b[0]
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
                        || !(*size == 512 && *vector_size > 800 && *thread < 6)
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

                        /*
                        let parameter_string = format!("{}-{}-{}", *size, *vector_size, *thread);
                        group.bench_with_input(
                            BenchmarkId::new("tokio_seq", parameter_string),
                            &(*size, *vector_size, *thread),
                            |b, (s, v, t)| {
                                let mut data: Vec<Data> = (0..*v)
                                    .into_par_iter()
                                    .map(|_| Data::new(1000, *s as i32, 1000))
                                    .collect::<Vec<Data>>();

                                b.iter(|| black_box(tokio_sequential_bench(&mut data, *t as usize)))
                            },
                        );
                        */

                        let parameter_string = format!("{}-{}-{}", *size, *vector_size, *thread);
                        group.bench_with_input(
                            BenchmarkId::new("async", parameter_string),
                            &(*size, *vector_size, *thread),
                            |b, (s, v, t)| {
                                let mut data: Vec<Data> = (0..*v)
                                    .into_par_iter()
                                    .map(|_| Data::new(1000, *s as i32, 1000))
                                    .collect::<Vec<Data>>();

                                b.iter(|| black_box(async_bench(&mut data)))
                            },
                        );

                        let parameter_string = format!("{}-{}-{}", *size, *vector_size, *thread);
                        group.bench_with_input(
                            BenchmarkId::new("sequential_par_iter", parameter_string),
                            &(*size, *vector_size, *thread),
                            |b, (s, v, t)| {
                                let mut data: Vec<rust_scheduler::sequential::data::Data> = (0..*v)
                                    .into_par_iter()
                                    .map(|_| {
                                        rust_scheduler::sequential::data::Data::new(
                                            1000, *s as i32, 1000,
                                        )
                                    })
                                    .collect::<Vec<rust_scheduler::sequential::data::Data>>();

                                b.iter(|| black_box(sequential_par_iter_bench(&mut data)))
                            },
                        );
                    }
                }
            }
        }
    }
    group.finish();

    /*
    c.bench_function("tokio", |b| {
        let mut data: Vec<Data> = (0..10000)
            .into_par_iter()
            .map(|_| Data::new(1000, 100, 1000))
            .collect::<Vec<Data>>();

        b.iter(|| black_box(tokio_bench(&mut data)))
    });

    c.bench_function("tokio_sequential", |b| {
        let mut data: Vec<Data> = (0..10000)
            .into_par_iter()
            .map(|_| Data::new(1000, 100, 1000))
            .collect::<Vec<Data>>();

        b.iter(|| black_box(tokio_bench(&mut data)))
    });

    c.bench_function("async", |b| {
        let mut data: Vec<Data> = (0..10000)
            .into_par_iter()
            .map(|_| Data::new(1000, 100, 1000))
            .collect::<Vec<Data>>();

        b.iter(|| black_box(async_bench(&mut data)))
    });

    c.bench_function("sequential iter", |b| {
        let mut data: Vec<rust_scheduler::sequential::data::Data> = (0..10000)
            .into_par_iter()
            .map(|_| rust_scheduler::sequential::data::Data::new(1000, 100, 1000))
            .collect::<Vec<rust_scheduler::sequential::data::Data>>();

        b.iter(|| black_box(sequential_iter_bench(&mut data)))
    });

    c.bench_function("sequential par_iter", |b| {
        let mut data: Vec<rust_scheduler::sequential::data::Data> = (0..10000)
            .into_par_iter()
            .map(|_| rust_scheduler::sequential::data::Data::new(1000, 100, 1000))
            .collect::<Vec<rust_scheduler::sequential::data::Data>>();

        b.iter(|| black_box(sequential_par_iter_bench(&mut data)))
    });

    c.bench_function("speculative ", |b| {
        let data: Vec<rust_scheduler::speculative::data::Data> = (0..10000)
            .into_par_iter()
            .map(|_| rust_scheduler::speculative::data::Data::new(1000, 100, 1000))
            .collect::<Vec<rust_scheduler::speculative::data::Data>>();

        let arc = Arc::new(RwLock::new(data));

        b.iter(|| black_box(speculative_bench(arc.clone())))
    });

    c.bench_function("parallel speculative iter", |b| {
        let mut d: Vec<Arc<RwLock<rust_scheduler::parallel_speculative::data::Data>>> = (0..10000)
            .into_par_iter()
            .map(|_| {
                Arc::new(RwLock::new(
                    rust_scheduler::parallel_speculative::data::Data::new(1000, 100, 1000),
                ))
            })
            .collect::<Vec<Arc<RwLock<rust_scheduler::parallel_speculative::data::Data>>>>();

        b.iter(|| black_box(parallel_speculative_iter_bench(&mut d)))
    });

    c.bench_function("parallel speculative par_iter", |b| {
        let mut d: Vec<Arc<RwLock<rust_scheduler::parallel_speculative::data::Data>>> = (0..10000)
            .into_par_iter()
            .map(|_| {
                Arc::new(RwLock::new(
                    rust_scheduler::parallel_speculative::data::Data::new(1000, 100, 1000),
                ))
            })
            .collect::<Vec<Arc<RwLock<rust_scheduler::parallel_speculative::data::Data>>>>();

        b.iter(|| black_box(parallel_speculative_par_iter_bench(&mut d)))
    });
        */
}

fn alternate_measurement() -> Criterion<PapiMeasurement> {
    Criterion::default()
        .sample_size(10)
        .with_profiler(PProfProfiler::new(10, Output::Protobuf))
        .with_measurement(PapiMeasurement::new("PAPI_TOT_INS"))
        .with_measurement(PapiMeasurement::new("PAPI_L1_DCA"))
        .with_measurement(PapiMeasurement::new("PAPI_L1_TCA"))
        .with_measurement(PapiMeasurement::new("PAPI_L1_ICH"))
        //        .with_measurement(PapiMeasurement::new("PAPI_SP_OPS"))
        //        .with_measurement(PapiMeasurement::new("PAPI_FP_OPS"))
        //        //       .with_measurement(PapiMeasurement::new("PAPI_STL_ICV"))
        //        //.with_measurement(PapiMeasurement::new("PAPI_LD_INS"))
        //        //        .with_measurement(PapiMeasurement::new("PAPI_L2_DCR"))
        //        //        .with_measurement(PapiMeasurement::new("PAPI_L3_DCR"))
        //        //        .with_measurement(PapiMeasurement::new("PAPI_L3_TCA"))
        //        //        .with_measurement(PapiMeasurement::new("PAPI_L3_TCM"))
        //        .with_measurement(PapiMeasurement::new("PAPI_FP_INS"))
        .configure_from_args()
}

criterion_group! {
    name = benches;
    config = Criterion::default().sample_size(10);//.with_profiler(PProfProfiler::new(10, Output::Flamegraph(None)));
    //config = alternate_measurement();
    targets = bench
}
criterion_main!(benches);
