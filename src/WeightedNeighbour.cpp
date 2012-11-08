#include "WeightedNeighbour.hpp"

WeightedNeighbour::WeightedNeighbour(Node::node_id id, GraphTypes::Cost cost):Node(id), _cost(cost){}

WeightedNeighbour::WeightedNeighbour(const WeightedNeighbour & source):Node(source), _cost(source._cost){}

bool WeightedNeighbour::operator==(const WeightedNeighbour & ref)const{
  return _cost == ref._cost && Node::operator==(ref);
}

bool WeightedNeighbour::operator<(const WeightedNeighbour & ref)const{
  return (_cost < ref._cost) || (_cost == ref._cost && Node::operator<(ref));
}

bool WeightedNeighbour::operator<=(const WeightedNeighbour & ref)const{
  return operator<(ref) || operator==(ref);
}

bool WeightedNeighbour::operator>(const WeightedNeighbour & ref)const{
  return !operator<=(ref);
}

bool WeightedNeighbour::operator>=(const WeightedNeighbour & ref)const{
  return !operator<(ref);
}

bool WeightedNeighbour::operator!=(const WeightedNeighbour & ref)const{
  return !operator==(ref);
}

GraphTypes::Cost WeightedNeighbour::cost()const{
  return _cost;
}
