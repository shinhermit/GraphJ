#ifndef WEIGHTEDNODE
#define WEIGHTEDNODE

#include "Node.hpp"
#include "GraphTypes.hpp"

class WeightedNode : public Node{
protected:
  GraphTypes::Cost _cost;

public:
  WeightedNode(GraphTypes::node_id id, GraphTypes::Cost cost);
  WeightedNode(const WeightedNode & source);

  bool operator==(const WeightedNode & ref)const;
  bool operator<(const WeightedNode & ref)const;
  bool operator<=(const WeightedNode & ref)const;
  bool operator>(const WeightedNode & ref)const;
  bool operator>=(const WeightedNode & ref)const;
  bool operator!=(const WeightedNode & ref)const;

  GraphTypes::Cost cost()const;
};

#endif
