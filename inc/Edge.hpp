#ifndef EDGE
#define EDGE

#include "Node.hpp"

class Edge{
private:
  Node::node_id _source;
  Node::node_id _target;

public:
  Edge(Node::node_id node1, Node::node_id node2);
  Edge(const Edge & source);

  Node::node_id source()const;
  Node::node_id target()const;
};

#endif
