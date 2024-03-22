#include <gtest/gtest.h>
#include <cstdint>
#include <iostream>

#include "Format.h"

// We gonna use the model into the subject (examples for tests)

namespace my {
  struct Foo {
    int i;
  };
  std::string to_string(const Foo& foo) {
    return std::to_string(foo.i);
  }

  std::ostream &operator<<(std::ostream &os, const Foo &foo)
  {
    os << foo.i;
    return os;
  }
}

TEST(FormatTest, ExampleWithASimpleInteger) {
  auto str = fp::format("The Anwser is %d", 42);
  EXPECT_EQ("The Anwser is 42", str);
}

TEST(FormatTest, ExampleWithASimpleIntegerAndHexa) {
  auto str = fp::format("%d in hexa is %x", 42, 42);
  EXPECT_EQ("42 in hexa is 0x2a", str);
}

TEST(FormatTest, ExampleWithHelloWorld) {
  auto str = fp::format("Hello world !");
  EXPECT_EQ("Hello world !", str);
}

TEST(FormatTest, ExampleWithHelloWorldwithStrings) {
  std::cout << typeid("hello").name() << std::endl;
  std::cout << typeid(std::string).name() << std::endl;
  std::cout << typeid(char *).name() << std::endl;
  std::cout << typeid(const char *).name() << std::endl;
  std::cout << typeid(char[6]).name() << std::endl;
  std::cout << typeid(char[]).name() << std::endl;
  auto str = fp::format("%s %s !", "Hello", "world");
  EXPECT_EQ("Hello world !", str);
}

TEST(FormatTest, WholeAlphabet) {
  auto str = fp::format("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 
                          'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 
                          'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 
                          'u', 'v', 'w', 'x', 'y', 'z');
  EXPECT_EQ("abcdefghijklmnopqrstuvwxyz", str);
}

TEST(FormatTest, YourLifeIsALie) {
  auto str = fp::format("%s %b", "Your life is a lie, no that's", false);
  EXPECT_EQ("Your life is a lie, no that's false", str);
}

TEST(FormatTest, NoSub) {
  auto str = fp::format("This sentence is 100%% true");
  EXPECT_EQ("This sentence is 100% true", str);
}

TEST(FormatTest, NoSubTwice) {
  auto str = fp::format("This sentence is 100%%%% true");
  EXPECT_EQ("This sentence is 100\%\% true", str);
}

TEST(FormatTest, ExampleWithFloatingPointNumber) {
  auto str = fp::format("The value of pi is approximately %f", 3.14159);
  EXPECT_EQ("The value of pi is approximately 3.141590", str);
}

TEST(FormatTest, ExampleWithBoolean) {
  auto str1 = fp::format("Is it sunny today? %b", true);
  auto str2 = fp::format("Is it raining tomorrow? %b", false);
  EXPECT_EQ("Is it sunny today? true", str1);
  EXPECT_EQ("Is it raining tomorrow? false", str2);
}

TEST(FormatTest, ExampleWithCharacter) {
  auto str = fp::format("The first letter of the alphabet is %c", 'a');
  EXPECT_EQ("The first letter of the alphabet is a", str);
}

TEST(FormatTest, ExampleWithPointer) {
  int x = 42;
  int* ptr = &x;
  auto str = fp::format("The value at address %p is %d", ptr, *ptr);
  std::stringstream ss;
  ss << std::hex << reinterpret_cast<std::uintptr_t>(ptr);
  std::string address = ss.str();
  EXPECT_EQ("The value at address 0x" + address + " is 42", str);
}

TEST(FormatTest, ExampleWithCustomTypeAdress) {
  my::Foo foo{42};
  auto str = fp::format("The answer to everything is %p", &foo);
  std::stringstream ss;
  ss << std::hex << reinterpret_cast<std::uintptr_t>(&foo);
  std::string address = ss.str();
  EXPECT_EQ("The answer to everything is 0x" + address, str);
}

TEST(FormatTest, ExampleWithCustomTypeRealValue) {
  my::Foo foo{42};
  auto str = fp::format("The answer to everything is %o", foo);
  EXPECT_EQ("The answer to everything is 42", str);
}

