#ifndef VISITOR
#define VISITOR

#include "Graph.hpp"

template<typename Type>
class Visitor{

public:

  Visitor();
  virtual ~Visitor();

  virtual void treat(Graph<Type> & graph, Node::node_id node)=0;
};

#include "Visitor.cpp"

#endif
