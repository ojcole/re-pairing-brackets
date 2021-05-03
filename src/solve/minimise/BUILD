load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "minimise_width",
    srcs = ["minimise_width.cc"],
    hdrs = ["minimise_width.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//helpers:traversal",
        "//solve/derived:derived_strategy",
        "//solve/exhaustive:solve_exhaustive",
        "//solve/predicate:width_check",
    ],
)

cc_test(
    name = "minimise_width_test",
    size = "small",
    srcs = ["minimise_width.cc"],
    deps = [
        ":minimise_width",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
