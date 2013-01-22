#ifndef NODE
#define NODE

#include <iostream>
#include "GraphTypes.hpp"

class Node{
protected:
  GraphTypes::node_id _id;

public:
  Node(const GraphTypes::node_id & id);
  Node(const Node & source);

  bool operator==(const Node & ref)const;
  bool operator<(const Node & ref)const;
  bool operator<=(const Node & ref)const;
  bool operator>(const Node & ref)const;
  bool operator>=(const Node & ref)const;
  bool operator!=(const Node & ref)const;

  GraphTypes::node_id id()const;
};

#endif
