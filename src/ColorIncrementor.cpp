#include "ColorIncrementor.hpp"

using namespace GraphTypes;

ColorIncrementor::ColorIncrementor(Color & color, const ColorIntensity & step)
  :_color(color),
   _step(step),
   _previousGreen( color.green() ),
   _previousBleue( color.bleue() )
{}

void ColorIncrementor::_inc(const short & step)
{
  _color.bleue() = ((short)_color.bleue() + step) % 256;

  _color.green() = ( (short)_color.green() + ((short)_previousBleue/255)*step ) % 256;

  _color.red() = ( (short)_color.red() + ((short)_previousGreen/255)*step ) % 256;

  _previousBleue = _color.bleue();
  _previousGreen = _color.green();
}

void ColorIncrementor::incrementBy(const ColorIntensity & step)
{
  _inc(step);
}

void ColorIncrementor::decrementBy(const ColorIntensity & step)
{
  _inc( -1 * (short)step );
}

void ColorIncrementor::next()
{
  incrementBy(_step);
}

void ColorIncrementor::prev()
{
  decrementBy(_step);
}
