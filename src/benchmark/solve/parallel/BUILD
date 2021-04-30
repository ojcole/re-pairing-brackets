load("@rules_cc//cc:defs.bzl", "cc_binary")
load("//benchmark:cc_opts.bzl", "COPTS")

cc_binary(
    name = "parallel_solve_benchmark",
    srcs = ["parallel_solve_benchmark.cc"],
    copts = COPTS,
    deps = [
        "//solve/parallel:solve",
        "@benchmark",
    ],
)
