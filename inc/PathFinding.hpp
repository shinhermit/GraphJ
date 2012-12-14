#ifndef _PathFinding
#define _PathFinding

#include <list>
#include <deque>
#include "Graph.hpp"
#include "PathBuilderVisitor.hpp"
#include "Traverse.hpp"

template <typename Type=GraphTypes::Default>
class PathFinding
{
private:
  Node::node_id _closest(std::map<Node::node_id, GraphTypes::Cost> & distances);

  void _update_tables(Graph<Type> & graph, Graph<> & paths, Node::node_id closest, std::map<Node::node_id, GraphTypes::Cost> & distance_from_source, std::map<Node::node_id, Node::node_id> & best_predecessor);

  std::deque<Node::node_id> _relaxation(Graph<Type> & graph, Graph<> & paths, std::list<Node::node_id> & candidates);

  void _add_relaxed_nodes(Graph<Type> & graph, Graph<> & paths, std::deque<Node::node_id> & waiting_for_insertion, std::map<Node::node_id, Node::node_id> & best_predecessor);

  void _update_tables(Graph<Type> & graph, Graph<> & paths, std::deque<Node::node_id> & waiting_for_insertion, std::map<Node::node_id, GraphTypes::Cost> & distance_from_source, std::map<Node::node_id, Node::node_id> & best_predecessor);

public:
  Graph<> dijkstra(Graph<Type> & graph, Node::node_id sourceNode);

  Graph<> bellman(Graph<Type> & graph, Node::node_id sourceNode);

  Graph<> between(Graph<Type> & graph, Node::node_id source, Node::node_id target, GraphTypes::SearchAlgorithm algo=GraphTypes::DIJKSTRA);
};

#include "PathFinding.cpp"

#endif
