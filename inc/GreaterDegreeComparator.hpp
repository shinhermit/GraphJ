#ifndef _GreaterDegreeComparator
#define _GreaterDegreeComparator

#include "Graph.hpp"

namespace GraphFunctor
{

  template<typename Type>
  class GreaterDegreeComparator
  {
  private:
    const Graph<Type> & _graph;

  public:
    GreaterDegreeComparator(const Graph<Type> & graph);

    bool operator()(const GraphTypes::node_id & node1,
		    const GraphTypes::node_id & node2);
  };

};

#include "GreaterDegreeComparator.cpp"

#endif
