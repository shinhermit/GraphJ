
template<typename Type>
void Coloring<Type>::_discard_incompatibles(const Graph<Type> & graph,
					    std::list<GraphTypes::node_id> & candidates)
{

  for(std::list<GraphTypes::node_id>::iterator candidate = candidates.begin();
      candidate != candidates.end();
      ++candidate)
    {

      for(typename Graph<Type>::NodeIterator adjacent = graph.adjacents_begin(*candidate);
	  adjacent != graph.adjacents_end(*candidate);
	  ++adjacent)
	{
	  std::list<GraphTypes::node_id>::iterator pos = std::find(candidates.begin(), candidates.end(), *adjacent);
	  if( pos != candidates.end() )
	    {
	      candidates.erase(pos);
	    }
	}

    }

}

template<typename Type>
void Coloring<Type>::_colorize_remove_compatibles(std::list<GraphTypes::node_id> & candidates,
						  std::map<GraphTypes::node_id, GraphTypes::NamedColor::E_NamedColor> & color_mapper,
						  const GraphTypes::NamedColor::E_NamedColor & color,
						  std::vector<GraphTypes::node_id> & sorted_nodes)
{

  for(std::list<GraphTypes::node_id>::iterator colorable = candidates.begin();
      colorable != candidates.end();
      ++colorable)
    {
      color_mapper[*colorable] = color;

      sorted_nodes.erase( std::find(sorted_nodes.begin(), sorted_nodes.end(), *colorable) );
    }

}

template<typename Type>
void Coloring<Type>::Welsh(const Graph<Type> & graph,
			   std::map<GraphTypes::node_id, GraphTypes::NamedColor::E_NamedColor> & color_mapper)
{
  std::vector<GraphTypes::node_id> sorted_nodes;
  std::list<GraphTypes::node_id> candidates;
  GraphTypes::NamedColor::ColorNameIterator color;

  sorted_nodes.assign( graph.nodes_begin(), graph.nodes_end() );
  std::sort( sorted_nodes.begin(), sorted_nodes.end(), GraphFunctor::GreaterDegreeComparator<Type>(graph) );

  color = GraphTypes::NamedColor::Names_begin();

  while( sorted_nodes.size() > 0 )
    {

      candidates.assign(sorted_nodes.begin(), sorted_nodes.end() );

      _discard_incompatibles(graph, candidates);

      _colorize_remove_compatibles(candidates, color_mapper, *color, sorted_nodes);

      ++color; if( color == GraphTypes::NamedColor::Names_end() ) color = GraphTypes::NamedColor::Names_begin(); //pas normal :p

    }
}

template<typename Type>
std::map<GraphTypes::node_id, GraphTypes::NamedColor::E_NamedColor> Coloring<Type>::Welsh(const Graph<Type> & graph)
{
  std::map<GraphTypes::node_id, GraphTypes::NamedColor::E_NamedColor> color_mapper;

  Welsh(graph, color_mapper);

  return color_mapper;
}
