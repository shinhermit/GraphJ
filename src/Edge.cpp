#include "Edge.hpp"

Edge::Edge(GraphTypes::node_id node1, GraphTypes::node_id node2):_source(node1), _target(node2){}

Edge::Edge(const Edge & source):_source(source._source), _target(source._target){
}

bool Edge::operator==(const Edge & ref)const{
  return _source == ref._source && _target == ref._target;
}

bool Edge::operator<(const Edge & ref)const{
  return (_source < ref._source) || (_source == ref._source && _target < ref._target);
}

bool Edge::operator<=(const Edge & ref)const{
  return operator<(ref) || operator==(ref);
}

bool Edge::operator>(const Edge & ref)const{
  return !operator<=(ref);
}

bool Edge::operator>=(const Edge & ref)const{
  return !operator<(ref);  
}

bool Edge::operator!=(const Edge & ref)const{
  return _source != ref._source || _target != ref._target;
}

GraphTypes::node_id Edge::source()const{
  return _source;
}

GraphTypes::node_id Edge::target()const{
  return _target;
}
