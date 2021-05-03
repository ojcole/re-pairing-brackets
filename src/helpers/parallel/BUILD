load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "compute_parallel",
    hdrs = ["compute_parallel.h"],
    linkopts = ["-pthread"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "reducers",
    hdrs = ["reducers.h"],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "compute_parallel_test",
    size = "small",
    srcs = ["compute_parallel_test.cc"],
    deps = [
        ":compute_parallel",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "reducers_test",
    size = "small",
    srcs = ["reducers_test.cc"],
    deps = [
        ":reducers",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
