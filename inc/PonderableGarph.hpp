#ifndef PONDERABLEGRAPH
#define PONDERABLEGRAPH

#include "DirectableGraph.hpp"

class PonderableGraph : public DirectableGraph{
public:
  enum EdgeState{WEIGHTED, UNWEIGHTED};
  typedef float Cost;

protected:
  EdgeState _edgeState;

  std::map<Edge, Cost> _weights;

public:
  PonderableGraph(EdgeType edgeType=UNDIRECTED, EdgeState state=WEIGHTED);
  PonderableGraph(const PonderableGraph & source);

  PonderableGraph & operator=(const PonderableGraph & source);

  // Adaptation des constructeurs
  void remove_node(Node::node_id id);
  void add_edge(Node::node_id id1, Node::node_id id2, Cost cost=1.F);
  void remove_edge(Node::node_id id1, Node::node_id id2);

  // Nouvelles opérations
  void setCost(Node::node_id node1, Node::node_id node2, Cost cost) throw(std::invalid_argument, std::logic_error);
  Cost getCost(Node::node_id node1, Node::node_id node2)const throw(std::invalid_argument, std::logic_error);

};

#endif
