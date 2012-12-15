#ifndef _Coloring
#define _Coloring

#include "Graph.hpp"
#include "WeightedNode.hpp"
#include "NamedColor.hpp"

template<typename Type=GraphTypes::Default>
class Coloring{
private:
  static std::set<WeightedNode> _sort_nodes_by_degrees(Graph<Type> & graph);

  static bool _partite_compatible(Graph<Type> graph, GraphTypes::node_id node, std::set<GraphTypes::node_id> partite);

public:
  static std::map<GraphTypes::node_id, NamedColor::ColorName> welsh(Graph<Type> & graph);
};

#include "Coloring.cpp"

#endif
