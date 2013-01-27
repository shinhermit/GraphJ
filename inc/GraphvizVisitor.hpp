#ifndef _GraphvizVisitor
#define _GraphvizVisitor

#include "Visitor.hpp"
#include <fstream>
#include <sstream>
#include <string>

namespace GraphFunctor
{

  template<typename Type>
  class GraphvizVisitor : public Visitor{
  private:
    const Graph<Type> & _graph;
    std::string & _buffer;
    std::set<GraphTypes::node_id> _visited;

  public:
    GraphvizVisitor(const Graph<Type> & graph, std::string & _buffer);

    ~GraphvizVisitor();

    void operator()(const GraphTypes::node_id & node);
  };

};

#include "GraphvizVisitor.cpp"

#endif
