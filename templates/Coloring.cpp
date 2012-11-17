template<typename Type>
std::set<WeightedNode> Coloring<Type>::_sort_nodes_by_degrees(Graph<Type> & graph){
  std::set<WeightedNode> sorted_nodes;
  Node::node_id node;
  unsigned long i, nodes_size;

  node = graph.first_node();
  nodes_size = graph.nodes_size();
  i = 0;

  while(i < nodes_size)
    {
      sorted_nodes.insert( WeightedNode(node, graph.degree(node)) );

      node = graph.next_node();
      i++;
    }

  return sorted_nodes;
}

template<typename Type>
bool Coloring<Type>::_partite_compatible(Graph<Type> graph, Node::node_id node, std::set<Node::node_id> partite){
  std::set<Node::node_id>::iterator it;
  bool compatible;

  compatible = true;
  it = partite.begin();
  while( it != partite.end() && compatible )
    {
      if( graph.has_edge(node, *it) )
	compatible = false;

      it++;
    }

  return compatible;
}

template<typename Type>
std::map<Node::node_id, NamedColor::ColorName> Coloring<Type>::welsh(Graph<Type> & graph){
  std::set<WeightedNode> sorted_nodes;
  std::set<WeightedNode>::iterator it_sn;
  std::set<NamedColor::ColorName> allColors;
  std::set<NamedColor::ColorName>::iterator it_color;
  std::map<NamedColor::ColorName, std::set<Node::node_id> > partites_list; //liste des stables
  std::map<Node::node_id, NamedColor::ColorName> color_mapper;
  Node::node_id node, current_node;

  sorted_nodes = _sort_nodes_by_degrees(graph);
  allColors = NamedColor::allNames();
  it_color = allColors.begin();

  while( sorted_nodes.size() > 0 ) //should check for color lack
    {
      node = sorted_nodes.rbegin()->id();

      color_mapper.insert( std::pair<Node::node_id, NamedColor::ColorName>(node, *it_color) );
      partites_list.insert( std::pair<NamedColor::ColorName, std::set<Node::node_id> >( *it_color, std::set<Node::node_id>() ) );
      partites_list[*it_color].insert(node);

      sorted_nodes.erase( --sorted_nodes.end() ); //same as --rbegin().base()

      for( it_sn = sorted_nodes.begin(); it_sn != sorted_nodes.end(); it_sn++ )
	{
	  current_node = it_sn->id();

	  if( _partite_compatible(graph, current_node, partites_list[*it_color]) )
	    {
	      color_mapper.insert( std::pair<Node::node_id, NamedColor::ColorName>(current_node, *it_color) );
	      partites_list[*it_color].insert(current_node);
	      sorted_nodes.erase(it_sn++);
	    }

	}

      it_color++;
    }

  return color_mapper;
}
