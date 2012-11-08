#ifndef NODE
#define NODE

#include <iostream>

class Node{
public:
  typedef unsigned long node_id;

protected:
  node_id _id;

public:
  Node(node_id id);
  Node(const Node & source);

  bool operator==(const Node & ref)const;
  bool operator<(const Node & ref)const;
  bool operator<=(const Node & ref)const;
  bool operator>(const Node & ref)const;
  bool operator>=(const Node & ref)const;
  bool operator!=(const Node & ref)const;

  node_id id()const;
};

#endif
