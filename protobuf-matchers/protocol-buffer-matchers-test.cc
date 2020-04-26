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
using ::protobuf_matchers::proto::IgnoringFieldPaths;
using ::protobuf_matchers::proto::IgnoringFields;
using ::protobuf_matchers::proto::IgnoringRepeatedFieldOrdering;
using ::protobuf_matchers::proto::Partially;
using ::protobuf_matchers::proto::TreatingNaNsAsEqual;
using ::protobuf_matchers::proto::WhenDeserialized;
using ::protobuf_matchers::proto::WhenDeserializedAs;
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

TEST(Matchers, IgnoringFields) {
  TestMessage m;
  m.set_name("foo");
  m.set_id(12);

  EXPECT_THAT(m, IgnoringFields({"protobuf_matchers.TestMessage.id"},
                                EqualsProto("name: 'foo' id: 13")));
  EXPECT_THAT(m, IgnoringFields({"protobuf_matchers.TestMessage.name"},
                                EqualsProto("id: 12")));
}

TEST(Matchers, IgnoringFieldPaths) {
  TestMessage m;
  m.set_name("foo");
  m.set_id(12);

  EXPECT_THAT(m, IgnoringFieldPaths({"id"}, EqualsProto("name: 'foo' id: 13")));
  EXPECT_THAT(m, IgnoringFieldPaths({"name"}, EqualsProto("id: 12")));
}

TEST(Matchers, IgnoringFieldPathsNested) {
  Container c;
  c.mutable_singular()->set_id(13);
  c.mutable_singular()->set_name("bar");

  EXPECT_THAT(
      c, IgnoringFieldPaths({"singular.name"},
                            EqualsProto("singular { name: 'foo' id: 13 }")));
}

TEST(Matchers, IgnoringFieldPathsRepeatedIndex) {
  Container c;
  c.add_plural()->set_id(10);
  c.add_plural()->set_id(20);

  EXPECT_THAT(
      c, IgnoringFieldPaths({"plural[0].id"},
                            EqualsProto("plural {id: 11} plural {id: 20}")));
}

TEST(Matchers, IgnoringFieldPathsRepeatedNested) {
  Container c;
  c.add_plural()->set_id(10);
  c.add_plural()->set_id(20);

  EXPECT_THAT(
      c, IgnoringFieldPaths({"plural.id"},
                            EqualsProto("plural {id: 11} plural {id: 21}")));
}

TEST(Matchers, IgnoringRepeatedFieldOrdering) {
  Container c;
  c.add_xs(10);
  c.add_xs(20);

  EXPECT_THAT(c, IgnoringRepeatedFieldOrdering(EqualsProto("xs: 20 xs: 10")));
}

TEST(Matchers, IgnoringRepeatedFieldOrderingNested) {
  Container c;
  c.add_plural()->set_id(10);
  c.add_plural()->set_id(20);

  EXPECT_THAT(c, IgnoringRepeatedFieldOrdering(
                     EqualsProto("plural {id: 20} plural {id: 10}")));
}

TEST(Matchers, Partially) {
  TestMessage m;
  m.set_name("foo");
  m.set_id(12);

  EXPECT_THAT(m, Partially(EqualsProto("id: 12")));
  EXPECT_THAT(m, Partially(EqualsProto("name: 'foo'")));
}

TEST(Matchers, WhenDeserialized) {
  TestMessage m;
  m.set_name("foo");
  m.set_id(12);
  std::string bytes = m.SerializeAsString();

  EXPECT_THAT(bytes, WhenDeserialized(EqualsProto(m)));
  EXPECT_THAT(bytes, WhenDeserializedAs<TestMessage>(
                         EqualsProto("id: 12 name: 'foo'")));
}

}  // namespace
}  // namespace protobuf_matchers
