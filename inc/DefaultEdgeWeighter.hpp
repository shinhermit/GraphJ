#ifndef _DefaultEdgeWeighter
#define _DefaultEdgeWeighter

#include "EdgeWeighter.hpp"

namespace GraphFunctor
{

  template<typename Type=GraphTypes::Default>
  struct DefaultEdgeWeighter : public EdgeWeighter<Type>
  {
    GraphTypes::Cost operator()(const Graph<Type> & graph,
				const GraphTypes::node_id & sourceNode,
				const GraphTypes::node_id & targetNode)const;
  };

};

#include "DefaultEdgeWeighter.cpp"

#endif
