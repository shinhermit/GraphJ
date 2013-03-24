#ifndef _PathFindingValidator
#define _PathFindingValidator

#include "EdgeWeighter.hpp"

namespace GraphFunctor
{

  template<typename Type>
  struct PathFindingValidator
  {
    bool operator()(const Graph<Type> & graph,
		    const GraphFunctor::EdgeWeighter<Type> & CostFunctor,
		    const std::map<GraphTypes::node_id, GraphTypes::Cost> & distances);
  };

};

#include "PathFindingValidator.cpp"

#endif
