#ifndef _Exporter
#define _Exporter

#include <iostream>
#include <string>
#include <sstream>
#include "Traverse.hpp"
#include "GraphFunctor.hpp"
#include "NamedColor.hpp"

template<typename Type=GraphTypes::Default>
class Exporter{
private:
  static std::string _graphviz_headers(const Graph<Type> & graph);
  static std::string _graphviz_relations(const Graph<Type> & graph);
  static std::string _graphviz_node_label_mapping(const Graph<Type> & graph, const std::map<GraphTypes::node_id, std::string> & label_mapper);
  static std::string _graphviz_node_color_mapping(const Graph<Type> & graph, const std::map<GraphTypes::node_id, NamedColor::ColorName> & color_mapper);
  static std::string _graphviz_paths_highlighting(const Graph<Type> & graph, const std::list<GraphTypes::Path> & paths_highlight);
  static std::string _graphviz_node_meta_mapping(const Graph<Type> & graph, const std::map<GraphTypes::node_id, std::string> & label_mapper, const std::map<GraphTypes::node_id, NamedColor::ColorName> & color_mapper);
  static std::string _graphviz_footers();

public:
  static std::string ToString(const Graph<Type> & graph);

  static std::string ToMathString(const Graph<Type> & graph, const std::map<GraphTypes::node_id, std::string> & label_mapper);

  static std::string ToMathString(const Graph<Type> & graph);

  static void ToStream(const Graph<Type> & graph, std::ostream & out);

  static std::string ToGraphviz(const Graph<Type> & graph);

  static std::string ToGraphviz(const Graph<Type> & graph, const std::map<GraphTypes::node_id, std::string> & label_mapper);

  static std::string ToGraphviz(const Graph<Type> & graph, const std::map<GraphTypes::node_id, NamedColor::ColorName> & color_mapper);

  static std::string ToGraphviz(const Graph<Type> & graph, const std::list<GraphTypes::Path> & paths_highlight);

  static std::string ToGraphviz(const Graph<Type> & graph, const std::map<GraphTypes::node_id, std::string> & label_mapper, const std::map<GraphTypes::node_id, NamedColor::ColorName> & color_mapper);

  static std::string ToGraphviz(const Graph<Type> & graph, const std::map<GraphTypes::node_id, std::string> & label_mapper, const std::list<GraphTypes::Path> & paths_highlight);

  static void ToGraphviz(const Graph<Type> & graph, const std::string & filename);

  static void ToGraphviz(const Graph<Type> & graph, const std::map<GraphTypes::node_id, std::string> & label_mapper, const std::string & filename);

  static void ToGraphviz(const Graph<Type> & graph, const std::map<GraphTypes::node_id, NamedColor::ColorName> & color_mapper, const std::string & filename);

  static void ToGraphviz(const Graph<Type> & graph, const std::list<GraphTypes::Path> & paths_highlight, const std::string & filename);

  static void ToGraphviz(const Graph<Type> & graph, const std::map<GraphTypes::node_id, std::string> & label_mapper, const std::map<GraphTypes::node_id, NamedColor::ColorName> & color_mapper, const std::string & filename);

  static void ToGraphviz(const Graph<Type> & graph, const std::map<GraphTypes::node_id, std::string> & label_mapper, const std::list<GraphTypes::Path> & paths_highlight, const std::string & filename);
};

#include "Exporter.cpp"

#endif
