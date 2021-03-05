!#/bin/sh
cd /home/resende/rust_scheduler
export PATH="$PATH:~/.rustup/toolchains/stable-x86_64-unknown-linux-gnu/bin"
module load gcc/6.1.0
module load cmake/3.13.5
RUSTFLAGS='-C target-cpu=native' cargo bench --bench native_schedulers
