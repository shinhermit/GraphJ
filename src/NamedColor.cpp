#include "NamedColor.hpp"

using namespace GraphTypes;

const std::set<NamedColor::E_NamedColor> NamedColor::_iterate = 
  CreateSet<NamedColor::E_NamedColor>
  (NamedColor::DefaultColor)
  (NamedColor::Red)
  (NamedColor::Green)
  (NamedColor::Blue)
  (NamedColor::Yellow)
  (NamedColor::Brown)
  (NamedColor::Purple)
  (NamedColor::Black)
  (NamedColor::White)
  (NamedColor::Orange)
  (NamedColor::Gray)
  (NamedColor::Pink)
  (NamedColor::Bordeaux);

const std::map<NamedColor::E_NamedColor, std::string> NamedColor::_toString =
  CreateMap<NamedColor::E_NamedColor, std::string>
  (NamedColor::DefaultColor, "black")
  (NamedColor::Red, "red")
  (NamedColor::Green, "green")
  (NamedColor::Blue, "blue")
  (NamedColor::Yellow,"yellow")
  (NamedColor::Brown,"brown")
  (NamedColor::Purple,"purple")
  (NamedColor::Black,"black")
  (NamedColor::White,"white")
  (NamedColor::Orange,"orange")
  (NamedColor::Gray,"gray")
  (NamedColor::Pink,"pink")
  (NamedColor::Bordeaux, "bordeaux");

const std::map<NamedColor::E_NamedColor, std::string> NamedColor::_toHexa =
  CreateMap<NamedColor::E_NamedColor, std::string>
  (NamedColor::DefaultColor, "000000")
  (NamedColor::Red, "ff0000")
  (NamedColor::Green, "00ff00")
  (NamedColor::Blue, "0000ff")
  (NamedColor::Yellow, "fff000")
  (NamedColor::Brown, "683100")
  (NamedColor::Purple,"68005d")
  (NamedColor::Black,"000000")
  (NamedColor::White,"ffffff")
  (NamedColor::Orange,"ffa00b")
  (NamedColor::Gray,"727272")
  (NamedColor::Pink,"ff82a5")
  (NamedColor::Bordeaux, "6d0701");

NamedColor::NamedColor(const NamedColor::E_NamedColor & col)
 :_col(col)
{}

NamedColor::NamedColor(const int & intVal)
  :_col( (E_NamedColor)intVal )
{}

NamedColor::NamedColor(const NamedColor & source)
 :_col(source._col)
{}

NamedColor & NamedColor::operator=(const NamedColor::E_NamedColor & col)
{
  _col = col;

  return *this;
}

NamedColor & NamedColor::operator=(const int & intVal)
{
  _col = (E_NamedColor)intVal;

  return *this;
}

NamedColor & NamedColor::operator=(const NamedColor & source)
{
  _col = source._col;

  return *this;
}

void NamedColor::operator>>(std::ostream & out)const
{
  out << toString();
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

std::string NamedColor::toHexa()const
{
  return _toHexa.find(_col)->second;
}

std::string NamedColor::toString()const
{
  return _toString.find(_col)->second;
}

NamedColor::operator NamedColor::E_NamedColor()const
{
  return _col;
}

NamedColor::ColorNameIterator NamedColor::Names_begin()
{
  return _iterate.begin();
}

NamedColor::ColorNameIterator NamedColor::Names_end()
{
  return _iterate.end();
}

std::string NamedColor::ToHexa(const NamedColor::E_NamedColor & color)
{
  return _toHexa.find(color)->second;
}

std::string NamedColor::ToString(const NamedColor::E_NamedColor & color)
{
  return _toString.find(color)->second;
}
