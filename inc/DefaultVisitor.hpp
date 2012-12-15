#ifndef DEFAULTVISITOR
#define DEFAULTVISITOR

#include <string>
#include <sstream>
#include "Visitor.hpp"
#include "GraphTypes.hpp"

template<typename Type>
class DefaultVisitor : public Visitor<Type>{
private:
  std::string _buffer;
  std::set<GraphTypes::node_id> _visited;

public:
  DefaultVisitor();
  virtual ~DefaultVisitor();

  //Attention: cette méthode a été spécialisée pour les std::string
  virtual void treat(Graph<Type> & graph, GraphTypes::node_id node);

  std::string nodes_representation()const;

  void flush();
};

#include "DefaultVisitor.cpp"

#endif
