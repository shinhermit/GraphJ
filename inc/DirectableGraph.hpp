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
  bool has_edge(GraphTypes::node_id id1, GraphTypes::node_id id2);
  bool is_directed();

  // Adaptation des constructeurs
  void add_edge(GraphTypes::node_id id1, GraphTypes::node_id id2);

  // Adaptation des observateurs
  GraphTypes::EdgeType edgeType()const;
  unsigned long edges_size()const;

  std::set<GraphTypes::node_id> predecessors(GraphTypes::node_id node) throw(std::invalid_argument);
  std::set<GraphTypes::node_id> adjacents(GraphTypes::node_id node) throw(std::invalid_argument);
  unsigned long in_degree(GraphTypes::node_id node) throw(std::invalid_argument);
  unsigned long degree(GraphTypes::node_id node) throw(std::invalid_argument);
};

#endif
