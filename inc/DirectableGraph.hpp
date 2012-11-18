#ifndef DIRECTABLEGRAPH
#define DIRECTABLEGRAPH

#include "DiGraph.hpp"
#include "GraphTypes.hpp"

class DirectableGraph : public DiGraph{
protected:
  GraphTypes::EdgeType _edgeType;

public:
  DirectableGraph(GraphTypes::EdgeType edgeType=GraphTypes::UNDIRECTED);
  DirectableGraph(const DirectableGraph & source);

  // Adaptation des prédicats
  bool has_edge(Node::node_id id1, Node::node_id id2);
  bool is_directed();
  bool is_weighted();

  // Adaptation des constructeurs
  void add_edge(Node::node_id id1, Node::node_id id2);

  // Adaptation des observateurs
  std::set<Node::node_id> predecessors(Node::node_id node) throw(std::invalid_argument);
  std::set<Node::node_id> adjacents(Node::node_id node) throw(std::invalid_argument);
  unsigned long in_degree(Node::node_id node) throw(std::invalid_argument);
  unsigned long degree(Node::node_id node) throw(std::invalid_argument);
};

#endif
