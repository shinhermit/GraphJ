#ifndef _NamedColor
#define _NamedColor

#include <string>
#include <map>
#include <set>
#include <iostream>
#include "CreateMap.hpp"
#include "CreateSet.hpp"

namespace GraphTypes
{

  class NamedColor{
  public:
    enum E_NamedColor {DefaultColor, Red, Green, Blue, Yellow, Brown, Purple, Black, White, Orange, Gray, Pink, Bordeaux};

    typedef std::set<E_NamedColor>::const_iterator ColorNameIterator;

  private:
    E_NamedColor _col;

    static const std::set<E_NamedColor> _iterate;
    static const std::map<E_NamedColor, std::string> _toString;
    static const std::map<E_NamedColor, std::string> _toHexa;

  public:
    NamedColor(const E_NamedColor & col=Black);
    NamedColor(const int & intVal);
    NamedColor(const NamedColor & source);

    NamedColor & operator=(const E_NamedColor & col);
    NamedColor & operator=(const int & intVal);
    NamedColor & operator=(const NamedColor & source);

    void operator>>(std::ostream & out)const;

    friend std::ostream & operator<<(std::ostream & out,
				     const NamedColor & col);

    bool operator==(const NamedColor & ref)const;
    bool operator!=(const NamedColor & ref)const;

    std::string toHexa()const;

    std::string toString()const;

    operator E_NamedColor()const;

    static ColorNameIterator Names_begin();

    static ColorNameIterator Names_end();

    static std::string ToHexa(const E_NamedColor & color);
    static std::string ToString(const E_NamedColor & color);
  };

};

#endif
