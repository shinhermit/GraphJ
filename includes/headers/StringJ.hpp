#ifndef _StringJ
#define _StringJ

#include <string>
#include <sstream>

class StringJ
{
public:

  template<typename Litteral>
  static std::string From(const Litteral & val)
  {
    std::ostringstream oss;

    oss << val;

    return oss.str();
  }

  template<typename Litteral>
  static Litteral To(const std::string & str)
  {
    std::istringstream iss(str);
    Litteral val;
    
    iss >> val;
    return val;
  }
};

#endif
