load("@rules_cc//cc:defs.bzl", "cc_binary")
load("@//:copts.bzl", "COPTS")

cc_binary(
    name = "width4",
    srcs = ["main.cc"],
    copts = COPTS,
    deps = [
        "@repairings//solve/predicate:width_check",
    ],
)
