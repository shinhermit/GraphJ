#ifndef _GraphTypes_ColorIntensity
#define _GraphTypes_ColorIntensity

#include <string>
#include <sstream>

namespace GraphTypes
{

  class ColorIntensity
  {
  private:
    short _value;

    void _backToBounds();

  public:
    ColorIntensity(const short & value=0);
    ColorIntensity(const ColorIntensity & source);

    ColorIntensity & operator=(const ColorIntensity & source);
    ColorIntensity & operator=(const short & value);

    ColorIntensity operator+(const ColorIntensity & additionnal)const;
    ColorIntensity operator-(const ColorIntensity & reducer)const;
    ColorIntensity operator*(const ColorIntensity & multiplier)const;
    ColorIntensity operator/(const ColorIntensity & devider)const;
    ColorIntensity operator%(const ColorIntensity & devider)const;

    ColorIntensity & operator+=(const ColorIntensity & intensity);
    ColorIntensity & operator-=(const ColorIntensity & intensity);
    ColorIntensity & operator*=(const ColorIntensity & intensity);
    ColorIntensity & operator/=(const ColorIntensity & intensity);
    ColorIntensity & operator%=(const ColorIntensity & intensity);

    operator short()const;
    std::string toString()const;
  };

};
#endif
