load("@rules_cc//cc:defs.bzl", "cc_binary")
load("//benchmark:cc_opts.bzl", "COPTS")

cc_binary(
    name = "width_check_bench",
    srcs = ["width_check.cc"],
    copts = COPTS,
    data = [
        "exhaustive_bench_set100.txt",
        "exhaustive_bench_set200.txt",
        "exhaustive_bench_set50.txt",
    ],
    deps = [
        "//generate:generate_random",
        "//solve/predicate:width_check",
        "@benchmark",
    ],
)
