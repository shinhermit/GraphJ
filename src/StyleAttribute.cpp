#include "StyleAttribute.hpp"

using namespace GraphTypes;
using namespace Graphviz;

StyleAttribute::StyleAttribute(const StyleAttribute::E_StyleAttribute & style)
  :_style(style)
{}

StyleAttribute::StyleAttribute(const StyleAttribute & source)
  :_style(source._style)
{}

StyleAttribute & StyleAttribute::operator=(const StyleAttribute::E_StyleAttribute & style)
{
  _style = style;

  return *this;
}

StyleAttribute & StyleAttribute::operator=(const StyleAttribute & source)
{
  _style = source._style;

  return *this;
}

bool StyleAttribute::operator==(const StyleAttribute & ref)const
{
  return (_style == ref._style);
}

bool StyleAttribute::operator==(const E_StyleAttribute & ref)const
{
  return (_style == ref);
}

bool StyleAttribute::operator!=(const StyleAttribute & ref)const
{
  return !operator==(ref);
}

bool StyleAttribute::operator!=(const E_StyleAttribute & ref)const
{
  return !operator==(ref);
}

void StyleAttribute::operator>>(std::ostream & out)const
{
  out << toString();
}

std::ostream & operator<<(std::ostream & out,
			  const StyleAttribute & style)
{
  style >> out;

  return out;
}

std::string StyleAttribute::toString()const
{
  return ToString(_style);
}

StyleAttribute::operator StyleAttribute::E_StyleAttribute()const
{
  return _style;
}

std::string StyleAttribute::ToString(const StyleAttribute::E_StyleAttribute & style)
{
  std::string stylestr;

  switch(style)
    {
    case DEFAULT_STYLE:
      stylestr = "solid";
      break;

    case SOLID:
      stylestr = "solid";
      break;

    case FILLED:
      stylestr = "filled";
      break;

    default:
      stylestr = "Unknown style";
    }

  return stylestr;
}
