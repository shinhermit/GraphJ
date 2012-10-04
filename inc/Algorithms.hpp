#ifndef ALGORITHMS
#define ALGORITHMS

#include <deque>
#include "Graph.hpp"
#include "Visitor.hpp"

namespace Algorithms{
  template<typename Type>
  void breadth_visit(Graph<Type> & graph, Node::node_id node, Visitor<Type> & visitor, std::set<Node::node_id> & marker);

  template<typename Type>
  void breadth_first_search(Graph<Type> & graph, Visitor<Type> & visitor);

  template<typename Type>
  void depth_visit(Graph<Type> & graph, Node::node_id node, Visitor<Type> & visitor, std::set<Node::node_id> & marker);

  template<typename Type>
  void depth_first_search(Graph<Type> & graph, Visitor<Type> & visitor);
};

#include "Algorithms.cpp"

#endif
