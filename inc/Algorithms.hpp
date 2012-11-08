#ifndef ALGORITHMS
#define ALGORITHMS

#include <deque>
#include "Graph.hpp"
#include "Visitor.hpp"
#include "WeightedEdge.hpp"
#include "WeightedEdgeSorter.hpp"

namespace Algorithms{
  template<typename Type>
  void breadth_visit(Graph<Type> & graph, Node::node_id node, Visitor<Type> & visitor, std::set<Node::node_id> & marker);

  template<typename Type>
  void breadth_first_search(Graph<Type> & graph, Visitor<Type> & visitor);

  template<typename Type>
  void depth_visit(Graph<Type> & graph, Node::node_id node, Visitor<Type> & visitor, std::set<Node::node_id> & marker);

  template<typename Type>
  void depth_first_search(Graph<Type> & graph, Visitor<Type> & visitor);

  template<typename Type>
  std::map<Node::node_id, int> color_each_node(Graph<Type> & graph);

  template<typename Type>
  Graph<Type> acm_kruskal(Graph<Type> & graph);

  template<typename Type>
  Graph<Type> acm_prim(Graph<Type> & graph);
};

#include "Algorithms.cpp"

#endif
