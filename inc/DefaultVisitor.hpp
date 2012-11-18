#ifndef DEFAULTVISITOR
#define DEFAULTVISITOR

#include <string>
#include <sstream>
#include "Visitor.hpp"
#include "GraphTypes.hpp"

template<typename Type>
class DefaultVisitor : public Visitor<Type>{
private:
  GraphTypes::What _what;
  std::string _buffer;

public:
  DefaultVisitor(GraphTypes::What what_to_print=GraphTypes::NODES);
  virtual ~DefaultVisitor();

  virtual void treat(Graph<Type> graph, Node::node_id node);

  void print_what(GraphTypes::What what);

  std::string nodes_representation()const;

  void flush();
};

#include "DefaultVisitor.cpp"

#endif
