#include "ShapeAttribute.hpp"

using namespace GraphTypes;
using namespace Graphviz;

ShapeAttribute::ShapeAttribute(const ShapeAttribute::E_ShapeAttribute & shape)
  :_shape(shape)
{}

ShapeAttribute::ShapeAttribute(const ShapeAttribute & source)
  :_shape(source._shape)
{}

ShapeAttribute & ShapeAttribute::operator=(const ShapeAttribute::E_ShapeAttribute & shape)
{
  _shape = shape;

  return *this;
}

ShapeAttribute & ShapeAttribute::operator=(const ShapeAttribute & source)
{
  _shape = source._shape;

  return *this;
}

bool ShapeAttribute::operator==(const ShapeAttribute & ref)const
{
  return (_shape == ref._shape);
}

bool ShapeAttribute::operator==(const E_ShapeAttribute & ref)const
{
  return (_shape == ref);
}

bool ShapeAttribute::operator!=(const ShapeAttribute & ref)const
{
  return !operator==(ref);
}

bool ShapeAttribute::operator!=(const E_ShapeAttribute & ref)const
{
  return !operator==(ref);
}

void ShapeAttribute::operator>>(std::ostream & out)const
{
  out << toString();
}

std::ostream & operator<<(std::ostream & out,
			  const ShapeAttribute & shape)
{
  shape >> out;

  return out;
}

std::string ShapeAttribute::toString()const
{
  return ToString(_shape);
}

ShapeAttribute::operator ShapeAttribute::E_ShapeAttribute()const
{
  return _shape;
}

std::string ShapeAttribute::ToString(const ShapeAttribute::E_ShapeAttribute & shape)
{
  std::string shapestr;

  switch(shape)
    {
    case DEFAULT_SHAPE:
      shapestr = "ellipse";
      break;

    case ELLIPSE:
      shapestr = "ellipse";
      break;

    case BOX:
      shapestr = "box";
      break;

    default:
      shapestr = "Unknown shape";
    }

  return shapestr;
}
