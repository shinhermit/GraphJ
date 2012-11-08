#include "WeightedEdge.hpp"

WeightedEdge::WeightedEdge(Node::node_id node1, Node::node_id node2, GraphTypes::Cost cost):Edge(node1, node2), _cost(cost){}

WeightedEdge::WeightedEdge(const WeightedEdge & source):Edge(source), _cost(source._cost){}

bool WeightedEdge::operator==(const WeightedEdge & ref)const{
  return Edge::operator==(ref) && _cost == ref._cost;
}

bool WeightedEdge::operator<(const WeightedEdge & ref)const{
  return _cost < ref._cost;
}

bool WeightedEdge::operator<=(const WeightedEdge & ref)const{
  return _cost <= ref._cost;
}

bool WeightedEdge::operator>(const WeightedEdge & ref)const{
  return _cost > ref._cost;
}

bool WeightedEdge::operator>=(const WeightedEdge & ref)const{
  return _cost >= ref._cost;
}

bool WeightedEdge::operator!=(const WeightedEdge & ref)const{
  return !operator==(ref);
}

GraphTypes::Cost WeightedEdge::cost()const{
  return _cost;
}
