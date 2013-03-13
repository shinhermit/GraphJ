#ifndef _GraphTypes_StyleAttribute
#define _GraphTypes_StyleAttribute

#include <iostream>

namespace GraphTypes
{
  namespace Graphviz
  {

    class StyleAttribute
    {
    public:
      enum E_StyleAttribute{DEFAULT_STYLE, SOLID, FILLED};

    private:
      E_StyleAttribute _style;

    public:
      StyleAttribute(const E_StyleAttribute & style=DEFAULT_STYLE);

      StyleAttribute(const StyleAttribute & source);

      StyleAttribute & operator=(const StyleAttribute & source);

      StyleAttribute & operator=(const E_StyleAttribute & style);

      bool operator==(const StyleAttribute & ref)const;

      bool operator==(const E_StyleAttribute & ref)const;

      bool operator!=(const StyleAttribute & ref)const;

      bool operator!=(const E_StyleAttribute & ref)const;

      void operator>>(std::ostream & out)const;
      friend std::ostream & operator<<(std::ostream & out,
				       const StyleAttribute & style);

      std::string toString()const;

      operator E_StyleAttribute()const;

      static std::string ToString(const E_StyleAttribute & style);
    };

  };
};

#endif
