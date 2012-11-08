#ifndef PONDERABLEGRAPH
#define PONDERABLEGRAPH

#include "DirectableGraph.hpp"

class PonderableGraph : public DirectableGraph{
protected:
  GraphTypes::EdgeState _edgeState;

  std::map<Edge,GraphTypes::Cost> _weights;

public:
  PonderableGraph(GraphTypes::EdgeType edgeType=GraphTypes::UNDIRECTED, GraphTypes::EdgeState state=GraphTypes::WEIGHTED);
  PonderableGraph(const PonderableGraph & source);

  PonderableGraph & operator=(const PonderableGraph & source);

  // Adaptation des prédicats
  bool is_weighted();

  // Adaptation des constructeurs
  void remove_node(Node::node_id id);
  void add_edge(Node::node_id id1, Node::node_id id2, GraphTypes::Cost cost=1.F);
  void remove_edge(Node::node_id id1, Node::node_id id2);

  // Nouvelles opérations
  void setCost(Node::node_id node1, Node::node_id node2, GraphTypes::Cost cost) throw(std::invalid_argument, std::logic_error);
  GraphTypes::Cost getCost(Node::node_id node1, Node::node_id node2) throw(std::invalid_argument, std::logic_error);

};

#endif
