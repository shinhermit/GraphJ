#ifndef _WeightedNode
#define _WeightedNode

#include "Node.hpp"
#include "GraphTypes.hpp"

class WeightedNode : public Node
{
protected:
  GraphTypes::Cost _cost;

public:
  WeightedNode(const GraphTypes::node_id & id, const GraphTypes::Cost & cost);
  WeightedNode(const WeightedNode & source);

  bool operator==(const WeightedNode & ref)const;
  bool operator<(const WeightedNode & ref)const;
  bool operator<=(const WeightedNode & ref)const;
  bool operator>(const WeightedNode & ref)const;
  bool operator>=(const WeightedNode & ref)const;
  bool operator!=(const WeightedNode & ref)const;

  const GraphTypes::Cost & cost()const;
};

#endif
