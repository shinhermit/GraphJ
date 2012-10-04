#ifndef NODE
#define NODE

#include <iostream>

class Node{
public:
  typedef unsigned long node_id;

private:
  node_id _id;

public:
  Node(node_id id);
  Node(const Node & source);
  ~Node();
  Node & operator=(const Node & source);

  node_id id()const;
};

#endif
