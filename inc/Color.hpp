#ifndef COLOR
#define COLOR

#include <string>
#include <map>
#include <ostream>
#include "CreateMap.hpp"

class Color{
public:
  enum ColorName {Red, Green, Bleu, Yellow, Brown, Violet, Black, White, Orange, Gray, Purlple, Pink};

private:
  ColorName _col;
  static std::map<ColorName, std::string> _toString;

public:
  Color(ColorName col=Black);

  Color & operator>>(std::ostream & out);

  friend std::ostream & operator<<(std::ostream & out, Color & col);

  std::string toString();
};

#endif
