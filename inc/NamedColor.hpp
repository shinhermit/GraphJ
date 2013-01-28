#ifndef _NamedColor
#define _NamedColor

#include <string>
#include <map>
#include <set>
#include <ostream>
#include "CreateMap.hpp"
#include "CreateSet.hpp"

class NamedColor{
public:
  enum ColorName {Red, Green, Blue, Yellow, Brown, Purple, Black, White, Orange, Gray, Pink, Bordeaux};

  typedef std::map<NamedColor::ColorName, std::string>::const_iterator NameToStringIterator;

  typedef std::map<NamedColor::ColorName, unsigned int>::const_iterator NameToHexaIterator;

private:
  ColorName _col;

  static const std::map<ColorName, std::string> _toString;
  static const std::map<ColorName, unsigned int> _hexaValue;

public:
  NamedColor(ColorName col=Black);
  NamedColor(const NamedColor & source);
  NamedColor & operator=(const NamedColor & source);

  void operator>>(std::ostream & out)const;

  friend std::ostream & operator<<(std::ostream & out, const NamedColor & col);

  bool operator==(const NamedColor & ref)const;
  bool operator!=(const NamedColor & ref)const;

  std::string toString()const;

  int hexaValue()const;

  static std::string ToString(const ColorName & color);

  static NameToStringIterator NamesToString_begin();

  static NameToStringIterator NamesToString_end();

  static NameToHexaIterator NamesToHexa_begin();

  static NameToHexaIterator NamesToHexa_end();
};

#endif
