#ifndef _WeightedEdgeComparator
#define _WeightedEdgeComparator

#include "Graph.hpp"

namespace GraphFunctor
{

  template<typename Type>
  class WeightedEdgeComparator
  {
  private:
    const Graph<Type> & _graph;

  public:
    WeightedEdgeComparator(const Graph<Type> & graph);

    bool operator()(const Edge & edge1, const Edge & edge2);
  };

};

#include "WeightedEdgeComparator.cpp"

#endif
