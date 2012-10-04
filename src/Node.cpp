#include "Node.hpp"

Node::Node(Node::node_id id):_id(id){}

Node::Node(const Node & source):_id(source._id){}

Node::~Node(){}

Node & Node::operator=(const Node & source){
  _id = source._id;
  return *this;
}

Node::node_id Node::id()const{
  return _id;
}
