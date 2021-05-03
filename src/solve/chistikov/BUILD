load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "solve_chistikov",
    srcs = ["solve_chistikov.cc"],
    hdrs = ["solve_chistikov.h"],
    visibility = ["//visibility:public"],
    deps = ["//solve:solution"],
)

cc_test(
    name = "solve_chistikov_test",
    size = "small",
    srcs = ["solve_chistikov_test.cc"],
    deps = [
        ":solve_chistikov",
        "//generate:generate_all",
        "//solve:solve_test_helpers",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
