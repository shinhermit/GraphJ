#ifndef _Exporter
#define _Exporter

#include <iostream>
#include <string>
#include <sstream>
#include "Traverse.hpp"
#include "DefaultVisitor.hpp"
#include "GraphvizVisitor.hpp"
#include "NamedColor.hpp"

template<typename Type=GraphTypes::Default>
class Exporter{
private:
  GraphTypes::What _what;

public:
  Exporter(GraphTypes::What what=GraphTypes::NODES);
  void what(GraphTypes::What what);

  std::string toString(Graph<Type> & graph);

  void toStream(Graph<Type> & graph, std::ostream & out);

  std::string toGraphviz(Graph<Type> & graph);
  std::string toGraphviz(Graph<Type> & graph, std::map<Node::node_id, NamedColor::ColorName> color_mapper);
  void toGraphviz(Graph<Type> & graph, std::string filename);
  void toGraphviz(Graph<Type> & graph, std::map<Node::node_id, NamedColor::ColorName> color_mapper, std::string filename);
};

#include "Exporter.cpp"

#endif
