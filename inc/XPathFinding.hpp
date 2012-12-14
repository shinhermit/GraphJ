#ifndef _XPathFinding
#define _XPathFinding

#include <list>
#include <deque>
#include "Graph.hpp"
#include "PathBuilderVisitor.hpp"
#include "Traverse.hpp"

typedef std::list<Node::node_id> Path;

template <typename Type=GraphTypes::Default>
class XPathFinding
{
private:
  //Xdijkstra
  std::list<Node::node_id> _minimals(std::map<Node::node_id, GraphTypes::Cost> & distances);

  void _add_edges(Graph<Type> & graph, Graph<> & paths, std::map<Node::node_id, std::list<Node::node_id> > & best_predecessors, std::list<Node::node_id> allClosest);

  void _remove_nodes(std::map<Node::node_id, GraphTypes::Cost> & distances, std::list<Node::node_id> allClosest);

  void _update_tables(Graph<Type> & graph, Graph<> & paths, std::list<Node::node_id> allClosest, std::map<Node::node_id, GraphTypes::Cost> & distance_from_source, std::map<Node::node_id, std::list<Node::node_id> > & best_predecessors);

  //Xbellman
  std::deque<Node::node_id> _relaxation(Graph<Type> & graph, Graph<> & paths, std::list<Node::node_id> & candidates);

  void _update_tables(Graph<Type> & graph, Graph<> & paths, std::deque<Node::node_id> & waiting_for_insertion, std::map<Node::node_id, GraphTypes::Cost> & distance_from_source, std::map<Node::node_id, std::list<Node::node_id> > & best_predecessors);

  void _add_relaxed_nodes(Graph<Type> & graph, Graph<> & paths, std::deque<Node::node_id> & waiting_for_insertion, std::map<Node::node_id, std::list<Node::node_id> > & best_predecessors);

public:
  Graph<> Xdijkstra(Graph<Type> & graph, Node::node_id sourceNode);

  Graph<> Xbellman(Graph<Type> & graph, Node::node_id sourceNode);

  std::list<Path> paths_to(Graph<Type> & graph, Graph<> & allPaths, Node::node_id target);

  std::list<Path> Xbetween(Graph<Type> & graph, Node::node_id source, Node::node_id target, GraphTypes::SearchAlgorithm algo=GraphTypes::DIJKSTRA);
};

#include "XPathFinding.cpp"

#endif
