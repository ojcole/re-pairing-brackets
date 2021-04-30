load("@rules_cc//cc:defs.bzl", "cc_binary")
load("//benchmark:cc_opts.bzl", "COPTS")

cc_binary(
    name = "parallel_convert_benchmark",
    srcs = ["parallel_convert_benchmark.cc"],
    copts = COPTS,
    deps = [
        "//generate:generate_next",
        "@benchmark",
    ],
)

cc_binary(
    name = "generate_next_all",
    srcs = ["generate_next_all.cc"],
    copts = COPTS,
    deps = [
        "//generate:generate_next",
        "@benchmark",
    ],
)

cc_binary(
    name = "generate_next_all_string",
    srcs = ["generate_next_all_string.cc"],
    copts = COPTS,
    deps = [
        "//generate:generate_all",
        "@benchmark",
    ],
)

cc_binary(
    name = "generate_next_symmetric_all",
    srcs = ["generate_next_symmetric_all.cc"],
    copts = COPTS,
    deps = [
        "//generate:generate_next_symmetric",
        "@benchmark",
    ],
)

cc_binary(
    name = "generate_next_symmetric_all_string",
    srcs = ["generate_next_symmetric_all_string.cc"],
    copts = COPTS,
    deps = [
        "//generate:generate_all",
        "@benchmark",
    ],
)

cc_binary(
    name = "generate_swapping_all",
    srcs = ["generate_swapping_all.cc"],
    copts = COPTS,
    deps = [
        "//generate:generate_all",
        "@benchmark",
    ],
)
