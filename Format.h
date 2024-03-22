#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cstdint> // Necessary for std::uintptr_t
#include <iomanip> // For std::setprecision
#include <typeindex>

namespace fp
{
  /**
   * @brief Generic toString function
   * 
   * @tparam T Type of the value
   * @param value The value to convert to string
   * @return std::string The value as a string
   */
  template <typename T>
  std::string toString(const T &value)
  {
    std::ostringstream oss;
    oss << value;
    return oss.str();
  }

  /**
   * @brief Overload for std::string
   * 
   * @param value The string to convert to string
   * @return std::string The value as a string
   */
  std::string toString(const std::string &value)
  {
    if (value.empty())
      return "(null)";
    return value;
  }

  /**
   * @brief Overload for C-style strings (literal strings)
   * 
   * @param value The C-style string to convert to string
   * @return std::string The value as a string
   */
  std::string toString(const char *value)
  {
    if (!value)
      return "(null)";
    return std::string(value);
  }

  /**
   * @brief Overload for pointers
   * 
   * @tparam T Type of the pointer
   * @param ptr The pointer to convert to string
   * @return std::string The value as a string
   */
  template <typename T>
  std::string toString(T *ptr)
  {
    if (!ptr)
      return "nullptr";
    std::ostringstream oss;
    oss << "0x" << std::hex << reinterpret_cast<std::uintptr_t>(ptr);
    return oss.str();
  }

  /**
   * @brief Overload for float
   * 
   * @param value The float to convert to string
   * @return std::string The value as a string
   */
  std::string toString(float value)
  {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(6) << value;
    return oss.str();
  }

  /**
   * @brief Overload for double
   * 
   * @param value The double to convert to string
   * @return std::string The value as a string
   */
  std::string toString(double value)
  {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(6) << value;
    return oss.str();
  }

  /**
   * @brief Overload for booleans
   * 
   * @param value The boolean to convert to string
   * @return std::string The value as a string
   */
  std::string toString(bool value)
  {
    return value ? "true" : "false";
  }

  /**
   * @brief Overload for unsigned int
   * 
   * @param value The unsigned int to convert to string
   * @return std::string The value as a string
   */
  std::string toString(unsigned int value)
  {
    std::ostringstream oss;
    oss << value;
    return oss.str();
  }

  /**
   * @brief Overload for long
   * 
   * @param value The long to convert to string
   * @return std::string The value as a string
   */
  std::string toString(long value)
  {
    std::ostringstream oss;
    oss << value;
    return oss.str();
  }

  /**
   * @brief Overload for long long
   * 
   * @param value The long long to convert to string
   * @return std::string The value as a string
   */
  std::string toString(long long value)
  {
    std::ostringstream oss;
    oss << value;
    return oss.str();
  }

  /**
   * @brief Overload for unsigned long
   * 
   * @param value The unsigned long to convert to string
   * @return std::string The value as a string
   */
  std::string toString(unsigned long value)
  {
    std::ostringstream oss;
    oss << value;
    return oss.str();
  }

  /**
   * @brief Overload for unsigned long long
   * 
   * @param value The unsigned long long to convert to string
   * @return std::string The value as a string
   */
  std::string toString(unsigned long long value)
  {
    std::ostringstream oss;
    oss << value;
    return oss.str();
  }

  /**
   * @brief Converts a string to hexadecimal
   * 
   * @param n The string to convert
   * @return std::string The hexadecimal representation of the string
   */
  std::string stringToHex(std::string n)
  {
    long num = std::stol(n);
    // Masking to get only the lower 32 bits
    unsigned int maskedNum = static_cast<unsigned int>(num);
    std::stringstream ss;
    ss << "0x" << std::hex << maskedNum;
    return ss.str();
  }

