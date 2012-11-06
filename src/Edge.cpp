#include "Edge.hpp"

Edge::Edge(Node::node_id node1, Node::node_id node2):_source(node1), _target(node2){}

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

Node::node_id Edge::source()const{
  return _source;
}

Node::node_id Edge::target()const{
  return _target;
}
