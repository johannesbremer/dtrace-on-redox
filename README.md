# Proof-of-Concept Redox DTrace Port

This is a fork of [Oracle's Linux DTrace port](https://github.com/oracle/dtrace-utils).

It's 100% userland, but since Redox is a microkernel, this is where all the interesting stuff happens anyway. At the moment, it doesn't have the permissions necessary to trace anything but itself.

It relies heavily on Oracle's work. They wanted their diff to upstream Linux as minimal as possible and used eBPF heavily. We rely on [rbpf](https://github.com/qmonnet/rbpf/) to execute that code in userland.

This project is driven by academic interest and is not production-grade. It only runs on Redox nightly and is heavily work in progress, but some stuff works!

### Installation

A zip-file of the application can be downloaded [here](https://nightly.link/johannesbremer/dtrace-on-redox/workflows/build-dtrace/devel/dtrace-redox.zip).

### What's Working

```sh
dtrace -l
```

```sh
dtrace -n 'BEGIN { printf("hello\n"); exit(0); }'
```

```sh
dtrace -n 'BEGIN { x = 10; printf("x is %s\n", x > 5 ? "big" : "small"); exit(0); }'
```

```sh
dtrace -n 'BEGIN { printf("pid=%d tid=%d uid=%d\n", pid, tid, uid); exit(0); }'
```

```sh
dtrace -n 'BEGIN { printf("timestamp=%d walltimestamp=%d\n", timestamp, walltimestamp); exit(0); }'
```

```sh
dtrace -n 'BEGIN { printf("Starting...\n"); } END { printf("Done!\n"); }'
```

↑ Press `Ctrl+C` to exit
