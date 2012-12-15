#ifndef EDGE
#define EDGE

#include "Node.hpp"

class Edge{
protected:
  GraphTypes::node_id _source;
  GraphTypes::node_id _target;

public:
  Edge();
  Edge(GraphTypes::node_id node1, GraphTypes::node_id node2);
  Edge(const Edge & source);

  bool operator==(const Edge & ref)const;
  bool operator<(const Edge & ref)const;
  bool operator<=(const Edge & ref)const;
  bool operator>(const Edge & ref)const;
  bool operator>=(const Edge & ref)const;
  bool operator!=(const Edge & ref)const;

  GraphTypes::node_id source()const;
  GraphTypes::node_id target()const;
};

#endif
