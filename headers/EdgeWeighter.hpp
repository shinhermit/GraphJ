#ifndef _EdgeWeighter
#define _EdgeWeighter

#include "Graph.hpp"
#include "GraphTypes.hpp"

namespace GraphFunctor
{

  template<typename Type=GraphTypes::Default>
  struct EdgeWeighter
  {
    virtual GraphTypes::Cost operator()(const Graph<Type> & graph,
					const GraphTypes::node_id & sourceNode,
					const GraphTypes::node_id & targetNode
					)const=0;
  };

}

#endif
