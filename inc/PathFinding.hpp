#ifndef _PathFinding
#define _PathFinding

#include "Graph.hpp"

template <typename Type>
class PathFinding
{
public:
  Graph<> dijkstra(Graph<Type> & graph, Node::node_id sourceNode);

  Graph<> bellman(Graph<Type> & graph, Node::node_id sourceNode);

  Graph<> bellman_dual(Graph<Type> & graph, Node::node_id targetNode);

};

#include "PathFinding.cpp"

#endif
