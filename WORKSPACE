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
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "com_google_googletest",
    url = "https://github.com/google/googletest/archive/dcc92d0ab6c4ce022162a23566d44f673251eee4.zip",
    sha256 = "a6ab7c7d6fd4dd727f6012b5d85d71a73d3aa1274f529ecd4ad84eb9ec4ff767",
    strip_prefix = "googletest-dcc92d0ab6c4ce022162a23566d44f673251eee4",
)

http_archive(
     name = "com_google_protobuf",
     strip_prefix = "protobuf-f15ac4091f96eb88f583eaa040ed16319104ebd2",
     urls = ["https://github.com/protocolbuffers/protobuf/archive/f15ac4091f96eb88f583eaa040ed16319104ebd2.zip"],
     sha256 = "a6896dfb9d4df9ed733edfeac9c714336c862b030c08c9395c579727af06c89b",
)

load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")

protobuf_deps()