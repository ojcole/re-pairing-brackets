load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "width_check",
    srcs = ["width_check.cc"],
    hdrs = ["width_check.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//generate:generate_random",
        "//helpers:verifiers",
        "//solve:solution",
    ],
)

cc_test(
    name = "width_check_test",
    srcs = ["width_check_test.cc"],
    visibility = ["//visibility:public"],
    deps = [
        ":width_check",
        "//generate:generate_all",
        "//solve/exhaustive:solve_exhaustive",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
