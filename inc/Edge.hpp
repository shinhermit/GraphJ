#ifndef EDGE
#define EDGE

#include "Node.hpp"

class Edge{
protected:
  Node::node_id _source;
  Node::node_id _target;

public:
  Edge();
  Edge(Node::node_id node1, Node::node_id node2);
  Edge(const Edge & source);

  bool operator==(const Edge & ref)const;
  bool operator<(const Edge & ref)const;
  bool operator<=(const Edge & ref)const;
  bool operator>(const Edge & ref)const;
  bool operator>=(const Edge & ref)const;
  bool operator!=(const Edge & ref)const;

  Node::node_id source()const;
  Node::node_id target()const;
};

#endif
