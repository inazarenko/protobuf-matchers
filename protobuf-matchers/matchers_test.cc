
/*
 * Copyright 2020 Igor Nazarenko
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "protobuf-matchers/protocol-buffer-matchers.h"

#include <iostream>
#include <type_traits>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "protobuf-matchers/test.pb.h"

namespace protobuf_matchers {
namespace {

using ::protobuf_matchers::proto::Approximately;
using ::protobuf_matchers::proto::TreatingNaNsAsEqual;
using ::testing::Not;

TEST(Matchers, EqualsProto) {
  TestMessage m;
  m.set_id(42);
  m.set_name("foo");

  TestMessage expected = m;
  EXPECT_THAT(m, EqualsProto(expected));
  EXPECT_THAT(m, EqualsProto("id: 42 name: 'foo'"));
  EXPECT_THAT(m, Not(EqualsProto("id: 43 name: 'foo'")));
}

TEST(Matchers, EquivToProto) {
  TestMessage m;
  m.set_name("foo");

  TestMessage expected = m;
  expected.set_id(0);
  EXPECT_THAT(m, EquivToProto(expected));
  EXPECT_THAT(m, EquivToProto("id: 0 name: 'foo'"));
  EXPECT_THAT(m, EquivToProto("name: 'foo'"));
}

TEST(Matchers, Approximately) {
  TestMessage m;
  m.set_weight(1.0);

  EXPECT_THAT(m, Approximately(EqualsProto("weight: 0.999"), 0.01));
  EXPECT_THAT(m, Not(Approximately(EqualsProto("weight: 0.9"), 0.01)));
}

TEST(Matchers, TreatingNaNsAsEqual) {
  TestMessage m;
  m.set_weight(0.0 / 0.0);

  EXPECT_THAT(m, TreatingNaNsAsEqual(EqualsProto("weight: nan")));
  EXPECT_THAT(m, Not(EqualsProto("weight: nan")));
}

}  // namespace
}  // namespace protobuf_matchers
