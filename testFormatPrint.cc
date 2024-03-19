#include <gtest/gtest.h>

#include "Format.h"

TEST(Format, onlyFormat)
{
  std::string result = fp::format("%d", 42);
  EXPECT_EQ(result, "42");
}

TEST(Format, noFormat)
{
  std::string result = fp::format("Test");
  EXPECT_EQ(result, "Test");
}

TEST(Format, onlyPercent)
{
  std::string result = fp::format("%%");
  EXPECT_EQ(result, "%");
}

TEST(Format, formatInt)
{
  std::string result = fp::format("Test %d", 42);
  EXPECT_EQ(result, "Test 42");

  result = fp::format("Test %i", 69);
  EXPECT_EQ(result, "Test 69");
}

TEST(Format, formatString1)
{
  std::string result = fp::format("Test %s", "Hello");
  EXPECT_EQ(result, "Test Hello");
}

TEST(Format, formatString2)
{
  std::string p = "Hello";
  std::string result = fp::format("Test %s", p);
  EXPECT_EQ(result, "Test Hello");
}

TEST(Format, formatString3)
{
  char p[6] = "Hello";
  std::string result = fp::format("Test %s", p);
  EXPECT_EQ(result, "Test Hello");
}

TEST(Format, formatChar)
{
  std::string result = fp::format("Test %c", 'A');
  EXPECT_EQ(result, "Test A");
}

TEST(Format, formatFloat)
{
  std::string result = fp::format("Test %f", 3.14f);
  EXPECT_EQ(result, "Test 3.140000");
}

TEST(Format, formatDouble)
{
  std::string result = fp::format("Test %f", 3.1415926);
  EXPECT_EQ(result, "Test 3.141593");
}

TEST(Format, formatPointer)
{
  int *ptr = nullptr;
  std::string result = fp::format("Test %p", ptr);
  EXPECT_EQ(result, "Test 0x0");
}

TEST(Format, formatHex)
{
  std::string result = fp::format("Test %x", 42);
  EXPECT_EQ(result, "Test 2a");
}

TEST(Format, formatBool)
{
  std::string result = fp::format("Test %b", true);
  EXPECT_EQ(result, "Test true");
}

namespace my
{
  struct Foo
  {
    int i;
  };
  std::string to_string(const Foo &foo)
  {
    return std::to_string(foo.i);
  }

  // Définition de l'opérateur << pour my::Foo
  std::ostream &operator<<(std::ostream &os, const Foo &foo)
  {
    os << foo.i; // ou toute autre représentation de Foo que vous souhaitez imprimer
    return os;
  }
}

TEST(Format, formatGeneric)
{
  my::Foo foo{42};
  std::string result = fp::format("Test %o", foo);
  EXPECT_EQ(result, "Test 42");
}

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
