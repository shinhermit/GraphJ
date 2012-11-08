#ifndef EDGESORTER
#define EDGESORTER

#include <set>
#include "Graph.hpp"
#include "WeightedEdge.hpp"
#include "Visitor.hpp"

template<typename Type>
class WeightedEdgeSorter: public Visitor<Type>{
private:
  std::set<WeightedEdge> _edgeSet;

public:

  WeightedEdgeSorter();
  ~WeightedEdgeSorter();

  void treat(Graph<Type> graph, Node::node_id node);

  std::set<WeightedEdge> getEdgeSet();
};

#include "WeightedEdgeSorter.cpp"

#endif
