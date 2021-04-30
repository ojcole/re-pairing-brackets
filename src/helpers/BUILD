load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "constants",
    hdrs = ["constants.h"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "manipulators",
    srcs = ["manipulators.cc"],
    hdrs = ["manipulators.h"],
    visibility = ["//visibility:public"],
    deps = [":constants"],
)

cc_library(
    name = "verifiers",
    srcs = ["verifiers.cc"],
    hdrs = ["verifiers.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":constants",
        ":manipulators",
    ],
)

cc_library(
    name = "catalan",
    srcs = ["catalan.cc"],
    hdrs = ["catalan.h"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "nchoosek",
    srcs = ["n_choose_k.cc"],
    hdrs = ["n_choose_k.h"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "traversal",
    hdrs = ["traversal.h"],
    visibility = ["//visibility:public"],
    deps = [":constants"],
)

cc_test(
    name = "catalan_test",
    srcs = ["catalan_test.cc"],
    deps = [
        ":catalan",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "n_choose_k_test",
    srcs = ["n_choose_k_test.cc"],
    deps = [
        ":nchoosek",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "manipulators_test",
    srcs = ["manipulators_test.cc"],
    deps = [
        ":constants",
        ":manipulators",
        "//generate:generate_random",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "verifiers_test",
    srcs = ["verifiers_test.cc"],
    deps = [
        ":verifiers",
        "//generate:generate_random",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "traversal_test",
    srcs = ["traversal_test.cc"],
    deps = [
        ":traversal",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
