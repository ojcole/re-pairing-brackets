load("@rules_cc//cc:defs.bzl", "cc_binary")
load("@//:copts.bzl", "COPTS")

cc_binary(
    name = "random-uniform",
    srcs = ["main.cc"],
    copts = COPTS,
    deps = [
        "@repairings//generate:generate_random",
    ],
)
