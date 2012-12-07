#ifndef _PathBuilderVisitor
#define _PathBuilderVisitor

#include "Graph.hpp"
#include "Visitor.hpp"

template <typename Type=GraphTypes::Default>
class PathBuilderVisitor : public Visitor<Type>
{
private:
  Graph<> _path;

public:
  PathBuilderVisitor();
  virtual ~PathBuilderVisitor();

  virtual void treat(Graph<> & graph, Node::node_id node);

  Graph<> path()const;
};

#include "PathBuilderVisitor.cpp"

#endif
