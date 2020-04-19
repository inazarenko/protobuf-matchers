load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test", "cc_proto_library")
load("@rules_proto//proto:defs.bzl", "proto_library")

cc_test(
    name = "temp_test",
    size = "small",
    srcs = [
        "temp_test.cc",
    ],
    deps = [
        "@com_google_googletest//:gtest_main",
    ],
)

proto_library(
    name = "deleteme_proto",
    srcs = ["deleteme.proto"]
)

cc_proto_library(
    name = "deleteme_cc_proto",
    deps = [":deleteme_proto"],
)