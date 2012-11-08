#ifndef WEIGHTEDNEIGHBOUR
#define WEIGHTEDNEIGHBOUR

#include "Node.hpp"
#include "GraphTypes.hpp"

class WeightedNeighbour : public Node{
protected:
  GraphTypes::Cost _cost;

public:
  WeightedNeighbour(node_id id, GraphTypes::Cost cost);
  WeightedNeighbour(const WeightedNeighbour & source);

  bool operator==(const WeightedNeighbour & ref)const;
  bool operator<(const WeightedNeighbour & ref)const;
  bool operator<=(const WeightedNeighbour & ref)const;
  bool operator>(const WeightedNeighbour & ref)const;
  bool operator>=(const WeightedNeighbour & ref)const;
  bool operator!=(const WeightedNeighbour & ref)const;

  GraphTypes::Cost cost()const;
};

#endif
