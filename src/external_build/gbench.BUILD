load("@rules_cc//cc:defs.bzl", "cc_library")
load("@//benchmark:cc_opts.bzl", "COPTS")

cc_library(
    name = "benchmark",
    srcs = glob(
        [
            "src/*.cc",
            "src/*.h",
        ],
        exclude = ["src/benchmark_main.cc"],
    ),
    hdrs = ["include/benchmark/benchmark.h"],
    copts = COPTS,
    linkopts = ["-pthread"],
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
)
