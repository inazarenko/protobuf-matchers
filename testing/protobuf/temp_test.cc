
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "testing/protobuf/deleteme.pb.h"

namespace {

using ::testing::HasSubstr;

TEST(MyTest, Basic) {
  ::deleteme::Mess m;
  m.set_id(42);
  EXPECT_THAT(m.DebugString(), HasSubstr("id: 42"));
}

}  // namespace
