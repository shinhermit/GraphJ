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
  GraphTypes::ComputingValidity _validity;

  GraphTypes::ComputingValidity _check_computing_validity(Graph<Type> & graph, std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source);

  //DIJKSTRA
  void _init(Graph<Type> & graph, Graph<> & paths, GraphTypes::node_id sourceNode, std::list<GraphTypes::node_id> & candidates, std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source, std::map<GraphTypes::node_id, GraphTypes::node_id> & best_predecessor);

  GraphTypes::node_id _closest(std::list<GraphTypes::node_id> & candidates, std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source);

  void _update_tables(Graph<Type> & graph, Graph<> & paths, GraphTypes::node_id closest, std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source, std::map<GraphTypes::node_id, GraphTypes::node_id> & best_predecessor);

  //BELLMAN GREEDY
  void _init(Graph<Type> & graph, Graph<> & paths, GraphTypes::node_id sourceNode, std::list<GraphTypes::node_id> & candidates, std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source, GraphTypes::OptimizationType optimizationType=GraphTypes::MINIMIZE);

  std::deque<GraphTypes::node_id> _relaxation(Graph<Type> & graph, Graph<> & paths, std::list<GraphTypes::node_id> & candidates);

  void _update_tables(Graph<Type> & graph, Graph<> & paths, std::deque<GraphTypes::node_id> & waiting_for_insertion, std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source, std::map<GraphTypes::node_id, GraphTypes::node_id> & best_predecessor, GraphTypes::OptimizationType optimizationType=GraphTypes::MINIMIZE);

  void _insert_waiting_nodes(Graph<Type> & graph, Graph<> & paths, std::deque<GraphTypes::node_id> & waiting_for_insertion, std::map<GraphTypes::node_id, GraphTypes::node_id> & best_predecessor);

  void _remove_nodes(std::list<GraphTypes::node_id> & candidates, std::deque<GraphTypes::node_id> & waiting_for_insertion);

  Graph<> _greedy_bellman(Graph<Type> & graph, GraphTypes::node_id sourceNode, GraphTypes::OptimizationType optimizationType=GraphTypes::MINIMIZE);

  //BELLMAN DYNAMIC
  void _init(Graph<Type> & graph, Graph<> & paths, GraphTypes::node_id sourceNode, std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source, GraphTypes::OptimizationType optimizationType=GraphTypes::MINIMIZE);

  void _update_tables(Graph<Type> & graph, std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source, std::map<GraphTypes::node_id, GraphTypes::node_id> & best_predecessor, GraphTypes::OptimizationType optimizationType=GraphTypes::MINIMIZE);

  void _build_paths_graph(Graph<Type> & graph, Graph<> & paths, GraphTypes::node_id sourceNode, std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source, std::map<GraphTypes::node_id, GraphTypes::node_id> & best_predecessor);

  Graph<> _dynamic_bellman(Graph<Type> & graph, GraphTypes::node_id sourceNode, GraphTypes::OptimizationType optimizationType=GraphTypes::MINIMIZE);

public:
  PathFinding();

  Graph<> dijkstra(Graph<Type> & graph, GraphTypes::node_id sourceNode);

  Graph<> bellman(Graph<Type> & graph, GraphTypes::node_id sourceNode, GraphTypes::AlgorithmicClass algoClass=GraphTypes::DYNAMIC, GraphTypes::OptimizationType optimizationType=GraphTypes::MINIMIZE);

  std::list<GraphTypes::Path> paths_to(Graph<> & allPaths, GraphTypes::node_id target) throw(std::logic_error);

  std::list<GraphTypes::Path> between(Graph<Type> & graph, GraphTypes::node_id source, GraphTypes::node_id target, GraphTypes::SearchAlgorithm algo=GraphTypes::DIJKSTRA) throw(std::logic_error);

  GraphTypes::ComputingValidity validity()const;
};

#include "PathFinding.cpp"

#endif
