#ifndef _GraphTypes_ShapeAttribute
#define _GraphTypes_ShapeAttribute

#include <iostream>

namespace GraphTypes
{
  namespace Graphviz
  {

    class ShapeAttribute
    {
    public:
      enum E_ShapeAttribute{DEFAULT_SHAPE, ELLIPSE, BOX};

    private:
      E_ShapeAttribute _shape;

    public:
      ShapeAttribute(const E_ShapeAttribute & shape=DEFAULT_SHAPE);

      ShapeAttribute(const ShapeAttribute & source);

      ShapeAttribute & operator=(const ShapeAttribute & source);

      ShapeAttribute & operator=(const E_ShapeAttribute & shape);

      bool operator==(const ShapeAttribute & ref)const;

      bool operator==(const E_ShapeAttribute & ref)const;

      bool operator!=(const ShapeAttribute & ref)const;

      bool operator!=(const E_ShapeAttribute & ref)const;

      void operator>>(std::ostream & out)const;
      friend std::ostream & operator<<(std::ostream & out,
				       const ShapeAttribute & shape);

      std::string toString()const;

      operator E_ShapeAttribute()const;

      static std::string ToString(const E_ShapeAttribute & shape);
    };

  };
};

#endif
