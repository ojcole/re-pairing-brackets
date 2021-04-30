load("@rules_cc//cc:defs.bzl", "cc_binary")
load("//benchmark:cc_opts.bzl", "COPTS")

cc_binary(
    name = "generate_random_symmetric_hard",
    srcs = ["generate_random_symmetric_hard.cc"],
    copts = COPTS,
    deps = [
        "//generate:generate_random",
        "@benchmark",
    ],
)

cc_binary(
    name = "generate_random_hard",
    srcs = ["generate_random_hard.cc"],
    copts = COPTS,
    deps = [
        "//generate:generate_random",
        "@benchmark",
    ],
)

cc_binary(
    name = "generate_random_symmetric",
    srcs = ["generate_random_symmetric.cc"],
    copts = COPTS,
    deps = [
        "//generate:generate_random",
        "@benchmark",
    ],
)

cc_binary(
    name = "generate_random_uniform",
    srcs = ["generate_random_uniform.cc"],
    copts = COPTS,
    deps = [
        "//generate:generate_random",
        "@benchmark",
    ],
)
