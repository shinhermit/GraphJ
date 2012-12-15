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
  GraphTypes::node_id _closest(std::map<GraphTypes::node_id, GraphTypes::Cost> & distances);

  void _update_tables(Graph<Type> & graph, Graph<> & paths, GraphTypes::node_id closest, std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source, std::map<GraphTypes::node_id, GraphTypes::node_id> & best_predecessor);

  std::deque<GraphTypes::node_id> _relaxation(Graph<Type> & graph, Graph<> & paths, std::list<GraphTypes::node_id> & candidates);

  void _add_relaxed_nodes(Graph<Type> & graph, Graph<> & paths, std::deque<GraphTypes::node_id> & waiting_for_insertion, std::map<GraphTypes::node_id, GraphTypes::node_id> & best_predecessor);

  void _update_tables(Graph<Type> & graph, Graph<> & paths, std::deque<GraphTypes::node_id> & waiting_for_insertion, std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source, std::map<GraphTypes::node_id, GraphTypes::node_id> & best_predecessor);

public:
  Graph<> dijkstra(Graph<Type> & graph, GraphTypes::node_id sourceNode);

  Graph<> bellman(Graph<Type> & graph, GraphTypes::node_id sourceNode);

  Graph<> between(Graph<Type> & graph, GraphTypes::node_id source, GraphTypes::node_id target, GraphTypes::SearchAlgorithm algo=GraphTypes::DIJKSTRA);
};

#include "PathFinding.cpp"

#endif
