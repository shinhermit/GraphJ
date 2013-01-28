#include "NamedColor.hpp"

const std::map<NamedColor::ColorName, std::string> NamedColor::_toString = CreateMap<NamedColor::ColorName, std::string>(NamedColor::Red, "red")(NamedColor::Green, "green")(NamedColor::Blue, "blue")(NamedColor::Yellow,"yellow")(NamedColor::Brown,"brown")(NamedColor::Purple,"purple")(NamedColor::Black,"black")(NamedColor::White,"white")(NamedColor::Orange,"orange")(NamedColor::Gray,"gray")(NamedColor::Pink,"pink")(NamedColor::Bordeaux, "bordeaux");

const std::map<NamedColor::ColorName, unsigned int> NamedColor::_hexaValue = CreateMap<NamedColor::ColorName, unsigned int>(NamedColor::Red, 0xff0000)(NamedColor::Green, 0x00ff00)(NamedColor::Blue, 0x0000ff)(NamedColor::Yellow, 0xfff000)(NamedColor::Brown, 0x683100)(NamedColor::Purple,0x68005d)(NamedColor::Black,0x000000)(NamedColor::White,0xffffff)(NamedColor::Orange,0xffa00b)(NamedColor::Gray,0x727272)(NamedColor::Pink,0xff82a5)(NamedColor::Bordeaux, 0x6d0701);

NamedColor::NamedColor(NamedColor::ColorName col):_col(col){}

NamedColor::NamedColor(const NamedColor & source):_col(source._col){}

NamedColor & NamedColor::operator=(const NamedColor & source)
{
  _col = source._col;

  return *this;
}

void NamedColor::operator>>(std::ostream & out)const
{
  out << _toString.find(_col)->second;
}

std::ostream & operator<<(std::ostream & out, const NamedColor & col)
{
  col >> out;

  return out;
}

bool NamedColor::operator==(const NamedColor & ref)const
{
  return _col == ref._col;
}

bool NamedColor::operator!=(const NamedColor & ref)const
{
  return !operator==(ref);
}

std::string NamedColor::toString()const
{
  return _toString.find(_col)->second;
}

int NamedColor::hexaValue()const
{
  return _hexaValue.find(_col)->second;
}

std::string NamedColor::ToString(const NamedColor::ColorName & color)
{
  return _toString.find(color)->second;
}

NamedColor::NameToStringIterator NamedColor::NamesToString_begin()
{
  return _toString.begin();
}

NamedColor::NameToStringIterator NamedColor::NamesToString_end()
{
  return _toString.end();
}

NamedColor::NameToHexaIterator NamedColor::NamesToHexa_begin()
{
  return _hexaValue.begin();
}

NamedColor::NameToHexaIterator NamedColor::NamesToHexa_end()
{
  return _hexaValue.end();
}
