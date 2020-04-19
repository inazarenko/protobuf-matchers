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
  name = "com_google_absl",
  urls = ["https://github.com/abseil/abseil-cpp/archive/master.zip"],
  strip_prefix = "abseil-cpp-master",
)

http_archive(
    name = "com_google_googletest",
    url = "https://github.com/google/googletest/archive/master.zip",
    strip_prefix = "googletest-master",
)

http_archive(
     name = "com_google_re2",
     urls = ["https://github.com/google/re2/archive/master.zip"],
     strip_prefix = "re2-master",
)

http_archive(
     name = "com_google_protobuf",
     urls = ["https://github.com/protocolbuffers/protobuf/archive/master.zip"],
     strip_prefix = "protobuf-master",
)

load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")

protobuf_deps()