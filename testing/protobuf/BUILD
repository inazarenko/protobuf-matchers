#
# Copyright 2020 Igor Nazarenko
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_proto_library", "cc_test")
load("@rules_proto//proto:defs.bzl", "proto_library")

cc_library(
    name = "matchers",
    hdrs = ["protocol-buffer-matchers.h"],
    srcs = ["protocol-buffer-matchers.cc"],
    testonly = 1,
    deps = [
        "@com_google_googletest//:gtest",
        "@com_google_protobuf//:protobuf",
        "@com_google_absl//absl/strings",
        "@com_google_re2//:re2",
    ]
)

proto_library(
    name = "deleteme_proto",
    srcs = ["deleteme.proto"],
)

cc_proto_library(
    name = "deleteme_cc_proto",
    deps = [":deleteme_proto"],
)

cc_test(
    name = "temp_test",
    size = "small",
    srcs = [
        "temp_test.cc",
    ],
    deps = [
        ":deleteme_cc_proto",
        "@com_google_googletest//:gtest_main",
    ],
)