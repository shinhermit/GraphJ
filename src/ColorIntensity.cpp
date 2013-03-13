#include "ColorIntensity.hpp"

using namespace GraphTypes;

void ColorIntensity::_backToBounds()
{
  if(_value < 0)
    _value = 0;

  else if(_value > 255)
    _value = 255;
}

ColorIntensity::ColorIntensity(const short & value)
  :_value(value)
{
  _backToBounds();
}

ColorIntensity::ColorIntensity(const ColorIntensity & source)
  :_value(source._value)
{}

ColorIntensity & ColorIntensity::operator=(const ColorIntensity & source)
{
  _value = source._value;

  return *this;
}
ColorIntensity & ColorIntensity::operator=(const short & value)
{
  _value = value;

  _backToBounds();

  return *this;
}

ColorIntensity ColorIntensity::operator+(const ColorIntensity & additionnal)const
{
  ColorIntensity res = _value + additionnal._value;

  return res;
}

ColorIntensity ColorIntensity::operator-(const ColorIntensity & reducer)const
{
  ColorIntensity res = _value - reducer._value;

  return res;
}

ColorIntensity ColorIntensity::operator*(const ColorIntensity & multiplier)const
{
  ColorIntensity res = _value * multiplier._value;

  return res;
}

ColorIntensity ColorIntensity::operator/(const ColorIntensity & devider)const
{
  ColorIntensity res = _value / devider._value;

  return res;
}

ColorIntensity ColorIntensity::operator%(const ColorIntensity & devider)const
{
  ColorIntensity res = _value % devider._value;

  return res;
}

ColorIntensity & ColorIntensity::operator+=(const ColorIntensity & additionnal)
{
  _value += additionnal._value;

  _backToBounds();

  return *this;
}

ColorIntensity & ColorIntensity::operator-=(const ColorIntensity & reducer)
{
  _value -= reducer._value;

  _backToBounds();

  return *this;
}

ColorIntensity & ColorIntensity::operator*=(const ColorIntensity & multiplier)
{
  _value *= multiplier._value;

  _backToBounds();

  return *this;
}

ColorIntensity & ColorIntensity::operator/=(const ColorIntensity & devider)
{
  _value /= devider._value;

  _backToBounds();

  return *this;
}

ColorIntensity & ColorIntensity::operator%=(const ColorIntensity & devider)
{
  _value %= devider._value;

  _backToBounds();

  return *this;
}

std::string ColorIntensity::toString()const
{
  std::ostringstream oss;

  oss << _value;

  return oss.str();
}

ColorIntensity::operator short()const
{
  return _value;
}
