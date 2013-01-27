#ifndef _Acm
#define _Acm

#include <vector>
#include <algorithm>
#include "Graph.hpp"
#include "GraphFunctor.hpp"
#include "Traverse.hpp"

template<typename Type=GraphTypes::Default>
class Acm{
private:
  //for Kruskal's algorithm
  static void _color_each_node(const Graph<Type> & graph, std::map<GraphTypes::node_id, GraphTypes::Algorithms::Color> & color_mapper);

  static void _update_colors(const Graph<> & acm, std::map<GraphTypes::node_id, GraphTypes::Algorithms::Color> & color_mapper, const GraphTypes::node_id & node1, const GraphTypes::node_id & node2);

  //for Prim's algorithm
  static void _init_tables(const Graph<Type> & graph, std::map<GraphTypes::node_id, GraphTypes::Cost> & distance, std::map<GraphTypes::node_id, GraphTypes::node_id> & predecessor);
				      
  static void _update_tables(const Graph<Type> & graph, const Graph<Type> & acm, const GraphTypes::node_id & closest, std::map<GraphTypes::node_id, GraphTypes::Cost> & distance, std::map<GraphTypes::node_id, GraphTypes::node_id> & predecessor);

public:
  static Graph<> Kruskal(const Graph<Type> & graph) throw(GraphException::InvalidOperation, GraphException::InvalidEdge, GraphException::InvalidNodeID);

  static Graph<> Prim(const Graph<Type> & graph) throw(GraphException::InvalidOperation, GraphException::InvalidEdge, GraphException::InvalidNodeID);
};

#include "Acm.cpp"

#endif
