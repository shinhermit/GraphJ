#ifndef MATHVISITOR
#define MATHVISITOR

#include "Visitor.hpp"
#include <fstream>
#include <sstream>
#include <string>

template<typename Type>
class MathVisitor : public Visitor<Type>{
private:
  std::string _S_buffer; //vertices
  std::string _A_buffer; //edges
  std::string _C_buffer; //weights

  std::set<Node::node_id> _visited;

public:
  MathVisitor();
  virtual ~MathVisitor();

  virtual void treat(Graph<Type> & graph, Node::node_id node);

  std::string math_representation()const;

  void flush();
};

#include "MathVisitor.cpp"

#endif
