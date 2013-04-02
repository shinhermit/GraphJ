template<typename Type>
void Traverse<Type>::_Add_edge(Graph<> & marker,
			       Graph<Type> & graph,
			       const GraphTypes::node_id & source,
			       const GraphTypes::node_id & target)
{
  if(graph.is_weighted)
    marker.add_edge( source, target, graph.getCost(source, target) );

  else
    marker.add_edge(source, target);
}

template<typename Type>
void Traverse<Type>::_Breadth_once(Graph<Type> & graph,
				   const GraphTypes::node_id & node,
				   GraphFunctor::Visitor & visit,
				   Graph<> & marker)
{
  typename Graph<Type>::NodeIterator begin;
  typename Graph<Type>::NodeIterator end;
  typename Graph<Type>::NodeIterator it;
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

template<typename Type>
void Traverse<Type>::_Depth_once(Graph<Type> & graph,
				 const GraphTypes::node_id & node,
				 GraphFunctor::Visitor & visit,
				 Graph<> & marker)
{
  typename Graph<Type>::NodeIterator begin;
  typename Graph<Type>::NodeIterator end;
  typename Graph<Type>::NodeIterator it;
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

template<typename Type>
void Traverse<Type>::Nodes(Graph<Type> & graph,
			   GraphFunctor::Visitor & visit)
{
  typename Graph<Type>::NodeIterator nodeIt;

  nodeIt = graph.nodes_begin();

  while( nodeIt != graph.nodes_end() )
    {
      visit(*nodeIt);

      ++nodeIt;
    }
}

template<typename Type>
void Traverse<Type>::Breadth_once(Graph<Type> & graph, const GraphTypes::node_id & node, GraphFunctor::Visitor & visit)
{
  Graph<> marker(graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT);
  _Breadth_once(graph, node, visit, marker);
}

template<typename Type>
void Traverse<Type>::Breadth(Graph<Type> & graph,
			     GraphFunctor::Visitor & visit)
{
  typename Graph<Type>::NodeIterator nodeIt;
  Graph<> marker(graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT);

  nodeIt = graph.nodes_begin();

  while( nodeIt != graph.nodes_end() )
    {
      if( !marker.has_node(*nodeIt) )
	_Breadth_once(graph, *nodeIt, visit, marker);

      ++nodeIt;
    }

}

template<typename Type>
void Traverse<Type>::Depth_once(Graph<Type> & graph,
				const GraphTypes::node_id & node,
				GraphFunctor::Visitor & visit)
{
  Graph<> marker(graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT);

  _Depth_once(graph, node, visit, marker);
}

template<typename Type>
void Traverse<Type>::Depth(Graph<Type> & graph,
			   GraphFunctor::Visitor & visit)
{
  typename Graph<Type>::NodeIterator nodeIt;
  Graph<> marker(graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT);

  nodeIt = graph.nodes_begin();

  while( nodeIt != graph.nodes_end() )
    {
      if( !marker.has_node(*nodeIt) )
	_Depth_once(graph, *nodeIt, visit, marker);

      ++nodeIt;
    }

}


template<typename Type>
Traverse<Type>::Traverse(Graph<Type> & graph):
  _graph(graph),
  _marker( graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT )
{}

template<typename Type>
void Traverse<Type>::breadth_once(const GraphTypes::node_id & node,
				  GraphFunctor::Visitor & visit)
{
  Breadth_once(_graph, node, visit, _maker);
}

template<typename Type>
void Traverse<Type>::breadth(GraphFunctor::Visitor & visit)
{

  for(Graph<Type>::NodeIterator nodeIt nodeIt = _graph.nodes_begin();
      nodeIt != _graph.nodes_end();
      ++nodeIt)
    {

      if( !_marker.has_node(*nodeIt) )
	_Breadth_once(_graph, *nodeIt, visit, _marker);
    }

}

template<typename Type>
void Traverse<Type>::depth_once(const GraphTypes::node_id & node,
				GraphFunctor::Visitor & visit)
{
  Depth_once(_graph, node, visit, _maker);
}

template<typename Type>
void Traverse<Type>::depth(GraphFunctor::Visitor & visit)
{

  for(typename Graph<Type>::NodeIterator nodeIt = _graph.nodes_begin();
      nodeIt != _graph.nodes_end();
      ++nodeIt)
    {

      if( !_marker.has_node(*nodeIt) )
	_Depth_once(_graph, *nodeIt, visit, _marker);
    }
}

template<typename Type>
const Graph<> & Traverse<Type>::traversingGraph()const
{
  return _marker;
}
