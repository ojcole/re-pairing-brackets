load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "solve",
    srcs = [
        "parallel_worker.cc",
        "solve_parallel.cc",
    ],
    hdrs = [
        "parallel_worker.h",
        "result.h",
        "solve_parallel.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//generate:generate_next",
        "//helpers/parallel:compute_parallel",
        "//solve:solution",
        "//solve/exhaustive:solve_exhaustive",
    ],
)

cc_test(
    name = "solve_parallel_test",
    srcs = ["solve_parallel_test.cc"],
    deps = [
        ":solve",
        "//helpers:catalan",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
