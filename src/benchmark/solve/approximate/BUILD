load("@rules_cc//cc:defs.bzl", "cc_binary")
load("//benchmark:cc_opts.bzl", "COPTS")

cc_binary(
    name = "solve_approximate_benchmark",
    srcs = ["solve_approximate_benchmark.cc"],
    copts = COPTS,
    deps = [
        "//generate:generate_all",
        "//solve:solve_approximate",
        "@benchmark",
    ],
)
