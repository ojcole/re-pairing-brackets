load("@rules_cc//cc:defs.bzl", "cc_binary")
load("//benchmark:cc_opts.bzl", "COPTS")

cc_binary(
    name = "generate_dynamic_all",
    srcs = ["generate_dynamic_all.cc"],
    copts = COPTS,
    deps = [
        "//generate:generate_all",
        "@benchmark",
    ],
)

cc_binary(
    name = "generate_simple_all",
    srcs = ["generate_simple_all.cc"],
    copts = COPTS,
    deps = [
        "//generate:generate_all",
        "@benchmark",
    ],
)

cc_binary(
    name = "generate_simple_memo_all",
    srcs = ["generate_simple_memo_all.cc"],
    copts = COPTS,
    deps = [
        "//generate:generate_all",
        "@benchmark",
    ],
)
