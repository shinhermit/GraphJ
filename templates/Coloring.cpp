template<typename Type>
std::set<WeightedNode> Coloring<Type>::_sort_nodes_by_degrees(Graph<Type> & graph){
  std::set<WeightedNode> sorted_nodes;
  typename Graph<Type>::NodeIterator node;

  node = graph.nodes_begin();

  while( node != graph.nodes_end() )
    {
      sorted_nodes.insert( WeightedNode(*node, graph.degree(*node)) );

      ++node;
    }

  return sorted_nodes;
}

template<typename Type>
bool Coloring<Type>::_partite_compatible(Graph<Type> graph, GraphTypes::node_id node, std::set<GraphTypes::node_id> partite){
  std::set<GraphTypes::node_id>::iterator it;
  bool compatible;

  compatible = true;
  it = partite.begin();
  while( it != partite.end() && compatible )
    {
      if( graph.has_edge(node, *it) )
	compatible = false;

      ++it;
    }

  return compatible;
}

template<typename Type>
std::map<GraphTypes::node_id, NamedColor::ColorName> Coloring<Type>::welsh(Graph<Type> & graph){
  std::set<WeightedNode> sorted_nodes;
  std::set<WeightedNode>::iterator it_sn;
  std::set<NamedColor::ColorName> allColors;
  std::set<NamedColor::ColorName>::iterator it_color;
  std::set<GraphTypes::node_id> partite; //the current partite (stable)
  std::map<GraphTypes::node_id, NamedColor::ColorName> color_mapper;
  GraphTypes::node_id node, current_node;

  sorted_nodes = _sort_nodes_by_degrees(graph);
  allColors = NamedColor::allNames();
  it_color = allColors.begin();

  while( sorted_nodes.size() > 0 ) //should check for color lack
    {
      node = sorted_nodes.rbegin()->id();
      partite.clear(); //possible issue: really empty ?

      color_mapper.insert( std::pair<GraphTypes::node_id, NamedColor::ColorName>(node, *it_color) );
      partite.insert( node );

      sorted_nodes.erase( --sorted_nodes.end() ); //same as --rbegin().base()

      it_sn = sorted_nodes.begin();
      while( it_sn != sorted_nodes.end() )
	{
	  current_node = it_sn->id();

	  if( _partite_compatible(graph, current_node, partite) )
	    {
	      color_mapper.insert( std::pair<GraphTypes::node_id, NamedColor::ColorName>(current_node, *it_color) );
	      partite.insert(current_node);
	      sorted_nodes.erase(it_sn++);
	    }
	  else
	    {
	      ++it_sn;
	    }

	}

      ++it_color;
    }

  return color_mapper;
}
