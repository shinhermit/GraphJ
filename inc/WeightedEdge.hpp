#ifndef _WeightedEdge
#define _WeightedEdge

#include "Edge.hpp"
#include "GraphTypes.hpp"

class WeightedEdge : public Edge
{
protected:
  GraphTypes::Cost _cost;

public:
  WeightedEdge(const GraphTypes::node_id & node1, const GraphTypes::node_id & node2, const GraphTypes::Cost & cost);
  WeightedEdge(const WeightedEdge & source);

  bool operator==(const WeightedEdge & ref)const;
  bool operator<(const WeightedEdge & ref)const;
  bool operator<=(const WeightedEdge & ref)const;
  bool operator>(const WeightedEdge & ref)const;
  bool operator>=(const WeightedEdge & ref)const;
  bool operator!=(const WeightedEdge & ref)const;

  const GraphTypes::Cost & cost()const;
};

#endif
