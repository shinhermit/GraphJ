#ifndef _Coloring
#define _Coloring

#include <algorithm>
#include <vector>
#include <list>
#include <iostream>
#include "Graph.hpp"
#include "GraphFunctor.hpp"
#include "NamedColor.hpp"

template<typename Type=GraphTypes::Default>
class Coloring{
private:
  static void _discard_incompatibles(const Graph<Type> & graph,
				     std::list<GraphTypes::node_id> & candidates);

  static void _colorize_remove_compatibles(std::list<GraphTypes::node_id> & candidates,
				    std::map<GraphTypes::node_id, GraphTypes::NamedColor::E_NamedColor> & color_mapper,
				    const GraphTypes::NamedColor::E_NamedColor & color,
				    std::vector<GraphTypes::node_id> & sorted_nodes);

public:
  static void Welsh(const Graph<Type> & graph,
		    std::map<GraphTypes::node_id, GraphTypes::NamedColor::E_NamedColor> & color_mapper);
  
  static std::map<GraphTypes::node_id, GraphTypes::NamedColor::E_NamedColor> Welsh(const Graph<Type> & graph);
};

#include "Coloring.cpp"

#endif
