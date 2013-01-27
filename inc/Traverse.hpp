#ifndef _Traverse
#define _Traverse

#include <deque>
#include "Graph.hpp"
#include "Visitor.hpp"

template<typename Type=GraphTypes::Default>
class Traverse{
private:
  static void _Breadth_once(Graph<Type> & graph, const GraphTypes::node_id & node, GraphFunctor::Visitor & visit, std::set<GraphTypes::node_id> & marker);

  static void _Depth_once(Graph<Type> & graph, const GraphTypes::node_id & node, GraphFunctor::Visitor & visit, std::set<GraphTypes::node_id> & marker);

public:
  static void Nodes(Graph<Type> & graph, GraphFunctor::Visitor & visit);

  static void Breadth_once(Graph<Type> & graph, const GraphTypes::node_id & node, GraphFunctor::Visitor & visit);

  static void Breadth(Graph<Type> & graph, GraphFunctor::Visitor & visit);

  static void Depth_once(Graph<Type> & graph, const GraphTypes::node_id & node, GraphFunctor::Visitor & visit);

  static void Depth(Graph<Type> & graph, GraphFunctor::Visitor & visit);

};

#include "Traverse.cpp"

#endif
