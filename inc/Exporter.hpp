#ifndef _Exporter
#define _Exporter

#include <iostream>
#include <string>
#include <sstream>
#include "Traverse.hpp"
#include "GraphvizAttributesHolder.hpp" 
#include "GraphFunctor.hpp"
#include "Color.hpp"
#include "NamedColor.hpp"

template<typename Type=GraphTypes::Default>
class Exporter{
private:
  static std::string _graphviz_headers(const Graph<Type> & graph,
				       GraphvizAttributesHolder & config);

  static std::string _graphviz_nodes(const Graph<Type> & graph,
				     GraphvizAttributesHolder & config);

  static std::string _graphviz_edges(const Graph<Type> & graph,
				     GraphvizAttributesHolder & config);

  static void _highlight_node(GraphvizAttributesHolder & config,
			      const GraphTypes::node_id & node,
			      const GraphTypes::NamedColor::E_NamedColor & color);

  static void _highlight_edge(GraphvizAttributesHolder & config,
			      const Edge & edge,
			      const GraphTypes::NamedColor::E_NamedColor & color);

  static void _graphviz_paths_highlight(GraphvizAttributesHolder & config,
					const std::list<GraphTypes::Path> & paths_highlight);

  static std::string _graphviz_footers();

public:
  static std::string ToString(const Graph<Type> & graph);

  static std::string ToMathString(const Graph<Type> & graph);

  static std::string ToMathString(const Graph<Type> & graph,
				  const std::map<GraphTypes::node_id, std::string> & label_mapper);

  static void ToStream(const Graph<Type> & graph,
		       std::ostream & out);

  static std::string ToGraphviz(const Graph<Type> & graph,
				GraphvizAttributesHolder & config);

  static std::string ToGraphviz(const Graph<Type> & graph);

  static std::string ToGraphviz(const Graph<Type> & graph,
				GraphvizAttributesHolder & config,
				const std::list<GraphTypes::Path> & paths_highlight);

  static std::string ToGraphviz(const Graph<Type> & graph,
				const std::list<GraphTypes::Path> & paths_highlight);

  static void ToGraphviz(const Graph<Type> & graph,
			 GraphvizAttributesHolder & config,
			 const std::string & filename);

  static void ToGraphviz(const Graph<Type> & graph,
			 const std::string & filename);

  static void ToGraphviz(const Graph<Type> & graph,
			 GraphvizAttributesHolder & config,
			 const std::list<GraphTypes::Path> & paths_highlight,
			 const std::string & filename);

  static void ToGraphviz(const Graph<Type> & graph,
			 const std::list<GraphTypes::Path> & paths_highlight,
			 const std::string & filename);
};

#include "Exporter.cpp"

#endif
