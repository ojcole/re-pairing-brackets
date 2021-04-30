load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "combine_solutions",
    srcs = ["combine_solutions.cc"],
    hdrs = ["combine_solutions.h"],
    visibility = ["//visibility:public"],
    deps = ["//solve:solution"],
)

cc_test(
    name = "combine_solutions_test",
    srcs = ["combine_solutions_test.cc"],
    deps = [
        ":combine_solutions",
        "//solve:solution",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
