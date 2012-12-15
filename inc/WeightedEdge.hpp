#ifndef WEIGHTEDEDGE
#define WEIGHTEDEDGE

#include "Edge.hpp"
#include "GraphTypes.hpp"

class WeightedEdge : public Edge{
protected:
  GraphTypes::Cost _cost;

public:
  WeightedEdge(GraphTypes::node_id node1, GraphTypes::node_id node2, GraphTypes::Cost cost);
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
