#ifndef NAMEDCOLOR
#define NAMEDCOLOR

#include <string>
#include <map>
#include <set>
#include <ostream>
#include "CreateMap.hpp"
#include "CreateSet.hpp"

class NamedColor{
public:
  enum ColorName {Red, Green, Blue, Yellow, Brown, Purple, Black, White, Orange, Gray, Pink, Bordeaux};

private:
  ColorName _col;
  static std::map<ColorName, std::string> _toString;
  static std::map<ColorName, int> _hexaValue;

public:
  NamedColor(ColorName col=Black);

  NamedColor & operator>>(std::ostream & out);

  friend std::ostream & operator<<(std::ostream & out, NamedColor & col);

  std::string toString();
  static std::string ToString(ColorName color);

  int hexaValue();

  static std::set<ColorName> AllNames();
};

#endif
