GMock matchers for protocol buffers
===================================

A library of matchers for protocol buffer message objects, for unit tests
written using Google Test framework. E.g.

```c++
  #include "protobuf-matchers/protocol-buffer-matchers.h"
  ...
  using ::protobuf_matchers::EqualsProto;
  using ::protobuf_matchers::Approximately;
  using ::protobuf_matchers::Partially;
  ...
  EXPECT_THAT(msg, EqualsProto("val: 10.0 is_null: false"));
  EXPECT_THAT(msg, Partially(Approximately(EqualsProto("val: 10.0000001"))));
```

Matcher code was released within [Nucleus](https://github.com/google/nucleus)
project. This fork removes dependencies on Tensorflow and the rest of the
Nucleus code.

# Using as a Bazel module

In your `MODULE.bazel`:

```
...
bazel_dep(name = "protobuf-matchers", version = "0.1.0")
...
```

In your `BUILD`:

```
cc_test(
    ...
    deps = [
       ...
       "@protobuf-matchers//protobuf-matchers",
    ],
)
```

See also: https://bazel.build/rules/lib/globals/module

# Build with Bazel

[Nix shell](https://nixos.org) (optional)
```sh
nix-shell -p stdenv bazel_5 jdk11_headless
```

Build and test
```sh
bazel build --cxxopt=-std=c++17 //protobuf-matchers:protobuf-matchers-test
```

# Build with CMake

Install dependencies from Conan (optional)
```sh
conan install . -if build -s build_type=Debug
```

Build and test
```sh
cmake -S . -B build -G Ninja -D CMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build --verbose
```
