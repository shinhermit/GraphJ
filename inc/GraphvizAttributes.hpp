#ifndef _GraphvizAttributes
#define _GraphvizAttributes

#include <string>
#include <sstream>

#include "GraphTypes.hpp"
#include "ShapeAttribute.hpp"
#include "StyleAttribute.hpp"
#include "NamedColor.hpp"

class GraphvizAttributes
{
private:
  std::string _label;

  GraphTypes::Color _fontcolor;

  GraphTypes::Color _color;

  GraphTypes::Graphviz::ShapeAttribute _shape;

  GraphTypes::Graphviz::StyleAttribute _style;

public:
  GraphvizAttributes(const std::string & label="",
		     const GraphTypes::Color & fontcolor=GraphTypes::NamedColor::DefaultColor,
		     const GraphTypes::Color & color=GraphTypes::NamedColor::DefaultColor,
		     const GraphTypes::Graphviz::ShapeAttribute & shape=GraphTypes::Graphviz::ShapeAttribute::DEFAULT_SHAPE,
		     const GraphTypes::Graphviz::StyleAttribute & style=GraphTypes::Graphviz::StyleAttribute::DEFAULT_STYLE);

  const std::string & label()const;

  const GraphTypes::Color & fontcolor()const;

  const GraphTypes::Color & color()const;

  const GraphTypes::Graphviz::ShapeAttribute & shape()const;

  const GraphTypes::Graphviz::StyleAttribute & style()const;

  void setLabel(const std::string & label);

  void setFontColor(const GraphTypes::Color & color);

  void setColor(const GraphTypes::Color & color);

  void setShape(const GraphTypes::Graphviz::ShapeAttribute & shape);

  void setStyle(const GraphTypes::Graphviz::StyleAttribute & style);

  std::string toString()const;

  operator std::string()const;
};

#endif
