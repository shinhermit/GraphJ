#ifndef WEIGHTEDEDGE
#define WEIGHTEDEDGE

#include "Edge.hpp"
#include "GraphTypes.hpp"

class WeightedEdge : public Edge{
protected:
  GraphTypes::Cost _cost;

public:
  WeightedEdge(Node::node_id node1, Node::node_id node2, GraphTypes::Cost cost);
  WeightedEdge(const Edge & source);

  bool operator==(const Edge & ref)const;
  bool operator<(const Edge & ref)const;
  bool operator<=(const Edge & ref)const;
  bool operator>(const Edge & ref)const;
  bool operator>=(const Edge & ref)const;
  bool operator!=(const Edge & ref)const;

  GraphTypes::Cost cost()const;
};

#endif
