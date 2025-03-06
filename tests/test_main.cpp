#include <gtest/gtest.h>
#include "mylib.h"

// 测试模块1
TEST(Module1Test, Addition) {
    EXPECT_DOUBLE_EQ(5.0, MyLib::add(2.0, 3.0));
    EXPECT_DOUBLE_EQ(0.0, MyLib::add(1.0, -1.0));
}

TEST(Module1Test, Subtraction) {
    EXPECT_DOUBLE_EQ(2.0, MyLib::subtract(5.0, 3.0));
    EXPECT_DOUBLE_EQ(-2.0, MyLib::subtract(3.0, 5.0));
}

// 测试模块2
TEST(Module2Test, Multiplication) {
    EXPECT_DOUBLE_EQ(6.0, MyLib::multiply(2.0, 3.0));
    EXPECT_DOUBLE_EQ(-6.0, MyLib::multiply(2.0, -3.0));
}

TEST(Module2Test, Division) {
    EXPECT_DOUBLE_EQ(2.0, MyLib::divide(6.0, 3.0));
    EXPECT_DOUBLE_EQ(0.5, MyLib::divide(1.0, 2.0));
    EXPECT_THROW(MyLib::divide(1.0, 0.0), std::invalid_argument);
}

TEST(Module2Test, Power) {
    EXPECT_DOUBLE_EQ(9.0, MyLib::power(3.0, 2.0));
    EXPECT_DOUBLE_EQ(1.0, MyLib::power(5.0, 0.0));
}

// 主测试入口
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 