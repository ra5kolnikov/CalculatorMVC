#include <gtest/gtest.h>
// #include "../Calc/ThirdParty/parser/parser.h"

extern "C" {
#include "../Calc/ThirdParty/parser/parser.h"
}

TEST(CoreTest, Test1) {
  char str[255] = "(tan(-2^4)^2)*5/3+(ln(sqrt(25))-(sin(-4)))";
  float res = calculator(str, 0);
  float res_orig = 1.0032683253667286;
  EXPECT_NEAR(res_orig, res, 1e-07);
}

TEST(CoreTest, Test2) {
  char str[255] = "(asin(1)-(sin(-1)))";
  float res = calculator(str, 0);
  float res_orig = 2.41226731;
  EXPECT_NEAR(res_orig, res, 1e-07);
}

TEST(CoreTest, Test3) {
  char str[255] = "(acos(x)-(sin(1)))";
  float res = calculator(str, 0);
  float res_orig = 0.72932534;
  EXPECT_NEAR(res_orig, res, 1e-07);
}

TEST(CoreTest, Test4) {
  char str[255] = "asin(x)-atan(x)+acos(x)";
  float x = 1;
  float res = calculator(str, x);
  float res_orig = 0.78539816;
  EXPECT_NEAR(res_orig, res, 1e-07);
}

TEST(CoreTest, Test5) {
  char str[255] = "sin(x)+16-3^8";
  float x = 0.5;
  float res = calculator(str, x);
  float res_orig = -6544.52057446;
  EXPECT_NEAR(res_orig, res, 1e-07);
}

TEST(CoreTest, Test6) {
  char str[255] = "-(-8*9.0)";
  float res = calculator(str, 0);
  float res_orig = 72.00000000;
  EXPECT_NEAR(res_orig, res, 1e-07);
}

TEST(CoreTest, Test7) {
  char str[255] = "(-2)";
  float res = calculator(str, 0);
  float res_orig = -2.0000000000000;
  EXPECT_NEAR(res_orig, res, 1e-07);
}

TEST(CoreTest, Test8) {
  char str[255] = "(2*x)-(sin(x))";
  float x = 1;
  float res = calculator(str, x);
  float res_orig = 1.15852902;
  EXPECT_NEAR(res_orig, res, 1e-07);
}

TEST(CoreTest, Test10) {
  char str[255] = "sqrt(x)";
  float x = 100;
  float res = calculator(str, x);
  float res_orig = 10.00000000;
  EXPECT_NEAR(res_orig, res, 1e-07);
}

TEST(CoreTest, Test16) {
  char str[255] = "53mod2";
  float res = calculator(str, 0);
  float res_orig = 1.00000000;
  EXPECT_NEAR(res_orig, res, 1e-07);
}

TEST(CoreTest, Test17) {
  char str[255] = "cos(0.5)+log(53)";
  float res = calculator(str, 0);
  float res_orig = 2.60185843;
  EXPECT_NEAR(res_orig, res, 1e-07);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
