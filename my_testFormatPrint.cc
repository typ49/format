#include <gtest/gtest.h>

#include "Format.h"

namespace My {
  struct Foo {
    int i;
  };
  std::string to_string(const Foo& foo) {
    return std::to_string(foo.i);
  }

  std::ostream& operator<<(std::ostream& os, const Foo& foo) {
    os << foo.i;
    return os;
  }
}

TEST(FormatGood, BasicTest)
{
  std::string formatString = "The value of x is x";
  std::string result = fp::format(formatString);
  EXPECT_EQ(result, "The value of x is x");
}

TEST(FormatGood, IntTest)
{
  std::string formatString = "The value of x is %d";
  int x = 5;
  std::string result = fp::format(formatString, x);
  EXPECT_EQ(result, "The value of x is 5");
}

TEST(FormatGood, FloatTest)
{
  std::string formatStringf = "The value of x is %f";
  std::string formatStringF = "The value of x is %F";
  float x = 5.5;
  std::string result = fp::format(formatStringf, x);
  EXPECT_EQ(result, "The value of x is 5.500000");
  result = fp::format(formatStringF, x);
  EXPECT_EQ(result, "The value of x is 5.500000");
}

TEST(FormatGood, StringTest)
{
  std::string formatString = "The value of x is %s";
  std::string x = "666 the devil number";
  std::string result = fp::format(formatString, x);
  EXPECT_EQ(result, "The value of x is 666 the devil number");
}

TEST(FormatGood, PointerTest)
{
  std::string formatString = "The value of x is %p";
  int x = 5;
  std::string result = fp::format(formatString, &x);
  std::string address = "The value of x is " + fp::toString(&x);
  EXPECT_EQ(result, address);
}

TEST(FormatGood, testChar)
{
  std::string formatString = "The value of x is %c";
  char x = '5';
  std::string result = fp::format(formatString, x);
  EXPECT_EQ(result, "The value of x is 5");
}

TEST(FormatGood, testHex)
{
  std::string formatString = "The value of x is %x";
  int x = 5;
  int y = 10;
  int z = 15;
  int a = 16;
  std::string result = fp::format(formatString, x);
  EXPECT_EQ(result, "The value of x is 0x5");
  result = fp::format(formatString, y);
  EXPECT_EQ(result, "The value of x is 0xa");
  result = fp::format(formatString, z);
  EXPECT_EQ(result, "The value of x is 0xf");
  result = fp::format(formatString, a);
  EXPECT_EQ(result, "The value of x is 0x10");
}

TEST(FormatGood, UserDefinedTypeTest)
{
  std::string formatString = "The value of x is %d";
  My::Foo x = {5};
  std::string result = fp::format(formatString, x);
  EXPECT_EQ(result, "The value of x is 5");
}

TEST(FormatGood, UserDefinedTypeAddresseTest)
{
  std::string formatString = "The value of x is %p";
  My::Foo x = {5};
  std::string result = fp::format(formatString, &x);
  std::string address = "The value of x is " + fp::toString(&x);
  EXPECT_EQ(result, address);
}

TEST(FormatGood, MultipleArgsTest)
{
  int i = 5;
  float f = 5.123456;
  char c = 'c';
  int x = 42;
  std::string s = "string";
  std::string formatString = "I panic, I put everything : %d, %i, %f, %x, %c, %s, %p";
  std::string result = fp::format(formatString, i, i, f, x, c, s, &i);
  std::string address = "I panic, I put everything : 5, 5, 5.123456, 0x2a, c, string, " + fp::toString(&i);
  EXPECT_EQ(result, address);
}

TEST(FormatGood, NoSubstitutionTest)
{
  std::string formatString = "I panic, I put everything : %%d, %%i, %%f, %%x, %%c, %%s, %%p";
  std::string result = fp::format(formatString);
  std::string address = "I panic, I put everything : %d, %i, %f, %x, %c, %s, %p";
  EXPECT_EQ(result, address);
}

/************************************************************
 * Test cases for wrong format                              *
 ************************************************************/

TEST(FormatWrong, testFloatOverLimit)
{
  std::string formatStringf = "The value of x is %f";
  std::string formatStringF = "The value of x is %F";
  float x = 5.1234567890;
  EXPECT_EQ(fp::format(formatStringf, x), "The value of x is 5.123457");
}

TEST(FormatWrong, testPercentOnly) {
  std::string formatString = "I love %";
  EXPECT_THROW(fp::format(formatString), std::runtime_error);
}

TEST (FormatWrong, testUnknownSpecifier) {
  std::string formatString = "Tell me %y";
  EXPECT_THROW(fp::format(formatString), std::runtime_error);
}

TEST (FormatWrong, testNoMatchingSpecifiers) {
  std::string formatString = "I panic, I put everything : %d, %i, %f, %x, %c, %s, %p";
  int i = 5;
  std::string s = "kirbo";
  EXPECT_THROW(fp::format(formatString, s, s, s, s, i ,i, i), std::invalid_argument);
}

TEST (FormatWrong, testNoArgumentPassed) {
  std::string formatString = "I panic, I put everything : %d, %i, %f, %x, %c, %s, %p";
  EXPECT_THROW(fp::format(formatString), std::runtime_error);

}

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
