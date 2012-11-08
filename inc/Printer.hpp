#ifndef PRINTER
#define PRINTER

#include "Visitor.hpp"

template<typename Type>
class Printer : public Visitor<Type>{
public:
  enum{NODES, CONTENTS} What;

private:
  What _what;

public:
  Printer(What what_to_print=NODES);
  virtual ~Printer();

  virtual void treat(Graph<Type> graph, Node::node_id node);

  void print_what(What what);
};

#include "Printer.cpp"

#endif
