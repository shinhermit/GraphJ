#ifndef _Exporter
#define _Exporter

#include <iostream>
#include <string>
#include <sstream>
#include "Traverse.hpp"
#include "DefaultVisitor.hpp"
#include "GraphvizVisitor.hpp"
#include "MathVisitor.hpp"
#include "NamedColor.hpp"

template<typename Type=GraphTypes::Default>
class Exporter{
private:
  std::string _graphviz_headers(Graph<Type> & graph);
  std::string _graphviz_relations(Graph<Type> & graph);
  std::string _graphviz_label_mapping(std::map<GraphTypes::node_id, std::string> & label_mapper);
  std::string _graphviz_color_mapping(std::map<GraphTypes::node_id, NamedColor::ColorName> & color_mapper);
  std::string _graphviz_paths_highlighting(std::list<GraphTypes::Path> & paths_highlight);
  std::string _graphviz_meta_mapping(Graph<Type> & graph, std::map<GraphTypes::node_id, std::string> & label_mapper, std::map<GraphTypes::node_id, NamedColor::ColorName> & color_mapper);
  std::string _graphviz_footers();

public:
  std::string toString(Graph<Type> & graph);

  std::string toMathString(Graph<Type> & graph, std::map<GraphTypes::node_id, std::string> & label_mapper);

  std::string toMathString(Graph<Type> & graph);

  void toStream(Graph<Type> & graph, std::ostream & out);

  std::string toGraphviz(Graph<Type> & graph);

  std::string toGraphviz(Graph<Type> & graph, std::map<GraphTypes::node_id, std::string> & label_mapper);

  std::string toGraphviz(Graph<Type> & graph, std::map<GraphTypes::node_id, NamedColor::ColorName> & color_mapper);

  std::string toGraphviz(Graph<Type> & graph, std::list<GraphTypes::Path> & paths_highlight);

  std::string toGraphviz(Graph<Type> & graph, std::map<GraphTypes::node_id, std::string> & label_mapper, std::map<GraphTypes::node_id, NamedColor::ColorName> & color_mapper);

  void toGraphviz(Graph<Type> & graph, std::string filename);

  void toGraphviz(Graph<Type> & graph, std::map<GraphTypes::node_id, std::string> & label_mapper, std::string filename);

  void toGraphviz(Graph<Type> & graph, std::map<GraphTypes::node_id, NamedColor::ColorName> & color_mapper, std::string filename);

  void toGraphviz(Graph<Type> & graph, std::list<GraphTypes::Path> & paths_highlight, std::string filename);

  void toGraphviz(Graph<Type> & graph, std::map<GraphTypes::node_id, std::string> & label_mapper, std::map<GraphTypes::node_id, NamedColor::ColorName> & color_mapper, std::string filename);
};

#include "Exporter.cpp"

#endif
