# Proof-of-Concept Redox DTrace Port

This is a fork of [Oracle's Linux DTrace port](https://github.com/oracle/dtrace-utils).

It's 100% userland, but since Redox is a microkernel, this is where all the interesting stuff happens anyway. At the moment, it doesn't have the permissions necessary to trace anything but itself.

It relies heavily on Oracle's work. They wanted their diff to upstream Linux as minimal as possible and used eBPF heavily. We rely on [rbpf](https://github.com/qmonnet/rbpf/) to execute that code in userland as well.

This project is driven by academic interest and is not production-grade. It only runs on Redox nightly and is heavily work in progress, but some stuff works!

### What's Working

You can list available probes:

```sh
dtrace -l
relibc getrlimit(7, 0x7fffffffdc20): not implemented
relibc setrlimit(7, 0x7fffffffdc20): not implemented
relibc setrlimit(8, 0x7fffffffecb0): not implemented
   ID   PROVIDER            MODULE                          FUNCTION NAME
    1     dtrace                                                     BEGIN
    2     dtrace                                                     END
    3     dtrace                                                     ERROR
    4    profile                                                     profile-97
    5    profile                                                     profile-199
    6    profile                                                     profile-499
    7    profile                                                     profile-997
    8    profile                                                     profile-1999
    9    profile                                                     profile-4001
   10    profile                                                     profile-4999
   11    profile                                                     tick-1
   12    profile                                                     tick-10
   13    profile                                                     tick-100
   14    profile                                                     tick-500
   15    profile                                                     tick-1000
   16    profile                                                     tick-5000
```

And run basic scripts:

```sh
dtrace -n 'BEGIN { printf("hello"); exit(0); }'
relibc getrlimit(7, 0x7fffffffdc20): not implemented
relibc setrlimit(7, 0x7fffffffdc20): not implemented
relibc setrlimit(8, 0x7fffffffecb0): not implemented
dtrace: description 'BEGIN ' matched 1 probe
CPU     ID                    FUNCTION:NAME
  0      1                           :BEGIN hello
```
