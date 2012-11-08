#include "Node.hpp"

Node::Node(Node::node_id id):_id(id){}

Node::Node(const Node & source):_id(source._id){}

bool Edge::operator==(const Edge & ref)const{
  return _id == ref._id;
}

bool Edge::operator<(const Edge & ref)const{
  return _id < ref._id;
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
  return !operator==(ref);
}

Node::node_id Node::id()const{
  return _id;
}
