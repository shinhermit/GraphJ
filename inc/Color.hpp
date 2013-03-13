#ifndef _GraphTypes_Color
#define _GraphTypes_Color

#include <string>
#include <sstream>
#include <iostream>
#include "ColorIntensity.hpp"
#include "NamedColor.hpp"

namespace GraphTypes
{

  class Color
  {
  private:
    ColorIntensity _red;
    ColorIntensity _green;
    ColorIntensity _bleue;

    static int _HexaStringToInt(const std::string & hexaString);
    static std::string _IntToHexaString(const int & value,
					const int & width=2);
    void _hexaStringToRGB(const std::string & hexaString);

  public:
    Color();

    Color(const ColorIntensity & red,
	  const ColorIntensity & green,
	  const ColorIntensity & bleue);

    Color(const Color & source);

    Color(const GraphTypes::NamedColor & color);
    Color(const GraphTypes::NamedColor::E_NamedColor & color);
    Color(const std::string & hexaString);

    Color & operator=(const Color & source);
    Color & operator=(const NamedColor & color);
    Color & operator=(const std::string & hexaString);

    bool operator==(const Color & ref)const;
    bool operator!=(const Color & ref)const;

    Color operator+(const Color & col)const;
    Color operator-(const Color & col)const;

    Color operator+(const ColorIntensity & value)const;
    Color operator-(const ColorIntensity & value)const;

    Color & operator+=(const Color & col);
    Color & operator-=(const Color & col);

    Color & operator+=(const ColorIntensity & value);
    Color & operator-=(const ColorIntensity & value);

    ColorIntensity & red();
    ColorIntensity & green();
    ColorIntensity & bleue();

    void setRGB(const ColorIntensity & red, const ColorIntensity & green, const ColorIntensity & bleue);

    std::string toHexa()const;
    std::string toString()const;
  };

};

#endif
