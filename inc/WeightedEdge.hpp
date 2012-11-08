#ifndef WEIGHTEDEDGE
#define WEIGHTEDEDGE

#include "Edge.hpp"
#include "GraphTypes.hpp"

class WeightedEdge : public Edge{
protected:
  GraphTypes::Cost _cost;

public:
  WeightedEdge(Node::node_id node1, Node::node_id node2, GraphTypes::Cost cost);
  WeightedEdge(const WeightedEdge & source);

  bool operator==(const WeightedEdge & ref)const;
  bool operator<(const WeightedEdge & ref)const;
  bool operator<=(const WeightedEdge & ref)const;
  bool operator>(const WeightedEdge & ref)const;
  bool operator>=(const WeightedEdge & ref)const;
  bool operator!=(const WeightedEdge & ref)const;

  GraphTypes::Cost cost()const;
};

#endif
