
template<typename Type>
void Traverse<Type>::_Breadth_once(Graph<Type> & graph,
				   const GraphTypes::node_id & node,
				   GraphFunctor::Visitor & visit,
				   std::set<GraphTypes::node_id> & marker)
{
  typename Graph<Type>::NodeIterator begin;
  typename Graph<Type>::NodeIterator end;
  typename Graph<Type>::NodeIterator it;
  GraphTypes::node_id son;
  std::deque<GraphTypes::node_id> waiters;

  waiters.push_back(node);

  while( waiters.size() > 0 )
    {
      son = waiters.front();
      waiters.pop_front();
      visit(son);
      marker.insert(son);

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

	  if( !marker.count(*it) )
	    {
	      marker.insert(*it);
	      waiters.push_back(*it);
	    }
	}

    }
}

template<typename Type>
void Traverse<Type>::_Depth_once(Graph<Type> & graph,
				 const GraphTypes::node_id & node,
				 GraphFunctor::Visitor & visit,
				 std::set<GraphTypes::node_id> & marker)
{
  typename Graph<Type>::NodeIterator begin;
  typename Graph<Type>::NodeIterator end;
  typename Graph<Type>::NodeIterator it;
  GraphTypes::node_id curr_node;

  visit(node);
  marker.insert(node);

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

      if( !marker.count(*it) )
	{
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
  std::set<GraphTypes::node_id> marker;
  _Breadth_once(graph, node, visit, marker);
}

template<typename Type>
void Traverse<Type>::Breadth(Graph<Type> & graph,
			     GraphFunctor::Visitor & visit)
{
  typename Graph<Type>::NodeIterator nodeIt;
  std::set<GraphTypes::node_id> marker;

  nodeIt = graph.nodes_begin();

  while( nodeIt != graph.at_nodes_end() )
    {
      if( !marker.count(*nodeIt) )
	_Breadth_once(graph, *nodeIt, visit, marker);

      ++nodeIt;
    }

}

template<typename Type>
void Traverse<Type>::Depth_once(Graph<Type> & graph,
				const GraphTypes::node_id & node,
				GraphFunctor::Visitor & visit)
{
  std::set<GraphTypes::node_id> marker;

  _Depth_once(graph, node, visit, marker);
}

template<typename Type>
void Traverse<Type>::Depth(Graph<Type> & graph,
			   GraphFunctor::Visitor & visit)
{
  typename Graph<Type>::NodeIterator nodeIt;
  std::set<GraphTypes::node_id> marker;

  nodeIt = graph.nodes_begin();

  while( nodeIt != graph.nodes_end() )
    {
      if( !marker.count(*nodeIt) )
	_Depth_once(graph, *nodeIt, visit, marker);

      ++nodeIt;
    }

}
