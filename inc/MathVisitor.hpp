#ifndef _MathVisitor
#define _MathVisitor

#include "Visitor.hpp"
#include <fstream>
#include <sstream>
#include <string>

namespace GraphFunctor
{

  template<typename Type>
  class MathVisitor : public Visitor
  {
  private:
    const Graph<Type> & _graph;
    std::string & _S_buffer; //vertices
    std::string & _A_buffer; //edges
    std::string & _C_buffer; //weights

    std::set<GraphTypes::node_id> _visited;

  public:
    MathVisitor(const Graph<Type> & graph, std::string & S_buffer, std::string & A_buffer, std::string & C_buffer);

    ~MathVisitor();

    void operator()(const GraphTypes::node_id & node);
  };

};

#include "MathVisitor.cpp"

#endif
