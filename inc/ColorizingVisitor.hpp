#ifndef _ColorizingVisitor
#define _ColorizingVisitor

#include <map>
#include "Visitor.hpp"
#include "GraphTypes.hpp"

namespace GraphFunctor
{

  class ColorizingVisitor : public Visitor
  {
  private:
    std::map<GraphTypes::node_id, GraphTypes::Algorithms::Color> & _color_mapper;

    const GraphTypes::Algorithms::Color & _color;

  public:
    ColorizingVisitor(std::map<GraphTypes::node_id, GraphTypes::Algorithms::Color> & color_mapper,
		      const GraphTypes::Algorithms::Color & col);

    ~ColorizingVisitor();

    void operator()(const GraphTypes::node_id & node);
  };

};

#endif
