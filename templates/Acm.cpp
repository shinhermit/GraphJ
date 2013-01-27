
template<typename Type>
void Acm<Type>::_color_each_node(const Graph<Type> & graph, std::map<GraphTypes::node_id, GraphTypes::Algorithms::Color> & color_mapper)
{
  GraphTypes::Algorithms::Color color;
  typename Graph<Type>::NodeIterator nodeIt;

  color = 0;

  nodeIt = graph.nodes_begin();
  while( nodeIt != graph.nodes_end() )
    {

      color_mapper.insert( std::pair<GraphTypes::node_id, GraphTypes::Algorithms::Color>(*nodeIt, color) );

      ++color;

      ++nodeIt;
    }

}

template<typename Type>
void Acm<Type>::_update_colors(const Graph<> & acm, std::map<GraphTypes::node_id, GraphTypes::Algorithms::Color> & color_mapper, const GraphTypes::node_id & node1, const GraphTypes::node_id & node2)
{
  GraphTypes::Algorithms::Color col1, col2, master_col;
  bool has1, has2;
  std::map<GraphTypes::node_id, GraphTypes::Algorithms::Color>::iterator it_col1, it_col2;

  has1 = acm.has_node(node1);
  has2 = acm.has_node(node2);

  it_col1 = color_mapper.find(node1);
  it_col2 = color_mapper.find(node2);

  col1 = it_col1->second;
  col2 = it_col2->second;

  if(!has1 && !has2)
    {
      master_col = col1;

      it_col1->second = master_col;
      it_col2->second = master_col;
    }

  else if(has1 && !has2)
    {
      it_col2->second = col1;
    }

  else if(has2 && !has1)
    {
      it_col1->second = col2;
    }

  else
    {
      GraphFunctor::ColorizingVisitor recolorize(color_mapper, col1);

      Traverse<Type>::Breadth_once(const_cast<Graph<>&>(acm), node2, recolorize);
    }
}

template<typename Type>
Graph<> Acm<Type>::Kruskal(const Graph<Type> & graph) throw(GraphException::InvalidOperation, GraphException::InvalidEdge, GraphException::InvalidNodeID)
{

  Graph<> acm(GraphTypes::UNDIRECTED, GraphTypes::WEIGHTED, GraphTypes::NOCONTENT);
  std::map<GraphTypes::node_id, GraphTypes::Algorithms::Color> color;
  std::vector<Edge> sorted_edges;
  std::vector<Edge>::iterator it;
  GraphTypes::node_id origin, target;

  if( graph.is_directed() || !graph.is_weighted() )
    {
      throw GraphException::InvalidOperation("This kruskal Algorithm is designed for undirected weighted graphs.", __LINE__, __FILE__, "Acm<Type>::kruskal(const Graph<Type>&)");
    }

  _color_each_node(graph, color);

  sorted_edges.assign( graph.edges_begin(), graph.edges_end() );
  std::sort( sorted_edges.begin(), sorted_edges.end(), GraphFunctor::WeightedEdgeComparator<Type>(graph) );

  it = sorted_edges.begin();

  while( it != sorted_edges.end() && acm.edges_size() < graph.nodes_size() - 1 )
    {
      origin = it->source();
      target = it->target();

      if( color[origin] != color[target] )
	{
	  _update_colors(acm, color, origin, target);

	  acm.add_edge( origin, target, graph.getCost(origin, target) );
	}

      ++it;
    }

  return acm;
}

template<typename Type>
void Acm<Type>::_init_tables(const Graph<Type> & graph, std::map<GraphTypes::node_id, GraphTypes::Cost> & distance, std::map<GraphTypes::node_id, GraphTypes::node_id> & predecessor)
{
  typename Graph<Type>::NodeIterator node;
  GraphTypes::node_id premier;
  GraphTypes::Cost weight;

  if(graph.nodes_size() > 0)
    {
      node = graph.nodes_begin();
      premier = *node;

      ++node;
      while( node != graph.nodes_end() )
	{
	  weight = graph.has_edge(premier, *node) ? graph.getCost(premier, *node) : GraphTypes::Algorithms::POSITIVE_INFINITY;

	  distance[*node] = weight;
	  predecessor[*node] = premier;

	  ++node;
	}
    }
}
				      
template<typename Type>
void Acm<Type>::_update_tables(const Graph<Type> & graph, const Graph<Type> & acm, const GraphTypes::node_id & closest, std::map<GraphTypes::node_id, GraphTypes::Cost> & distance, std::map<GraphTypes::node_id, GraphTypes::node_id> & predecessor)
{

  GraphTypes::Cost new_distance;

  for(typename Graph<Type>::NodeIterator adjacent = graph.adjacents_begin(closest);
      adjacent != graph.adjacents_end(closest);
      ++adjacent)
    {
      new_distance = graph.getCost(closest, *adjacent);

      if( !acm.has_node(*adjacent) )
	{

	  if(new_distance < distance[*adjacent])
	    {
	      distance[*adjacent] = new_distance;

	      predecessor[*adjacent] = closest;
	    }

	}
    }

  distance.erase(closest);

}

template<typename Type>
Graph<> Acm<Type>::Prim(const Graph<Type> & graph) throw(GraphException::InvalidOperation, GraphException::InvalidEdge, GraphException::InvalidNodeID)
{

  Graph<> acm(GraphTypes::UNDIRECTED, GraphTypes::WEIGHTED, GraphTypes::NOCONTENT);
  std::map<GraphTypes::node_id, GraphTypes::Cost> distance;
  std::map<GraphTypes::node_id, GraphTypes::node_id> predecessor;
  std::map<GraphTypes::node_id, GraphTypes::Cost>::iterator closest;
  GraphTypes::node_id origin, target;
  bool allInfinite;

  if( graph.is_directed() || !graph.is_weighted() )
    {
      throw GraphException::InvalidOperation("This Prim Algorithm is designed for undirected weighted graphs.", __LINE__, __FILE__, "Acm<Type>::prim(const Graph<Type>&)");
    }

  _init_tables(graph, distance, predecessor);

  allInfinite = false;

  while(distance.size() > 0 && !allInfinite )
    {
      closest = std::min_element( distance.begin(), distance.end(),
  				  GraphFunctor::MapValueComparator<GraphTypes::node_id, GraphTypes::Cost>() );

      if( closest->second != GraphTypes::Algorithms::POSITIVE_INFINITY )
      	{
      	  target = closest->first;
      	  origin = predecessor[target];

      	  acm.add_edge( origin,target, graph.getCost(origin,target) );

      	  _update_tables(graph, acm, target, distance, predecessor);
      	}

      else
      	{
      	  allInfinite = true;
      	}
    }

  return acm;
}
