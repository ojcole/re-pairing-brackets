load("@rules_cc//cc:defs.bzl", "cc_binary")
load("//benchmark:cc_opts.bzl", "COPTS")

cc_binary(
    name = "derived_solve_benchmark",
    srcs = ["derived_solve_benchmark.cc"],
    copts = COPTS,
    deps = [
        "//generate:generate_next",
        "//generate:generate_random",
        "//solve/derived:derived_strategy",
        "@benchmark",
    ],
)
