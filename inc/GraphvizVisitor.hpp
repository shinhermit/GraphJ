#ifndef GRAPHVIZVISITOR
#define GRAPHVIZVISITOR

#include "Visitor.hpp"
#include <fstream>
#include <sstream>
#include <string>

template<typename Type>
class GraphvizVisitor : public Visitor<Type>{
private:
  std::string _buffer;
  std::set<Node::node_id> _visited;

public:
  GraphvizVisitor();
  virtual ~GraphvizVisitor();

  virtual void treat(Graph<Type> & graph, Node::node_id node);

  std::string nodes_representation()const;

  void flush();
};

#include "GraphvizVisitor.cpp"

#endif
