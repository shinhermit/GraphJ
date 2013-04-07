template<typename Content>
void Traverse<Content>::_Add_edge(Graph<> & marker,
				  Graph<Content> & graph,
				  const GraphTypes::node_id & source,
				  const GraphTypes::node_id & target)
{
  if( graph.is_weighted() )
    marker.add_edge( source, target, graph.getCost(source, target) );

  else
    marker.add_edge(source, target);
}

template<typename Content>
void Traverse<Content>::_Breadth_once(Graph<Content> & graph,
				      const GraphTypes::node_id & node,
				      GraphFunctor::Visitor & visit,
				      Graph<> & marker)
{
  typename Graph<Content>::NodeIterator begin;
  typename Graph<Content>::NodeIterator end;
  typename Graph<Content>::NodeIterator it;
  GraphTypes::node_id son;
  std::deque<GraphTypes::node_id> waiters;

  marker.add_node(node);
  waiters.push_back(node);

  while( waiters.size() > 0 )
    {
      son = waiters.front();
      waiters.pop_front();
      visit(son);

      if( graph.is_directed() )
	{
	  begin = graph.successors_begin(son);
	  end = graph.successors_end(son);
	}

      else
	{
	  begin = graph.adjacents_begin(son);
	  end = graph.adjacents_end(son);
	}

      for(it = begin; it != end; ++it)
	{

	  if( !marker.has_node(*it) )
	    {
	      marker.add_node(*it);
	      waiters.push_back(*it);
	      _Add_edge(marker, graph, son, *it);
	    }
	}

    }
}

template<typename Content>
void Traverse<Content>::_Depth_once(Graph<Content> & graph,
				    const GraphTypes::node_id & node,
				    GraphFunctor::Visitor & visit,
				    Graph<> & marker)
{
  typename Graph<Content>::NodeIterator begin;
  typename Graph<Content>::NodeIterator end;
  typename Graph<Content>::NodeIterator it;
  GraphTypes::node_id curr_node;

  visit(node);
  marker.add_node(node);

  if( graph.is_directed() )
    {
      begin = graph.successors_begin(node);
      end = graph.successors_end(node);
    }

  else
    {
      begin = graph.adjacents_begin(node);
      end = graph.adjacents_end(node);
    }

  for(it=begin; it != end; ++it)
    {

      if( !marker.has_node(*it) )
	{
	  _Add_edge(marker, graph, node, *it);
	  depth_once(graph, *it, visit, marker);
	}

    }
}

template<typename Content>
void Traverse<Content>::Nodes(Graph<Content> & graph,
			      GraphFunctor::Visitor & visit)
{
  typename Graph<Content>::NodeIterator nodeIt;

  nodeIt = graph.nodes_begin();

  while( nodeIt != graph.nodes_end() )
    {
      visit(*nodeIt);

      ++nodeIt;
    }
}

template<typename Content>
void Traverse<Content>::Breadth_once(Graph<Content> & graph, const GraphTypes::node_id & node, GraphFunctor::Visitor & visit)
{
  Graph<> marker(graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT);
  _Breadth_once(graph, node, visit, marker);
}

template<typename Content>
void Traverse<Content>::Breadth(Graph<Content> & graph,
				GraphFunctor::Visitor & visit)
{
  typename Graph<Content>::NodeIterator nodeIt;
  Graph<> marker(graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT);

  nodeIt = graph.nodes_begin();

  while( nodeIt != graph.nodes_end() )
    {
      if( !marker.has_node(*nodeIt) )
	_Breadth_once(graph, *nodeIt, visit, marker);

      ++nodeIt;
    }

}

template<typename Content>
void Traverse<Content>::Depth_once(Graph<Content> & graph,
				   const GraphTypes::node_id & node,
				   GraphFunctor::Visitor & visit)
{
  Graph<> marker(graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT);

  _Depth_once(graph, node, visit, marker);
}

template<typename Content>
void Traverse<Content>::Depth(Graph<Content> & graph,
			      GraphFunctor::Visitor & visit)
{
  typename Graph<Content>::NodeIterator nodeIt;
  Graph<> marker(graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT);

  nodeIt = graph.nodes_begin();

  while( nodeIt != graph.nodes_end() )
    {
      if( !marker.has_node(*nodeIt) )
	_Depth_once(graph, *nodeIt, visit, marker);

      ++nodeIt;
    }

}


template<typename Content>
Traverse<Content>::Traverse(Graph<Content> & graph):
  _graph(graph),
  _marker( graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT )
{}

template<typename Content>
void Traverse<Content>::breadth_once(const GraphTypes::node_id & node,
				     GraphFunctor::Visitor & visit)
{
  if( _marker.nodes_size() != 0 )
    _marker = Graph<>( _graph.edgeType(), _graph.edgeState(), GraphTypes::NOCONTENT );

  _Breadth_once(_graph, node, visit, _marker);
}

template<typename Content>
void Traverse<Content>::breadth(GraphFunctor::Visitor & visit)
{

  for(typename Graph<Content>::NodeIterator nodeIt = _graph.nodes_begin();
      nodeIt != _graph.nodes_end();
      ++nodeIt)
    {

      if( !_marker.has_node(*nodeIt) )
	_Breadth_once(_graph, *nodeIt, visit, _marker);
    }

}

template<typename Content>
void Traverse<Content>::depth_once(const GraphTypes::node_id & node,
				   GraphFunctor::Visitor & visit)
{
  if( _marker.nodes_size() != 0 )
    _marker = Graph<>( _graph.edgeType(), _graph.edgeState(), GraphTypes::NOCONTENT );

  _Depth_once(_graph, node, visit, _marker);
}

template<typename Content>
void Traverse<Content>::depth(GraphFunctor::Visitor & visit)
{

  for(typename Graph<Content>::NodeIterator nodeIt = _graph.nodes_begin();
      nodeIt != _graph.nodes_end();
      ++nodeIt)
    {

      if( !_marker.has_node(*nodeIt) )
	_Depth_once(_graph, *nodeIt, visit, _marker);
    }
}

template<typename Content>
Graph<> & Traverse<Content>::traversingGraph()
{
  return _marker;
}
