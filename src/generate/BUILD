load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "generate_all",
    srcs = ["generate_all.cc"],
    hdrs = ["generate_all.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":generate_next",
        ":generate_next_symmetric",
        "//helpers:catalan",
        "//helpers:constants",
    ],
)

cc_library(
    name = "generate_next",
    srcs = ["generate_next.cc"],
    hdrs = ["generate_next.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//helpers:verifiers",
        "//solve:solution",
    ],
)

cc_library(
    name = "generate_xyz",
    srcs = ["generate_xyz.cc"],
    hdrs = ["generate_xyz.h"],
    visibility = ["//visibility:public"],
    deps = ["//solve:solution"],
)

cc_library(
    name = "generate_random",
    srcs = [
        "generate_random.cc",
        "generate_random_hard.cc",
    ],
    hdrs = [
        "generate_random.h",
        "generate_random_hard.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//solve:solution",
    ],
)

cc_library(
    name = "generate_test_helpers",
    srcs = ["generate_test_helpers.cc"],
    hdrs = ["generate_test_helpers.h"],
    visibility = [
        "//visibility:private",
    ],
    deps = ["//helpers:constants"],
)

cc_library(
    name = "generate_next_symmetric",
    srcs = ["generate_next_symmetric.cc"],
    hdrs = ["generate_next_symmetric.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//helpers:constants",
        "//helpers:verifiers",
    ],
)

cc_test(
    name = "generate_all_test",
    size = "small",
    srcs = ["generate_all_test.cc"],
    deps = [
        ":generate_all",
        ":generate_test_helpers",
        "//helpers:catalan",
        "//helpers:constants",
        "//helpers:nchoosek",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "generate_next_test",
    size = "small",
    srcs = ["generate_next_test.cc"],
    deps = [
        ":generate_all",
        ":generate_next",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "generate_random_test",
    size = "medium",
    srcs = ["generate_random_test.cc"],
    deps = [
        ":generate_random",
        "//helpers:verifiers",
        "//solve:solution",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "generate_random_hard_test",
    size = "small",
    srcs = ["generate_random_hard_test.cc"],
    deps = [
        ":generate_random",
        ":generate_test_helpers",
        "//helpers:verifiers",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "generate_xyz_test",
    size = "small",
    srcs = ["generate_xyz_test.cc"],
    deps = [
        ":generate_xyz",
        "//helpers:verifiers",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "generate_next_symmetric_test",
    size = "small",
    srcs = ["generate_next_symmetric_test.cc"],
    deps = [
        ":generate_next_symmetric",
        "//helpers:constants",
        "//helpers:manipulators",
        "//helpers:nchoosek",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
