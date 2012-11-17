#ifndef _Acm
#define _Acm

#include "Graph.hpp"
#include "WeightedEdge.hpp"

template<typename Type>
class Acm{
private:
  //for Kurskal's algorithm
  static std::map<Node::node_id, unsigned long> _color_each_node(Graph<Type> & graph);

  static void _update_colors(Graph<Type> & graph, Graph<Type> & acm, std::map<Node::node_id, unsigned long> & color_mapper, Node::node_id node1, Node::node_id node2);

  static std::set<WeightedEdge> _sort_edges_by_weights(Graph<Type> & graph);

  //for Prim's algorithm
  static std::set<WeightedEdge> _weightedNeighboursFromSuccessors(Graph<Type> graph, Node::node_id node);

public:
  static Graph<Type> kruskal(Graph<Type> & graph);

  static Graph<Type> prim(Graph<Type> & graph);
};

#include "Acm.cpp"

#endif
