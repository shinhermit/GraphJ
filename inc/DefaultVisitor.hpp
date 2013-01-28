#ifndef _DefaultVisitor
#define _DefaultVisitor

#include <string>
#include <sstream>
#include "Visitor.hpp"
#include "GraphTypes.hpp"

namespace GraphFunctor
{

  template<typename Type>
  class DefaultVisitor : public Visitor{
  private:
    const Graph<Type> & _graph;
    std::string & _buffer;
    std::set<GraphTypes::node_id> _visited;

  public:
    DefaultVisitor(const Graph<Type> & graph,
		   std::string & buffer);

    ~DefaultVisitor();

    void operator()(const GraphTypes::node_id & node);
  };

};

#include "DefaultVisitor.cpp"

#endif
