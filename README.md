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
