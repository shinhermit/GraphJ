#ifndef _Exporter
#define _Exporter

#include <iostream>
#include <string>
#include <sstream>
#include <memory>

#include "Traverse.hpp"
#include "GraphvizAttributesHolder.hpp" 
#include "GraphFunctor.hpp"
#include "Color.hpp"
#include "NamedColor.hpp"
#include "MpmNetwork.hpp"

template<typename Type=GraphTypes::Default>
class Exporter{
private:
  static std::string _graphviz_headers(const Graph<Type> & graph,
				       const GraphvizAttributesHolder & config);

  static std::string _graphviz_nodes(const Graph<Type> & graph,
				     const GraphvizAttributesHolder & config);

  static std::string _graphviz_edges(const Graph<Type> & graph,
				     const GraphvizAttributesHolder & config);

  static std::string _graphviz_footers();

  static void _highlight_node(GraphvizAttributesHolder & config,
			      const GraphTypes::node_id & node,
			      const GraphTypes::Color & color,
			      const GraphTypes::Graphviz::StyleAttribute & nodeStyle=GraphTypes::Graphviz::StyleAttribute::DEFAULT_STYLE);

  static void _highlight_edge(GraphvizAttributesHolder & config,
			      const Edge & edge,
			      const GraphTypes::Color & color);

  static void _mpm_node_prepare(const MpmNetwork & network,
				GraphvizAttributesHolder & config,
				const GraphTypes::node_id & node);

public:
  static std::string ToString(const Graph<Type> & graph);

  static std::string ToMathString(const Graph<Type> & graph);

  static std::string ToMathString(const Graph<Type> & graph,
				  const std::map<GraphTypes::node_id, std::string> & label_mapper);

  static void ToStream(const Graph<Type> & graph,
		       std::ostream & out);

  static void GraphvizPathHighlight(GraphvizAttributesHolder & config,
				     const GraphTypes::Path & path,
				    const GraphTypes::Color & col=GraphTypes::NamedColor::Red,
				    const GraphTypes::Graphviz::StyleAttribute & nodeStyle=GraphTypes::Graphviz::StyleAttribute::DEFAULT_STYLE);

  static void GraphvizPathsHighlight(GraphvizAttributesHolder & config,
				     const std::list<GraphTypes::Path> & paths,
				     const GraphTypes::Graphviz::StyleAttribute & nodeStyle=GraphTypes::Graphviz::StyleAttribute::DEFAULT_STYLE);

  static void GraphvizMpmPrepare(const MpmNetwork & network,
				 GraphvizAttributesHolder & config);

  static std::string ToGraphviz(const Graph<Type> & graph,
				const GraphvizAttributesHolder & config);

  static std::string ToGraphviz(const Graph<Type> & graph);

  static void ToGraphviz(const Graph<Type> & graph,
			 const GraphvizAttributesHolder & config,
			 const std::string & filename);

  static void ToGraphviz(const Graph<Type> & graph,
			 const std::string & filename);
};

#include "Exporter.cpp"

#endif
