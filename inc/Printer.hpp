#ifndef PRINTER
#define PRINTER

#include "Visitor.hpp"
#include "GraphTypes.hpp"

template<typename Type>
class Printer : public Visitor<Type>{
private:
  GraphTypes::What _what;

public:
  Printer(GraphTypes::What what_to_print=GraphTypes::NODES);
  virtual ~Printer();

  virtual void treat(Graph<Type> graph, Node::node_id node);

  void print_what(GraphTypes::What what);
};

#include "Printer.cpp"

#endif
