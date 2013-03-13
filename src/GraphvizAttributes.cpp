#include "GraphvizAttributes.hpp"

GraphvizAttributes::GraphvizAttributes(const std::string & label,
				       const GraphTypes::Color & fontcolor,
				       const GraphTypes::Color & color,
				       const GraphTypes::Graphviz::ShapeAttribute & shape,
				       const GraphTypes::Graphviz::StyleAttribute & style)
  :_label(label),
   _fontcolor(fontcolor),
   _color(color),
   _shape(shape),
   _style(style)
{}

const std::string & GraphvizAttributes::label()const
{
  return _label;
}

const GraphTypes::Color & GraphvizAttributes::fontcolor()const
{
  return _fontcolor;
}

const GraphTypes::Color & GraphvizAttributes::color()const
{
  return _color;
}

const GraphTypes::Graphviz::ShapeAttribute & GraphvizAttributes::shape()const
{
  return _shape;
}

const GraphTypes::Graphviz::StyleAttribute & GraphvizAttributes::style()const
{
  return _style;
}

void GraphvizAttributes::setLabel(const std::string & label)
{
  _label = label;
}

void GraphvizAttributes::setFontColor(const GraphTypes::Color & color)
{
  _fontcolor = color;
}

void GraphvizAttributes::setColor(const GraphTypes::Color & color)
{
  _color = color;
}

void GraphvizAttributes::setShape(const GraphTypes::Graphviz::ShapeAttribute & shape)
{
  _shape = shape;
}

void GraphvizAttributes::setStyle(const GraphTypes::Graphviz::StyleAttribute & style)
{
  _style = style;
}

void GraphvizAttributes::clear()
{
  _label.clear();

  _fontcolor = GraphTypes::Color(GraphTypes::NamedColor::DefaultColor);

  _color = GraphTypes::Color(GraphTypes::NamedColor::DefaultColor);

  _shape = GraphTypes::Graphviz::ShapeAttribute::DEFAULT_SHAPE;

  _style = GraphTypes::Graphviz::StyleAttribute::DEFAULT_STYLE;
  
}

void GraphvizAttributes::reset()
{
  clear();
}

std::string GraphvizAttributes::toString()const
{
  std::ostringstream oss;
  bool virgule = false;

  oss << "[";

  if(_label != "")
    {
      oss << "label=\"" << _label << "\"";
      virgule = true;
    }

  if( _fontcolor != GraphTypes::NamedColor(GraphTypes::NamedColor::DefaultColor) )
    {
      if(virgule)
	oss << ", ";

      oss << "fontcolor=\"#" << _fontcolor.toHexa() << "\"";

      virgule = true;
    }

  if( _color != GraphTypes::NamedColor(GraphTypes::NamedColor::DefaultColor) )
    {
      if(virgule)
	oss << ", ";

      oss << "color=\"#" << _color.toHexa() << "\"";

      virgule = true;
    }

  if(_shape != GraphTypes::Graphviz::ShapeAttribute::DEFAULT_SHAPE)
    {
      if(virgule)
	oss << ", ";

      oss << "shape=\"" << _shape.toString() << "\"";

      virgule = true;
    }

  if(_style != GraphTypes::Graphviz::StyleAttribute::DEFAULT_STYLE)
    {
      if(virgule)
	oss << ", ";

      oss << "style=\"" << _style.toString() << "\"";

     virgule = true;
    }

  oss << "]" << std::endl;

  return oss.str();
}

GraphvizAttributes::operator std::string()const
{
  return toString();
}
