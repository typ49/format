#include <gtest/gtest.h>

#include "Format.h"

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

TEST(Integer, Simple)
{
  auto str = fp::format("%d", 42);
  EXPECT_EQ(str, "42");
}

TEST(Integer, SimpleLong)
{
  auto str = fp::format("%d", 42L);
  EXPECT_EQ(str, "42");
}

TEST(Integer, SimpleLongLong)
{
  auto str = fp::format("%d", 42LL);
  EXPECT_EQ(str, "42");
}

TEST(Integer, SimpleUnsigned)
{
  auto str = fp::format("%d", 42U);
  EXPECT_EQ(str, "42");
}

TEST(Integer, SimpleUnsignedLong)
{
  auto str = fp::format("%d", 42UL);
  EXPECT_EQ(str, "42");
}

TEST(Integer, SimpleUnsignedLongLong)
{
  auto str = fp::format("%d", 42ULL);
  EXPECT_EQ(str, "42");
}

TEST(Integer, ConstSimple)
{
  const int i = 42;
  auto str = fp::format("%d", i);
  EXPECT_EQ(str, "42");
}

TEST(Integer, ConstSimpleLong)
{
  const long i = 42;
  auto str = fp::format("%d", i);
  EXPECT_EQ(str, "42");
}

TEST(Integer, ConstSimpleLongLong)
{
  const long long i = 42;
  auto str = fp::format("%d", i);
  EXPECT_EQ(str, "42");
}

TEST(Integer, ConstSimpleUnsigned)
{
  const unsigned i = 42;
  auto str = fp::format("%d", i);
  EXPECT_EQ(str, "42");
}

TEST(Integer, ConstSimpleUnsignedLong)
{
  const unsigned long i = 42;
  auto str = fp::format("%d", i);
  EXPECT_EQ(str, "42");
}

TEST(Integer, ConstSimpleUnsignedLongLong)
{
  const unsigned long long i = 42;
  auto str = fp::format("%d", i);
  EXPECT_EQ(str, "42");
}

TEST(Integer, Simple2)
{
  auto str = fp::format("%i", 42);
  EXPECT_EQ(str, "42");
}

TEST(Integer, SimpleLong2)
{
  auto str = fp::format("%i", 42L);
  EXPECT_EQ(str, "42");
}

TEST(Integer, SimpleLongLong2)
{
  auto str = fp::format("%i", 42LL);
  EXPECT_EQ(str, "42");
}

TEST(Integer, SimpleUnsigned2)
{
  auto str = fp::format("%i", 42U);
  EXPECT_EQ(str, "42");
}

TEST(Integer, SimpleUnsignedLong2)
{
  auto str = fp::format("%i", 42UL);
  EXPECT_EQ(str, "42");
}

TEST(Integer, SimpleUnsignedLongLong2)
{
  auto str = fp::format("%i", 42ULL);
  EXPECT_EQ(str, "42");
}

TEST(Integer, ConstSimple2)
{
  const int i = 42;
  auto str = fp::format("%i", i);
  EXPECT_EQ(str, "42");
}

TEST(Integer, ConstSimpleLong2)
{
  const long i = 42;
  auto str = fp::format("%i", i);
  EXPECT_EQ(str, "42");
}

TEST(Integer, ConstSimpleLongLong2)
{
  const long long i = 42;
  auto str = fp::format("%i", i);
  EXPECT_EQ(str, "42");
}

TEST(Integer, ConstSimpleUnsigned2)
{
  const unsigned i = 42;
  auto str = fp::format("%i", i);
  EXPECT_EQ(str, "42");
}

TEST(Integer, ConstSimpleUnsignedLong2)
{
  const unsigned long i = 42;
  auto str = fp::format("%i", i);
  EXPECT_EQ(str, "42");
}

TEST(Integer, ConstSimpleUnsignedLongLong2)
{
  const unsigned long long i = 42;
  auto str = fp::format("%i", i);
  EXPECT_EQ(str, "42");
}

TEST(Integer, Negative)
{
  auto str = fp::format("%d", -42);
  EXPECT_EQ(str, "-42");
}

TEST(Integer, Negative2)
{
  auto str = fp::format("%i", -42);
  EXPECT_EQ(str, "-42");
}

TEST(Hexadecimal, Simple)
{
  auto str = fp::format("%x", 42);
  EXPECT_EQ(str, "0x2a");
}

TEST(Hexadecimal, SimpleLong)
{
  auto str = fp::format("%x", 42L);
  EXPECT_EQ(str, "0x2a");
}

TEST(Hexadecimal, SimpleLongLong)
{
  auto str = fp::format("%x", 42LL);
  EXPECT_EQ(str, "0x2a");
}

TEST(Hexadecimal, SimpleUnsigned)
{
  auto str = fp::format("%x", 42U);
  EXPECT_EQ(str, "0x2a");
}

TEST(Hexadecimal, SimpleUnsignedLong)
{
  auto str = fp::format("%x", 42UL);
  EXPECT_EQ(str, "0x2a");
}

TEST(Hexadecimal, SimpleUnsignedLongLong)
{
  auto str = fp::format("%x", 42ULL);
  EXPECT_EQ(str, "0x2a");
}

TEST(Hexadecimal, ConstSimple)
{
  const int i = 42;
  auto str = fp::format("%x", i);
  EXPECT_EQ(str, "0x2a");
}

TEST(Hexadecimal, ConstSimpleLong)
{
  const long i = 42;
  auto str = fp::format("%x", i);
  EXPECT_EQ(str, "0x2a");
}