TEST(FormatTest, ExampleWithInvalidSpecifier1) {
  EXPECT_THROW(fp::format("Invalid specifier: %z", 42), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidSpecifier2) {
  my::Foo foo{42};
  EXPECT_THROW(fp::format("Invalid specifier: %z", foo), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidSpecifier3) {
  EXPECT_THROW(fp::format("Invalid specifier: %z"), std::runtime_error);
}

TEST(FormatTest, ExampleWithSpaceSpecifier1) {
  EXPECT_THROW(fp::format("Invalid specifier: % i", 42), std::runtime_error);
}

TEST(FormatTest, ExampleWithSpaceSpecifier2) {
  EXPECT_THROW(fp::format("Invalid specifier: % i"), std::runtime_error);
}

TEST(FormatTest, ExampleWithConsecutiveSpecifier1) {
  EXPECT_EQ("%%%%",fp::format("%%%%%%%%"));
}

TEST(FormatTest, ExampleWithConsecutiveSpecifier2) {
  EXPECT_EQ("%%%%i",fp::format("%%%%%%%%i"));
}

TEST(FormatTest, ExampleWithConsecutiveSpecifier3) {
  EXPECT_EQ("%%%%81",fp::format("%%%%%%%%%i",81));
}

TEST(FormatTest, ExampleWithConsecutiveSpecifierError1) {
  EXPECT_THROW(fp::format("%%%%%%%%i",81), std::runtime_error);
}

TEST(FormatTest, ExampleWithConsecutiveSpecifierError2) {
  EXPECT_THROW(fp::format("%%%%%%%%%i"), std::runtime_error);
}

TEST(FormatTest, ExampleWithSpecifierAtTheEnd1) {
  EXPECT_THROW(fp::format("Invalid specifier: %", 42), std::runtime_error);
}

TEST(FormatTest, ExampleWithSpecifierAtTheEnd2) {
  EXPECT_THROW(fp::format("Invalid specifier: %"), std::runtime_error);
}

TEST(FormatTest, ExampleWithExtraArguments) {
  EXPECT_THROW(fp::format("The value is %d", 42, 24), std::runtime_error);
}

TEST(FormatTest, ExampleWithNullString) {
  char* ptr = nullptr;
  auto str = fp::format("The pointer value is %p", ptr);
  EXPECT_EQ("The pointer value is 0x0", str);
}

TEST(FormatTest, ExampleWithInvalidCharacter) {
  EXPECT_THROW(fp::format("Invalid character: %c%c%c", "abc"), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeIntChar) {
  EXPECT_THROW(fp::format("Invalid integer: %i", 'a'), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeIntChar2) {
  EXPECT_THROW(fp::format("Invalid integer: %d", 'a'), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeIntBool) {
  EXPECT_THROW(fp::format("Invalid integer: %i", false), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeIntBool2) {
  EXPECT_THROW(fp::format("Invalid integer: %d", false), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeIntFloat) {
  EXPECT_THROW(fp::format("Invalid integer: %i", 1.0f), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeIntFloat2) {
  EXPECT_THROW(fp::format("Invalid integer: %d", 1.0f), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeIntString) {
  EXPECT_THROW(fp::format("Invalid integer: %i", "error"), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeIntString2) {
  EXPECT_THROW(fp::format("Invalid integer: %d", "error"), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeIntPtr) {
  int* ptr = nullptr;
  EXPECT_THROW(fp::format("Invalid integer: %i", ptr), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeIntPtr2) {
  int* ptr = nullptr;
  EXPECT_THROW(fp::format("Invalid integer: %d", ptr), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeIntFoo) {
  my::Foo foo{81};
  EXPECT_THROW(fp::format("Invalid integer: %i", foo), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeIntFoo2) {
  my::Foo foo{81};
  EXPECT_THROW(fp::format("Invalid integer: %d", foo), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeHexaChar) {
  EXPECT_THROW(fp::format("Invalid integer: %x", 'a'), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeHexaBool) {
  EXPECT_THROW(fp::format("Invalid integer: %x", false), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeHexaFloat) {
  EXPECT_THROW(fp::format("Invalid integer: %x", 1.0f), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeHexaString) {
  EXPECT_THROW(fp::format("Invalid integer: %x", "error"), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeHexaPtr) {
  int* ptr = nullptr;
  EXPECT_THROW(fp::format("Invalid integer: %x", ptr), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeHexaFoo) {
  my::Foo foo{81};
  EXPECT_THROW(fp::format("Invalid integer: %x", foo), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeFloatChar) {
  EXPECT_THROW(fp::format("Invalid float: %f", 'a'), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeFloatInt) {
  EXPECT_THROW(fp::format("Invalid float: %f", 81), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeFloatBool) {
  EXPECT_THROW(fp::format("Invalid float: %f", false), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeFloatString) {
  EXPECT_THROW(fp::format("Invalid float: %f", "error"), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeFloatPtr) {
  float* ptr = nullptr;
  EXPECT_THROW(fp::format("Invalid float: %f", ptr), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeFloatFoo) {
  my::Foo foo{81};
  EXPECT_THROW(fp::format("Invalid float: %f", foo), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeBoolChar) {
  EXPECT_THROW(fp::format("Invalid boolean: %b", 'a'), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeBoolInt) {
  EXPECT_THROW(fp::format("Invalid boolean: %b", 81), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeBoolFloat) {
  EXPECT_THROW(fp::format("Invalid boolean: %b", 1.0f), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeBoolString) {
  EXPECT_THROW(fp::format("Invalid boolean: %b", "error"), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeBoolPtr) {
  bool* ptr = nullptr;
  EXPECT_THROW(fp::format("Invalid boolean: %b", ptr), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeBoolFoo) {
  my::Foo foo{81};
  EXPECT_THROW(fp::format("Invalid boolean: %b", foo), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeStringChar) {
  EXPECT_THROW(fp::format("Invalid string: %s", 'a'), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeStringInt) {
  EXPECT_THROW(fp::format("Invalid string: %s", 81), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeStringFloat) {
  EXPECT_THROW(fp::format("Invalid string: %s", 1.0f), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeStringBool) {
  EXPECT_THROW(fp::format("Invalid string: %s", false), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeStringPtr) {
  std::string* ptr = nullptr;
  EXPECT_THROW(fp::format("Invalid string: %s", ptr), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeStringFoo) {
  my::Foo foo{81};
  EXPECT_THROW(fp::format("Invalid string: %s", foo), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeCharInt) {
  EXPECT_THROW(fp::format("Invalid char: %c", 8), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeCharFloat) {
  EXPECT_THROW(fp::format("Invalid char: %c", 1.0f), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeCharBool) {
  EXPECT_THROW(fp::format("Invalid char: %c", false), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeCharString) {
  EXPECT_THROW(fp::format("Invalid char: %c", "error"), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeCharPtr) {
  char* ptr = nullptr;
  EXPECT_THROW(fp::format("Invalid char: %c", ptr), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeCharFoo) {
  my::Foo foo{81};
  EXPECT_THROW(fp::format("Invalid char: %c", foo), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypePtrChar) {
  EXPECT_THROW(fp::format("Invalid pointer: %p", 'a'), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypePtrInt) {
  EXPECT_THROW(fp::format("Invalid pointer: %p", 81), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypePtrFloat) {
  EXPECT_THROW(fp::format("Invalid pointer: %p", 1.0f), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypePtrBool) {
  EXPECT_THROW(fp::format("Invalid pointer: %p", false), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypePtrString) {
  EXPECT_THROW(fp::format("Invalid pointer: %p", "error"), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypePtrFoo) {
  my::Foo foo{81};
  EXPECT_THROW(fp::format("Invalid pointer: %p", foo), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeObjectChar) {
  EXPECT_THROW(fp::format("Invalid object: %o", 'a'), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeObjectInt) {
  EXPECT_THROW(fp::format("Invalid object: %o", 81), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeObjectFloat) {
  EXPECT_THROW(fp::format("Invalid object: %o", 1.0f), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeObjectBool) {
  EXPECT_THROW(fp::format("Invalid object: %o", false), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeObjectString) {
  EXPECT_THROW(fp::format("Invalid object: %o", "error"), std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeObjectPtr) {
  my::Foo* ptr = nullptr;
  EXPECT_THROW(fp::format("Invalid object: %o", ptr), std::runtime_error);
}

TEST(FormatTest, ExampleWithEveryType) {
  my::Foo* ptr = nullptr;
  my::Foo foo{81};
  EXPECT_EQ("811.000000every81true0x51a0x081",fp::format("%i%f%s%d%b%x%c%p%o", 81,1.0f,"every",81,true,81,'a',ptr,foo));
}

TEST(FormatTest, ExampleWithInvalidType) {
  my::Foo* ptr = nullptr;
  my::Foo foo{81};
  EXPECT_THROW(fp::format("%i%f%s%d%b%x%c%p%o", 81,1.0f,'a',81,false,81,'a',ptr,foo), std::runtime_error);
}

TEST(FormatTest, ExampleWithTooFewParameters) {
  my::Foo* ptr = nullptr;
  EXPECT_THROW(fp::format("%i%f%s%d%b%x%c%p%o", 81,1.0f,"error",81,false,81,'a',ptr), std::runtime_error);
}

TEST(FormatTest, ExampleWithTooMuchParameters) {
  my::Foo* ptr = nullptr;
  my::Foo foo{81};
  EXPECT_THROW(fp::format("%i%f%s%d%b%x%c%p%o", 81,1.0f,"error",81,false,81,'a',ptr,foo,"Error Error Error ErrorError ErrorError ErrorError ErrorError ErrorError ErrorError ErrorError ErrorError ErrorError ErrorError ErrorError ErrorError Error"), std::runtime_error);
}

TEST(FormatTest, ExampleWithEmptyParametersInt1) {
  EXPECT_THROW(fp::format("%i"), std::runtime_error);
}

TEST(FormatTest, ExampleWithEmptyParametersInt2) {
  EXPECT_THROW(fp::format("%d"), std::runtime_error);
}

TEST(FormatTest, ExampleWithEmptyParametersHexa) {
  EXPECT_THROW(fp::format("%x"), std::runtime_error);
}

TEST(FormatTest, ExampleWithEmptyParametersFloat) {
  EXPECT_THROW(fp::format("%f"), std::runtime_error);
}

TEST(FormatTest, ExampleWithEmptyParametersBool) {
  EXPECT_THROW(fp::format("%b"), std::runtime_error);
}

TEST(FormatTest, ExampleWithEmptyParametersString) {
  EXPECT_THROW(fp::format("%s"), std::runtime_error);
}

TEST(FormatTest, ExampleWithEmptyParametersChar) {
  EXPECT_THROW(fp::format("%c"), std::runtime_error);
}

TEST(FormatTest, ExampleWithEmptyParametersPtr) {
  EXPECT_THROW(fp::format("%p"), std::runtime_error);
}

TEST(FormatTest, ExampleWithEmptyParametersObject) {
  EXPECT_THROW(fp::format("%o"), std::runtime_error);
}

TEST(FormatTest, ExampleWithTooFewParametersInt1) {
  EXPECT_THROW(fp::format("%i%i",81), std::runtime_error);
}

TEST(FormatTest, ExampleWithTooFewParametersInt2) {
  EXPECT_THROW(fp::format("%d%d",81), std::runtime_error);
}

TEST(FormatTest, ExampleWithTooFewParametersHexa) {
  EXPECT_THROW(fp::format("%x%x",81), std::runtime_error);
}

TEST(FormatTest, ExampleWithTooFewParametersFloat) {
  EXPECT_THROW(fp::format("%f%f",1.0f), std::runtime_error);
}

TEST(FormatTest, ExampleWithTooFewParametersBool) {
  EXPECT_THROW(fp::format("%b%b",false), std::runtime_error);
}

TEST(FormatTest, ExampleWithTooFewParametersString) {
  EXPECT_THROW(fp::format("%s%s","error"), std::runtime_error);
}

TEST(FormatTest, ExampleWithTooFewParametersChar) {
  EXPECT_THROW(fp::format("%c%c",'a'), std::runtime_error);
}

TEST(FormatTest, ExampleWithTooFewParametersPtr) {
  my::Foo* ptr1 = nullptr;
  EXPECT_THROW(fp::format("%p%p",ptr1), std::runtime_error);
}

TEST(FormatTest, ExampleWithTooFewParametersObject) {
  my::Foo foo1{81};
  EXPECT_THROW(fp::format("%o%o",foo1), std::runtime_error);
}

TEST(FormatTest, ExampleWithTooMuchParametersInt1) {
  EXPECT_THROW(fp::format("%i%i",81,8,42), std::runtime_error);
}

TEST(FormatTest, ExampleWithTooMuchParametersInt2) {
  EXPECT_THROW(fp::format("%d%d",81,8,42), std::runtime_error);
}

TEST(FormatTest, ExampleWithTooMuchParametersHexa) {
  EXPECT_THROW(fp::format("%x%x",81,8,42), std::runtime_error);
}

TEST(FormatTest, ExampleWithTooMuchParametersFloat) {
  EXPECT_THROW(fp::format("%f%f",1.0f,81.81f,42.42f), std::runtime_error);
}

TEST(FormatTest, ExampleWithTooMuchParametersBool) {
  EXPECT_THROW(fp::format("%b%b",true,true,false), std::runtime_error);
}

TEST(FormatTest, ExampleWithTooMuchParametersString) {
  EXPECT_THROW(fp::format("%s%s","good","awesome","error"), std::runtime_error);
}

TEST(FormatTest, ExampleWithTooMuchParametersChar) {
  EXPECT_THROW(fp::format("%c%c",'a','g','f'), std::runtime_error);
}

TEST(FormatTest, ExampleWithTooMuchParametersPtr) {
  my::Foo* ptr1 = nullptr;
  int* ptr2 = nullptr;
  char* ptr3 = nullptr;
  EXPECT_THROW(fp::format("%p%p",ptr1,ptr2,ptr3), std::runtime_error);
}

TEST(FormatTest, ExampleWithTooMuchParametersObject) {
  my::Foo foo1{81};
  my::Foo foo2{8};
  my::Foo foo3{42};
  EXPECT_THROW(fp::format("%o%o",foo1,foo2,foo3), std::runtime_error);
}

TEST(FormatTest, ExampleWithUnsignedLong) {
  unsigned long n=81;
  EXPECT_EQ("81",fp::format("%i",n));
}

TEST(FormatTest, ExampleWithLong) {
  long n=81;
  EXPECT_EQ("81",fp::format("%i",n));
}

TEST(FormatTest, ExampleWithUnsigned) {
  unsigned n=81;
  EXPECT_EQ("81",fp::format("%i",n));
}

TEST(FormatTest, ExampleWithUnsignedInt) {
  unsigned int n=81;
  EXPECT_EQ("81",fp::format("%i",n));
}

TEST(FormatTest, ExampleWithUnsignedShort) {
  unsigned short n=81;
  EXPECT_EQ("81",fp::format("%i",n));
}

TEST(FormatTest, ExampleWithShort) {
  short n=81;
  EXPECT_EQ("81",fp::format("%i",n));
}

TEST(FormatTest, ExampleWithUnsignedLong2) {
  unsigned long n=81;
  EXPECT_EQ("81",fp::format("%d",n));
}

TEST(FormatTest, ExampleWithLong2) {
  long n=81;
  EXPECT_EQ("81",fp::format("%d",n));
}

TEST(FormatTest, ExampleWithUnsigned2) {
  unsigned n=81;
  EXPECT_EQ("81",fp::format("%d",n));
}

TEST(FormatTest, ExampleWithUnsignedInt2) {
  unsigned int n=81;
  EXPECT_EQ("81",fp::format("%d",n));
}

TEST(FormatTest, ExampleWithUnsignedShort2) {
  unsigned short n=81;
  EXPECT_EQ("81",fp::format("%d",n));
}

TEST(FormatTest, ExampleWithShort2) {
  short n=81;
  EXPECT_EQ("81",fp::format("%d",n));
}

TEST(FormatTest, ExampleWithUnsignedLongHex) {
  unsigned long n=81;
  EXPECT_EQ("0x51",fp::format("%x",n));
}

TEST(FormatTest, ExampleWithLongHex) {
  long n=81;
  EXPECT_EQ("0x51",fp::format("%x",n));
}

TEST(FormatTest, ExampleWithUnsignedHex) {
  unsigned n=81;
  EXPECT_EQ("0x51",fp::format("%x",n));
}

TEST(FormatTest, ExampleWithUnsignedIntHex) {
  unsigned int n=81;
  EXPECT_EQ("0x51",fp::format("%x",n));
}

TEST(FormatTest, ExampleWithUnsignedShortHex) {
  unsigned short n=81;
  EXPECT_EQ("0x51",fp::format("%x",n));
}

TEST(FormatTest, ExampleWithShortHex) {
  short n=81;
  EXPECT_EQ("0x51",fp::format("%x",n));
}

TEST(FormatTest, ExampleWithInvalidTypeFloatUnsignedLong) {
  unsigned long n=81;
  EXPECT_THROW(fp::format("%f",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeFloatLong) {
  long n=81;
  EXPECT_THROW(fp::format("%f",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeFloatUnsigned) {
  unsigned n=81;
  EXPECT_THROW(fp::format("%f",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeFloatUnsignedInt) {
  unsigned int n=81;
  EXPECT_THROW(fp::format("%f",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeFloatUnsignedShort) {
  unsigned short n=81;
  EXPECT_THROW(fp::format("%f",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeFloatShort) {
  short n=81;
  EXPECT_THROW(fp::format("%f",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeBoolUnsignedLong) {
  unsigned long n=81;
  EXPECT_THROW(fp::format("%b",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeBoolLong) {
  long n=81;
  EXPECT_THROW(fp::format("%b",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeBoolUnsigned) {
  unsigned n=81;
  EXPECT_THROW(fp::format("%b",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeBoolUnsignedInt) {
  unsigned int n=81;
  EXPECT_THROW(fp::format("%b",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeBoolUnsignedShort) {
  unsigned short n=81;
  EXPECT_THROW(fp::format("%b",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeBoolShort) {
  short n=81;
  EXPECT_THROW(fp::format("%b",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeStringUnsignedLong) {
  unsigned long n=81;
  EXPECT_THROW(fp::format("%s",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeStringLong) {
  long n=81;
  EXPECT_THROW(fp::format("%s",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeStringUnsigned) {
  unsigned n=81;
  EXPECT_THROW(fp::format("%s",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeStringUnsignedInt) {
  unsigned int n=81;
  EXPECT_THROW(fp::format("%s",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeStringUnsignedShort) {
  unsigned short n=81;
  EXPECT_THROW(fp::format("%s",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeStringShort) {
  short n=81;
  EXPECT_THROW(fp::format("%s",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeCharUnsignedLong) {
  unsigned long n=81;
  EXPECT_THROW(fp::format("%c",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeCharLong) {
  long n=81;
  EXPECT_THROW(fp::format("%c",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeCharUnsigned) {
  unsigned n=81;
  EXPECT_THROW(fp::format("%c",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeCharUnsignedInt) {
  unsigned int n=81;
  EXPECT_THROW(fp::format("%c",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeCharUnsignedShort) {
  unsigned short n=81;
  EXPECT_THROW(fp::format("%c",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeCharShort) {
  short n=81;
  EXPECT_THROW(fp::format("%c",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypePtrUnsignedLong) {
  unsigned long n=81;
  EXPECT_THROW(fp::format("%p",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypePtrLong) {
  long n=81;
  EXPECT_THROW(fp::format("%p",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypePtrUnsigned) {
  unsigned n=81;
  EXPECT_THROW(fp::format("%p",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypePtrUnsignedInt) {
  unsigned int n=81;
  EXPECT_THROW(fp::format("%p",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypePtrUnsignedShort) {
  unsigned short n=81;
  EXPECT_THROW(fp::format("%p",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypePtrShort) {
  short n=81;
  EXPECT_THROW(fp::format("%p",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeObjectUnsignedLong) {
  unsigned long n=81;
  EXPECT_THROW(fp::format("%o",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeObjectLong) {
  long n=81;
  EXPECT_THROW(fp::format("%o",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeObjectUnsigned) {
  unsigned n=81;
  EXPECT_THROW(fp::format("%o",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeObjectUnsignedInt) {
  unsigned int n=81;
  EXPECT_THROW(fp::format("%o",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeObjectUnsignedShort) {
  unsigned short n=81;
  EXPECT_THROW(fp::format("%o",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeObjectShort) {
  short n=81;
  EXPECT_THROW(fp::format("%o",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithDouble) {
  double n=81.500000;
  EXPECT_EQ("81.500000",fp::format("%f",n));
}

TEST(FormatTest, ExampleWithInvalidTypeIntDouble) {
  double n=81.500000;
  EXPECT_THROW(fp::format("%i",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeIntDouble2) {
  double n=81.500000;
  EXPECT_THROW(fp::format("%d",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeHexaDouble) {
  double n=81.500000;
  EXPECT_THROW(fp::format("%x",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeBoolDouble) {
  double n=81.500000;
  EXPECT_THROW(fp::format("%b",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeStringDouble) {
  double n=81.500000;
  EXPECT_THROW(fp::format("%s",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeCharDouble) {
  double n=81.500000;
  EXPECT_THROW(fp::format("%c",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypePointerDouble) {
  double n=81.500000;
  EXPECT_THROW(fp::format("%p",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithInvalidTypeObjectDouble) {
  double n=81.500000;
  EXPECT_THROW(fp::format("%o",n),std::runtime_error);
}

TEST(FormatTest, ExampleWithPI){
  EXPECT_EQ("Approx of Pi is 3.141592",fp::format("Approx of %s is %f", "Pi", 3.141592));
}

TEST(FormatTest, ExampleWithNullptr){
  my::Foo* ptr = nullptr;
  EXPECT_EQ("0x0",fp::format("%p",ptr));
}

TEST(FormatTest, ExampleWithEmpty){
  EXPECT_EQ("",fp::format(""));
}

TEST(FormatTest, ExampleWithEmptyError){
  EXPECT_THROW(fp::format("","erreur"),std::runtime_error);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
