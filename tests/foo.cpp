#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::AllOf;
using ::testing::HasSubstr;
using ::testing::ThrowsMessage;


namespace {
TEST(FooTest, Check) { EXPECT_EQ(9, (int)(4 + 5)); }
}  // namespace
