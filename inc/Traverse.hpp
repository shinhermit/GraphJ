#ifndef _Traverse
#define _Traverse

#include <deque>
#include "Graph.hpp"
#include "Visitor.hpp"

template<typename Type>
class Traverse{
public:
  static void nodes(Graph<Type> & graph, Visitor<Type> & visitor);

  static void breadth_once(Graph<Type> & graph, Node::node_id node, Visitor<Type> & visitor, std::set<Node::node_id> & marker);

  static void breadth(Graph<Type> & graph, Visitor<Type> & visitor);

  static void depth_once(Graph<Type> & graph, Node::node_id node, Visitor<Type> & visitor, std::set<Node::node_id> & marker);

  static void depth(Graph<Type> & graph, Visitor<Type> & visitor);
};

#include "Traverse.cpp"

#endif