TEST(Hexadecimal, ConstSimpleLongLong)
{
  const long long i = 42;
  auto str = fp::format("%x", i);
  EXPECT_EQ(str, "0x2a");
}

TEST(Hexadecimal, ConstSimpleUnsigned)
{
  const unsigned i = 42;
  auto str = fp::format("%x", i);
  EXPECT_EQ(str, "0x2a");
}

TEST(Hexadecimal, ConstSimpleUnsignedLong)
{
  const unsigned long i = 42;
  auto str = fp::format("%x", i);
  EXPECT_EQ(str, "0x2a");
}

TEST(Hexadecimal, ConstSimpleUnsignedLongLong)
{
  const unsigned long long i = 42;
  auto str = fp::format("%x", i);
  EXPECT_EQ(str, "0x2a");
}

TEST(Hexadecimal, Zero)
{
  auto str = fp::format("%x", 0);
  EXPECT_EQ(str, "0x0");
}

TEST(Hexadecimal, Negative)
{
  auto str = fp::format("%x", -1);
  EXPECT_EQ(str, "0xffffffff");
}

TEST(Float, Simple)
{
  auto str = fp::format("%f", 3.141592);
  EXPECT_EQ(str, "3.141592");
}

TEST(Float, Negative)
{
  auto str = fp::format("%f", -3.141592);
  EXPECT_EQ(str, "-3.141592");
}

TEST(Float, Approx)
{
  auto str = fp::format("%f", 3.1415927);
  EXPECT_EQ(str, "3.141593");
}

TEST(Float, Without6Decimal)
{
  auto str = fp::format("%f", 42.0);
  EXPECT_EQ(str, "42.000000");
}

TEST(Boolean, True)
{
  auto str = fp::format("%b", true);
  EXPECT_EQ(str, "true");
}

TEST(Boolean, False)
{
  auto str = fp::format("%b", false);
  EXPECT_EQ(str, "false");
}

TEST(String, Simple)
{
  auto str = fp::format("%s", "Hello");
  EXPECT_EQ(str, "Hello");
}

TEST(String, Null)
{
  auto str = fp::format("%s", "");
  EXPECT_EQ(str, "");
}

TEST(Char, Simple)
{
  auto str = fp::format("%c", 'A');
  EXPECT_EQ(str, "A");
}

TEST(Pointer, Integer)
{
  int i = 42;
  auto str = fp::format("%p", &i);
  std::ostringstream oss;
  oss << &i;
  std::string expectedAddress = oss.str();
  EXPECT_EQ(str, expectedAddress);
}

TEST(Pointer, Float)
{
  float f = 3.14;
  auto str = fp::format("%p", &f);
  std::ostringstream oss;
  oss << &f;
  std::string expectedAddress = oss.str();
  EXPECT_EQ(str, expectedAddress);
}

TEST(Pointer, String)
{
  std::string s = "Hello";
  auto str = fp::format("%p", &s);
  std::ostringstream oss;
  oss << &s;
  std::string expectedAddress = oss.str();
  EXPECT_EQ(str, expectedAddress);
}

TEST(Format, One)
{
  // auto str = fp::format("One %");
  // EXPECT_EQ(str, "One %");
  try
  {
    auto str = fp::format("One %!", "Hello");
  }
  catch (const std::runtime_error &e)
  {
    std::cout << e.what() << std::endl;
  }
}

TEST(FormatPrint, CustomTypeToString)
{
  try
  {
    auto str = fp::format("%o", "foo");
    EXPECT_EQ(str, "foo");
  }
  catch (const std::runtime_error &e)
  {
    std::cout << e.what() << std::endl;
  }
}

TEST(FormatPrint, Oui)
{
  auto str = fp::format("%d%%i", 100);
  EXPECT_EQ(str, "100%i");
}

TEST(Generic, Long)
{
  long l = 42;
  try
  {
    auto str = fp::format("%i", l);
  }
  catch (const std::runtime_error &e)
  {
    std::cout << e.what() << std::endl;
  }
}

TEST(Exemple, Exemple)
{
  auto str = fp::format("%s %s!", "Hello", "World");
  EXPECT_EQ(str, "Hello World!");

  str = fp::format("The cake is lie!");
  EXPECT_EQ(str, "The cake is lie!");

  str = fp::format("The Answer is %d", 42);
  EXPECT_EQ(str, "The Answer is 42");

  str = fp::format("Approx of %s is %f", "Pi", 3.141592);
  EXPECT_EQ(str, "Approx of Pi is 3.141592");

  str = fp::format("%d in hexadecimal %x", 42, 42);
  EXPECT_EQ(str, "42 in hexadecimal 0x2a");

  str = fp::format("'%c' is the 1st alphabet letter", 'A');
  EXPECT_EQ(str, "'A' is the 1st alphabet letter");

  str = fp::format("This sentence is %b", false);
  EXPECT_EQ(str, "This sentence is false");

  my::Foo foo = {8};
  str = fp::format("%o", foo);
  EXPECT_EQ(str, "8");

  str = fp::format("%p", &foo);
  std::ostringstream oss;
  oss << &foo;
  std::string expectedAddress = oss.str();
  EXPECT_EQ(str, expectedAddress);

  str = fp::format("No substitution: %%i");
  EXPECT_EQ(str, "No substitution: %i");

  try
  {
    str = fp::format("Too many arguments", 10);
  }
  catch (const std::runtime_error &e)
  {
    std::cout << e.what() << std::endl;
  }

  try
  {
    str = fp::format("Missing argument: %d");
  }
  catch (const std::runtime_error &e)
  {
    std::cout << e.what() << std::endl;
  }
}

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
