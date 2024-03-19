#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cstdint> // Nécessaire pour std::uintptr_t
#include <iomanip> // Pour std::setprecision

namespace fp
{

  // Fonction générique toString
  template <typename T>
  std::string toString(const T &value)
  {
    std::ostringstream oss;
    oss << value;
    return oss.str();
  }

  // Surcharge pour les chaînes de caractères
  std::string toString(const std::string &value)
  {
    if (value.empty())
      return "(null)";
    return value;
  }

  // Surcharge pour les chaînes de caractères C-style (chaînes littérales)
  std::string toString(const char *value)
  {
    if (!value)
      return "(null)";
    return std::string(value);
  }

  // Surcharge pour les pointeurs
  template <typename T>
  std::string toString(T *ptr)
  {
    if (!ptr)
      return "nullptr";
    std::ostringstream oss;
    oss << "0x" << std::hex << reinterpret_cast<std::uintptr_t>(ptr);
    return oss.str();
  }

  // Surcharge pour float
  std::string toString(float value)
  {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(6) << value;
    return oss.str();
  }

  // Surcharge pour double
  std::string toString(double value)
  {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(6) << value;
    return oss.str();
  }

  // Surcharge pour booléens
  std::string toString(bool value)
  {
    return value ? "true" : "false";
  }

  std::string stringToHex(std::string n)
  {
    long num = std::stol(n);
    // Masquage pour obtenir seulement les 32 bits inférieurs
    unsigned int maskedNum = static_cast<unsigned int>(num);
    std::stringstream ss;
    ss << "0x" << std::hex << maskedNum;
    return ss.str();
  }

  template <typename... Args>
  std::string format(const std::string &formatString, const Args &...args)
  {
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
        case 'd':
        case 'i':
        case 'u':
        case 'o':
        case 'x':
        case 'X':
        case 'f':
        case 'F':
        case 'a':
        case 'A':
        case 'c':
        case 's':
        case 'p':
        case 'n':
        case 'b':
          if (argIndex >= argsList.size())
          {
            throw std::runtime_error("Too few arguments provided for the format specifiers.");
          }
          if (specifier == 'x' || specifier == 'X')
          {
            oss << stringToHex(argsList[argIndex]);
          }
          else
          {
            oss << argsList[argIndex];
          }
          if (specifier == 'b')
          {
            if (argsList[argIndex] == "1")
            {
              oss << "true";
            }
            else if (argsList[argIndex] == "0")
            {
              oss << "false";
            }
            argIndex++;
            i++;      // Avance pour passer le spécificateur de format.
            continue; // Passe au prochain caractère dans formatString sans exécuter les parties suivantes de la boucle.
          }

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
