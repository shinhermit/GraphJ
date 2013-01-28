#include "ColorizingVisitor.hpp"

using namespace GraphFunctor;

ColorizingVisitor::ColorizingVisitor(std::map<GraphTypes::node_id, GraphTypes::Algorithms::Color> & color_mapper,
				     const GraphTypes::Algorithms::Color & color):
  _color_mapper(color_mapper),
  _color(color)
{}

ColorizingVisitor::~ColorizingVisitor(){}

void ColorizingVisitor::operator()(const GraphTypes::node_id & node)
{
  _color_mapper[node] = _color;
}
