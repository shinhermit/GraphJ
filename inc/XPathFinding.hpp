#ifndef _XPathFinding
#define _XPathFinding

#include <list>
#include <deque>
#include "Graph.hpp"
#include "PathBuilderVisitor.hpp"
#include "Traverse.hpp"

template <typename Type=GraphTypes::Default>
class XPathFinding
{
private:
  //Xdijkstra
  void _init(Graph<Type> & graph, Graph<> & paths, GraphTypes::node_id sourceNode, std::list<GraphTypes::node_id> & candidates, std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source, std::map<GraphTypes::node_id, std::list<GraphTypes::node_id> > & best_predecessors);

  std::list<GraphTypes::node_id> _minimals(std::list<GraphTypes::node_id> & candidates, std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source);

  void _add_edges(Graph<Type> & graph, Graph<> & paths, std::map<GraphTypes::node_id, std::list<GraphTypes::node_id> > & best_predecessors, std::list<GraphTypes::node_id> allClosest);

  void _remove_nodes(std::list<GraphTypes::node_id> & candidates, std::list<GraphTypes::node_id> allClosest);

  void _update_tables(Graph<Type> & graph, Graph<> & paths, std::list<GraphTypes::node_id> allClosest, std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source, std::map<GraphTypes::node_id, std::list<GraphTypes::node_id> > & best_predecessors);

  //Xbellman
  std::deque<GraphTypes::node_id> _relaxation(Graph<Type> & graph, Graph<> & paths, std::list<GraphTypes::node_id> & candidates);

  void _update_tables(Graph<Type> & graph, Graph<> & paths, std::deque<GraphTypes::node_id> & waiting_for_insertion, std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source, std::map<GraphTypes::node_id, std::list<GraphTypes::node_id> > & best_predecessors);

  void _insert_waiting_nodes(Graph<Type> & graph, Graph<> & paths, std::deque<GraphTypes::node_id> & waiting_for_insertion, std::map<GraphTypes::node_id, std::list<GraphTypes::node_id> > & best_predecessors);

  void _remove_nodes(std::list<GraphTypes::node_id> & candidates, std::deque<GraphTypes::node_id> & waiting_for_insertion);

public:
  Graph<> Xdijkstra(Graph<Type> & graph, GraphTypes::node_id sourceNode);

  Graph<> Xbellman(Graph<Type> & graph, GraphTypes::node_id sourceNode);

  //Attention: Ne surtout pas utiliser avec des graphes non orientés
  //(Pour cela, il faudrait rajouter un marquage)
  std::list<GraphTypes::Path> paths_to(Graph<> & allPaths, GraphTypes::node_id target);

  std::list<GraphTypes::Path> Xbetween(Graph<Type> & graph, GraphTypes::node_id source, GraphTypes::node_id target, GraphTypes::SearchAlgorithm algo=GraphTypes::DIJKSTRA);
};

#include "XPathFinding.cpp"

#endif
