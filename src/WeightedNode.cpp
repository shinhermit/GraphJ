#include "WeightedNode.hpp"

WeightedNode::WeightedNode(const GraphTypes::node_id & id, const GraphTypes::Cost & cost):Node(id), _cost(cost){}

WeightedNode::WeightedNode(const WeightedNode & source):Node(source), _cost(source._cost){}

bool WeightedNode::operator==(const WeightedNode & ref)const{
  return _cost == ref._cost && Node::operator==(ref);
}

bool WeightedNode::operator<(const WeightedNode & ref)const{
  return (_cost < ref._cost) || (_cost == ref._cost && Node::operator<(ref));
}

bool WeightedNode::operator<=(const WeightedNode & ref)const{
  return operator<(ref) || operator==(ref);
}

bool WeightedNode::operator>(const WeightedNode & ref)const{
  return !operator<=(ref);
}

bool WeightedNode::operator>=(const WeightedNode & ref)const{
  return !operator<(ref);
}

bool WeightedNode::operator!=(const WeightedNode & ref)const{
  return !operator==(ref);
}

const GraphTypes::Cost & WeightedNode::cost()const{
  return _cost;
}
