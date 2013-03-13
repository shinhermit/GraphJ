#include "Color.hpp"

using namespace GraphTypes;

int Color::_HexaStringToInt(const std::string & hexaString)
{
  std::istringstream iss;
  int res;

  iss.setf(std::ios::hex, std::ios::basefield);
  iss.str( std::string("0x") + hexaString );

  iss >> res;

  return res;
}

std::string Color::_IntToHexaString(const int & value,
				    const int & width)
{
  std::ostringstream oss;

  oss.setf(std::ios::hex, std::ios::basefield);
  oss.unsetf ( std::ios::showbase ); //vire le 0x
  oss.fill('0');
  oss.width(width);

  oss << value;

  return oss.str();
}

void Color::_hexaStringToRGB(const std::string & hexaString)
{
  short debut;

  debut = 0;
  _red = _HexaStringToInt( hexaString.substr(debut, 2) );

  debut+=2;
  _green = _HexaStringToInt( hexaString.substr(debut, 2) );

  debut+=2;
  _bleue = _HexaStringToInt( hexaString.substr(debut, 2) );
}

Color::Color()
  :_red(0),
   _green(0),
   _bleue(0)
{}

Color::Color(const ColorIntensity & red,
	     const ColorIntensity & green,
	     const ColorIntensity & bleue)
  :_red(red),
   _green(green),
   _bleue(bleue)
{}

Color::Color(const Color & source)
  :_red(source._red),
   _green(source._green),
   _bleue(source._bleue)
{}

Color::Color(const NamedColor & color)
{
  _hexaStringToRGB( color.toHexa() );
}

Color::Color(const GraphTypes::NamedColor::E_NamedColor & color)
{
  _hexaStringToRGB( GraphTypes::NamedColor::ToHexa(color) );
}

Color::Color(const std::string & hexaString)
{
  _hexaStringToRGB(hexaString);
}

Color & Color::operator=(const Color & source)
{
  _red = source._red;
  _green = source._green;
  _bleue = source._bleue;

  return *this;
}

Color & Color::operator=(const NamedColor & color)
{
  _hexaStringToRGB( color.toHexa() );

  return *this;
}

Color & Color::operator=(const std::string & hexaString)
{
  _hexaStringToRGB(hexaString);

  return *this;
}

bool Color::operator==(const Color & ref)const
{
  return (_red == ref._red && _green == ref._green && _bleue == ref._bleue);
}

bool Color::operator!=(const Color & ref)const
{
  return !operator==(ref);
}

Color & Color::operator+=(const Color & col)
{
  _red += col._red;
  _green += col._green;
  _bleue += col._bleue;

  return *this;
}

Color & Color::operator-=(const Color & col)
{
  _red -= col._red;
  _green -= col._green;
  _bleue -= col._bleue;

  return *this;
}

Color & Color::operator+=(const ColorIntensity & value)
{
  _red += value;
  _green += value;
  _bleue += value;

  return *this;
}

Color & Color::operator-=(const ColorIntensity & value)
{
  _red -= value;
  _green -= value;
  _bleue -= value;

  return *this;
}

Color Color::operator+(const Color & col)const
{
  Color res = *this;

  return res += col;
}

Color Color::operator-(const Color & col)const
{
  Color res = *this;

  return res -= col;
}

Color Color::operator+(const ColorIntensity & value)const
{
  Color res = *this;

  return res += value;
}

Color Color::operator-(const ColorIntensity & value)const
{
  Color res = *this;

  return res -= value;
}

ColorIntensity & Color::red()
{
  return _red;
}

ColorIntensity & Color::green()
{
  return _green;
}

ColorIntensity & Color::bleue()
{
  return _bleue;
}

void Color::setRGB(const ColorIntensity & red, const ColorIntensity & green, const ColorIntensity & bleue)
{
  _red = red;
  _green = green;
  _bleue = bleue;
}

std::string Color::toHexa()const
{
  return _IntToHexaString(_red) + _IntToHexaString(_green) + _IntToHexaString(_bleue);
}

std::string Color::toString()const
{
  return std::string("RGB(")+_red.toString()+", "+_green.toString()+", "+_bleue.toString()+")";
}
