#ifndef DIRECTABLEGRAPH
#define DIRECTABLEGRAPH

#include "DiGraph.hpp"

class DirectableGraph : public DiGraph{
public:
  enum EdgeType{DIRECTED, UNDIRECTED};

protected:
  EdgeType _edgeType;

public:
  DirectableGraph(EdgeType edgeType=UNDIRECTED);
  DirectableGraph(const DirectableGraph & source);

  // Adaptation des prédicats
  bool has_edge(Node::node_id id1, Node::node_id id2);

  // Adaptation des constructeurs
  void add_edge(Node::node_id id1, Node::node_id id2);

  // Adaptation des observateurs
  std::set<Node::node_id> predecessors(Node::node_id node) throw(std::invalid_argument);
  std::set<Node::node_id> adjacents(Node::node_id node) throw(std::invalid_argument);
  unsigned long internally(Node::node_id node) throw(std::invalid_argument);
  unsigned long degree(Node::node_id node) throw(std::invalid_argument);
};

#endif
