#ifndef _GraphTypes_ColorIncrementor
#define _GraphTypes_ColorIncrementor

#include "Color.hpp"

namespace GraphTypes
{

  class ColorIncrementor
  {
  private:
    Color & _color;
    ColorIntensity _step;

    ColorIntensity _previousGreen;
    ColorIntensity _previousBleue;

    void _inc(const short & step);

  public:
    ColorIncrementor(Color & color, const ColorIntensity & step=16);

    void incrementBy(const ColorIntensity & step);

    void decrementBy(const ColorIntensity & step);

    void next();

    void prev();
  };

};
#endif