  /**
   * @brief Formats a string with the given arguments
   * 
   * @tparam Args Types of the arguments
   * @param formatString The format string
   * @param args The arguments to format the string with
   * @return std::string The formatted string
   */
  template <typename... Args>
  std::string format(const std::string &formatString, const Args &...args)
  {
    std::vector<std::type_index> argsType = {typeid(args)...};
    std::vector<std::string> argsList = {toString(args)...};
    std::ostringstream oss;
    size_t argIndex = 0;

    for (size_t i = 0; i < formatString.length(); ++i)
    {
      if (formatString[i] == '%')
      {
        if (i + 1 >= formatString.length())
        {
          throw std::runtime_error("Format specifier incomplete at the end of the string.");
        }
        char specifier = formatString[i + 1];
        switch (specifier)
        {
        case 'o':
          if (argIndex >= argsList.size())
          {
            throw std::runtime_error("Too few arguments provided for the format specifiers.");
          }
          oss << argsList[argIndex];
          argIndex++;
          i++; // Skip the specifier character
          break;
        case 'u':
        case 'd':
        case 'i':
          if (argIndex >= argsList.size())
          {
            throw std::runtime_error("Too few arguments provided for the format specifiers.");
          }
          if (argsType[argIndex] != typeid(int) && argsType[argIndex] != typeid(unsigned int) &&
              argsType[argIndex] != typeid(long) && argsType[argIndex] != typeid(long long) &&
              argsType[argIndex] != typeid(unsigned long) && argsType[argIndex] != typeid(unsigned long long))
          {
            throw std::runtime_error("Invalid argument type for format specifier %i: expected int or similar.");
          }
          oss << argsList[argIndex];
          argIndex++;
          i++; // Skip the specifier character
          break;
        case 's':
          if (argIndex >= argsList.size())
          {
            throw std::runtime_error("Too few arguments provided for the format specifiers.");
          }
          if (argsType[argIndex] != typeid(std::string) && argsType[argIndex] != typeid(char *))
          {
            throw std::runtime_error("Invalid argument type for format specifier %s: expected string.");
          }
          oss << argsList[argIndex];
          argIndex++;
          i++; // Skip the specifier character
          break;
        case 'c':
          if (argIndex >= argsList.size())
          {
            throw std::runtime_error("Too few arguments provided for the format specifiers.");
          }
          if (argsType[argIndex] != typeid(char))
          {
            throw std::runtime_error("Invalid argument type for format specifier %c: expected char.");
          }
          oss << argsList[argIndex];
          argIndex++;
          i++; // Skip the specifier character
          break;
        case 'p':
          if (argIndex >= argsList.size())
          {
            throw std::runtime_error("Too few arguments provided for the format specifiers.");
          }
          oss << argsList[argIndex];
          argIndex++;
          i++; // Skip the specifier character
          break;

        case 'f':
        case 'a':
          if (argIndex >= argsList.size())
          {
            throw std::runtime_error("Too few arguments provided for the format specifiers.");
          }
          if (argsType[argIndex] != typeid(float) && argsType[argIndex] != typeid(double))
          {
            throw std::runtime_error("Invalid argument type for format specifier %f: expected float or double.");
          }
          oss << argsList[argIndex];
          argIndex++;
          i++; // Skip the specifier character
          break;
        case 'x':
          if (argIndex >= argsList.size())
          {
            throw std::runtime_error("Too few arguments provided for the format specifiers.");
          }
          if (argsType[argIndex] != typeid(int))
          {
            throw std::runtime_error("Invalid argument type for format specifier %x: expected int.");
          }
          oss << std::hex << std::showbase << std::stoi(argsList[argIndex]);
          argIndex++;
          i++; // Skip the specifier character
          break;
        case 'n':
          if (argIndex >= argsList.size())
          {
            throw std::runtime_error("Too few arguments provided for the format specifiers.");
          }
          if (argsType[argIndex] != typeid(int))
          {
            throw std::runtime_error("Invalid argument type for format specifier %n: expected int.");
          }
          oss << stringToHex(argsList[argIndex]);
          argIndex++;
          i++; // Skip the specifier character
          break;
        case 'b':
          if (argIndex >= argsList.size())
          {
            throw std::runtime_error("Too few arguments provided for the format specifiers.");
          }
          if (argsType[argIndex] != typeid(bool))
          {
            throw std::runtime_error("Invalid argument type for format specifier %b: expected bool.");
          }
          oss << argsList[argIndex];
          argIndex++;
          i++; // Skip the specifier character
          break;
        case '%':
          oss << '%';
          i++; // Skip the next '%'
          break;
        default:
          throw std::runtime_error(std::string("Unsupported format specifier: %") + specifier);
        }
      }
      else
      {
        oss << formatString[i];
      }
    }

    if (argIndex < argsList.size())
    {
      throw std::runtime_error("Too many arguments provided for the format specifiers.");
    }

    return oss.str();
  }
}
