
template <typename Type>
XPathFinding<Type>::XPathFinding()
  :_resultGraph(GraphTypes::DIRECTED, GraphTypes::WEIGHTED, GraphTypes::NOCONTENT)
{}

template <typename Type>
void XPathFinding<Type>::_reset()
{

  if(_distance_from_source.size() != 0)
    _distance_from_source.clear();

  if(_best_predecessors.size() != 0)
    _best_predecessors.clear();

  if(_resultGraph.nodes_size() != 0)
    _resultGraph = Graph<>(GraphTypes::DIRECTED, GraphTypes::WEIGHTED, GraphTypes::NOCONTENT);

  if(_foundPaths.size() != 0)
    _foundPaths.clear();
}

template <typename Type>
void XPathFinding<Type>::_init(const Graph<Type> & graph,
			       const GraphFunctor::EdgeWeighter<Type> & getCost,
			       const GraphTypes::node_id & sourceNode,
			       std::list<GraphTypes::node_id> & candidates)
{
  typename Graph<Type>::NodeIterator it;
  GraphTypes::Cost distance;

  _reset();

  _distance_from_source[sourceNode] = 0;
  _resultGraph.add_node(sourceNode);

  for(it = graph.nodes_begin(); it != graph.nodes_end(); ++it)
    {
      _best_predecessors[*it] = std::list<GraphTypes::node_id>();
      _best_predecessors[*it].push_back(sourceNode);

      if(*it != sourceNode)
	{
	  candidates.push_back(*it);

	  if( graph.has_edge(sourceNode, *it) )
	    {
	      distance = getCost(graph, sourceNode, *it);
	    }

	  else
	    {
	      distance = GraphTypes::Algorithms::POSITIVE_INFINITY;
	    }

	  _distance_from_source[*it] = distance;
	}

    }
}

template <typename Type>
std::list<GraphTypes::node_id> XPathFinding<Type>::_allClosest(const std::list<GraphTypes::node_id> & candidates)
{
  GraphTypes::node_id closest;
  GraphTypes::Cost d_closest, new_distance;
  std::list<GraphTypes::node_id>::const_iterator node;
  std::list<GraphTypes::node_id> allClosest;

  node = candidates.begin();

  closest = *node;
  d_closest = _distance_from_source.find(closest)->second;
  allClosest.push_back(closest);

  ++node;
  while( node != candidates.end() )
    {

      new_distance = _distance_from_source.find(*node)->second;

      if( new_distance < d_closest )
	{
	  d_closest = new_distance;
	  closest = *node;

	  allClosest.clear();
	  allClosest.push_back(closest);
	}

      else if(new_distance == d_closest)
	{
	  allClosest.push_back(*node);
	}

      ++node;

    }

  return allClosest;
}

template <typename Type>
void XPathFinding<Type>::_add_edges(const Graph<Type> & graph,
				    const GraphFunctor::EdgeWeighter<Type> & getCost,
				    const std::list<GraphTypes::node_id> allClosest)
{
  std::list<GraphTypes::node_id>::const_iterator closest, pred;

  for(closest = allClosest.begin(); closest != allClosest.end(); ++closest)
    {

      std::list<GraphTypes::node_id> & best_preds = _best_predecessors.find(*closest)->second;

      for(pred = best_preds.begin(); pred != best_preds.end(); ++pred)
	{
	  _resultGraph.add_edge( *pred, *closest, getCost(graph, *pred, *closest) );
	}

    }
}

template <typename Type>
void XPathFinding<Type>::_remove_nodes(std::list<GraphTypes::node_id> & candidates,
				       const std::list<GraphTypes::node_id> & allClosest)
{
  std::list<GraphTypes::node_id>::const_iterator closest;

  for(closest = allClosest.begin(); closest != allClosest.end(); ++closest)
    {
      candidates.remove(*closest);
    }
}

template <typename Type>
void XPathFinding<Type>::_update_tables(const Graph<Type> & graph,
					const GraphFunctor::EdgeWeighter<Type> & getCost,
					const std::list<GraphTypes::node_id> allClosest)
{
  typename Graph<Type>::NodeIterator succ;
  std::list<GraphTypes::node_id>::const_iterator closest;
  GraphTypes::Cost distance, new_distance;

  for(closest = allClosest.begin(); closest != allClosest.end(); ++closest)
    {

      for(succ = graph.successors_begin(*closest); succ != graph.successors_end(*closest); ++succ)
	{

	  if( !_resultGraph.has_node(*succ) )
	    {
	      distance = _distance_from_source[*succ];
	      new_distance = _distance_from_source[*closest] + getCost(graph, *closest, *succ);

	      if(new_distance < distance)
		{
		  _distance_from_source[*succ] = new_distance;

		  _best_predecessors[*succ].clear();
		  _best_predecessors[*succ].push_back(*closest);
		}

	      else if(new_distance == distance)
		{
		  _best_predecessors[*succ].push_back(*closest);
		}

	    }
	}

    }
}

template <typename Type>
void XPathFinding<Type>::Xdijkstra(const Graph<Type> & graph,
				   const GraphFunctor::EdgeWeighter<Type> & getCost,
				   const GraphTypes::node_id & sourceNode
				   ) throw(GraphException::InvalidOperation)
{
  std::list<GraphTypes::node_id> candidates, allClosest;
  GraphTypes::node_id closest;
  bool allInfinite;


  if( !graph.is_directed() || !graph.is_weighted() )
    {
      throw GraphException::InvalidOperation("This implemention of Dijkstra'algorithm has been designed for directed weighted graphs", __LINE__, __FILE__, "XPathFinding<Type>::Xdijkstra(const Graph<Type>&, const GraphTypes::node_id&)");
    }

  //initialisation des tables
  _init(graph, getCost, sourceNode, candidates);

  //début de l'algorithme
  allInfinite = false;

  while( _resultGraph.nodes_size() < graph.nodes_size() && !allInfinite )
    {
      allClosest = _allClosest(candidates);

      closest = *allClosest.begin();

      if(_distance_from_source[closest] == GraphTypes::Algorithms::POSITIVE_INFINITY)
	{
	  allInfinite = true;
	}

      else
	{
	  _update_tables(graph, getCost, allClosest);

	  _add_edges(graph, getCost, allClosest);

	  _remove_nodes(candidates, allClosest);
	}

    }

}

template <typename Type>
void XPathFinding<Type>::Xdijkstra(const Graph<Type> & graph,
				   const GraphTypes::node_id & sourceNode
				   ) throw(GraphException::InvalidOperation)
{
  GraphFunctor::DefaultEdgeWeighter<Type> getCost;

  Xdijkstra(graph, getCost, sourceNode);
}

template <typename Type>
void XPathFinding<Type>::dual_Xdijkstra(Graph<Type> & graph,
					const GraphFunctor::EdgeWeighter<Type> & getCost,
					const GraphTypes::node_id & targetNode
					) throw(GraphException::InvalidOperation)
{
  graph.reverse_edges();

  Xdijkstra(graph, getCost, targetNode);

  graph.reverse_edges();
  _resultGraph.reverse_edges();
}

template <typename Type>
void XPathFinding<Type>::dual_Xdijkstra(Graph<Type> & graph,
				   const GraphTypes::node_id & targetNode
				   ) throw(GraphException::InvalidOperation)
{
  GraphFunctor::DefaultEdgeWeighter<Type> getCost;

  dual_Xdijkstra(graph, getCost, targetNode);
}

template <typename Type>
void XPathFinding<Type>::_init(const Graph<Type> & graph,
			       const GraphTypes::node_id & sourceNode,
			       std::list<GraphTypes::node_id> & candidates,
			       const GraphTypes::Algorithms::OptimizationType & optimizationType)
{
  typename Graph<Type>::NodeIterator it;
  GraphTypes::Cost infinite;

  _reset();

  infinite = (optimizationType == GraphTypes::Algorithms::MINIMIZE) ? GraphTypes::Algorithms::POSITIVE_INFINITY : GraphTypes::Algorithms::NEGATIVE_INFINITY;

  _distance_from_source[sourceNode] = 0;
  _resultGraph.add_node(sourceNode);

  for(it = graph.nodes_begin(); it != graph.nodes_end(); ++it)
    {

      if(*it != sourceNode)
	{
	  _distance_from_source[*it] = infinite;

	  candidates.push_back(*it);
	}

    }
}

template <typename Type>
std::deque<GraphTypes::node_id> XPathFinding<Type>::_coupe(const Graph<Type> & graph,
							   const std::list<GraphTypes::node_id> & candidates)
{
  typename Graph<Type>::NodeIterator pred;
  std::list<GraphTypes::node_id>::const_iterator s;
  std::deque<GraphTypes::node_id> relaxed;
  bool relaxable;

  s = candidates.begin();
  while(s != candidates.end())
    {

      relaxable = false;

      pred = graph.predecessors_begin(*s);

      if( pred != graph.predecessors_end(*s) )
	{
	  relaxable = true;

	  while(pred != graph.predecessors_end(*s) && relaxable)
	    {

	      if( !_resultGraph.has_node(*pred) )
		{
		  relaxable = false;
		}

	      ++pred;
	    }

	}

      if(relaxable)
	{
	  relaxed.push_back(*s);
	}

      ++s;
    }

  return relaxed;
}

template <typename Type>
void XPathFinding<Type>::_update_tables(const Graph<Type> & graph,
					const GraphFunctor::EdgeWeighter<Type> & getCost,
					const std::deque<GraphTypes::node_id> & waiting_for_insertion,
					const GraphTypes::Algorithms::OptimizationType & optimizationType)
{
  typename Graph<Type>::NodeIterator pred;
  std::deque<GraphTypes::node_id>::const_iterator s;
  GraphTypes::Cost new_distance;
  bool optimal;

  for(s = waiting_for_insertion.begin(); s != waiting_for_insertion.end(); ++s)
    {

      std::list<GraphTypes::node_id> & s_best_preds = _best_predecessors[*s];
      GraphTypes::Cost & s_distance = _distance_from_source[*s];

      for(pred = graph.predecessors_begin(*s); pred != graph.predecessors_end(*s); ++pred)
	{

	  if( _resultGraph.has_node(*pred) )
	    {

	      new_distance = _distance_from_source[*pred] + getCost(graph, *pred, *s);

	      optimal = (optimizationType == GraphTypes::Algorithms::MINIMIZE) ? (new_distance < s_distance) : (new_distance > s_distance);

	      if(optimal)
		{
		  s_distance = new_distance;

		  s_best_preds.clear();
		  s_best_preds.push_back(*pred);
		}

	      else if(new_distance == s_distance)
		{
		  s_best_preds.push_back(*pred);	
		}

	    }
	}

    }
}

template <typename Type>
void XPathFinding<Type>::_insert_waiting_nodes(const Graph<Type> & graph,
					       const GraphFunctor::EdgeWeighter<Type> & getCost,
					       std::deque<GraphTypes::node_id> & waiting_for_insertion)
{
  std::list<GraphTypes::node_id>::const_iterator pred;
  GraphTypes::node_id s;

  while( waiting_for_insertion.size() > 0 )
    {

      s  = waiting_for_insertion.front();

      const std::list<GraphTypes::node_id> & predecessors = _best_predecessors.find(s)->second;

      for(pred = predecessors.begin(); pred != predecessors.end(); ++pred)
	{
	  _resultGraph.add_edge( *pred, s, getCost(graph, *pred, s) );
	}

      waiting_for_insertion.pop_front();

    }
}

template <typename Type>
void XPathFinding<Type>::_remove_nodes(std::list<GraphTypes::node_id> & candidates,
				       const std::deque<GraphTypes::node_id> & waiting_for_insertion)
{
  std::deque<GraphTypes::node_id>::const_iterator node;

  for(node = waiting_for_insertion.begin(); node != waiting_for_insertion.end(); ++node)
    {
      candidates.remove(*node);
    }
}

template <typename Type>
void XPathFinding<Type>::_greedy_bellman(const Graph<Type> & graph,
					 const GraphFunctor::EdgeWeighter<Type> & getCost,
					 const GraphTypes::node_id & sourceNode,
					 const GraphTypes::Algorithms::OptimizationType & optimizationType)
{
  std::list<GraphTypes::node_id> candidates;
  std::deque<GraphTypes::node_id> waiting_for_insertion;

  _init(graph, sourceNode, candidates, optimizationType);

  waiting_for_insertion = _coupe(graph, candidates);

  while( waiting_for_insertion.size() > 0 )
    {

      _update_tables(graph, getCost, waiting_for_insertion, optimizationType);

      _remove_nodes(candidates, waiting_for_insertion);

      _insert_waiting_nodes(graph, getCost, waiting_for_insertion);

      waiting_for_insertion = _coupe(graph, candidates);

    }

}

template <typename Type>
void XPathFinding<Type>::_init(const Graph<Type> & graph,
			       const GraphTypes::node_id & sourceNode,
			       const GraphTypes::Algorithms::OptimizationType & optimizationType)
{
  typename Graph<Type>::NodeIterator node;
  GraphTypes::Cost infinite;

  _reset();

  infinite = (optimizationType == GraphTypes::Algorithms::MINIMIZE) ? GraphTypes::Algorithms::POSITIVE_INFINITY : GraphTypes::Algorithms::NEGATIVE_INFINITY;

  _distance_from_source[sourceNode] = 0;
  _resultGraph.add_node(sourceNode);

  for(node = graph.nodes_begin(); node != graph.nodes_end(); ++node)
    {

      if(*node != sourceNode)
	{
	  _distance_from_source[*node] = infinite;
	}

    }
}

template <typename Type>
void XPathFinding<Type>::_update_tables(const Graph<Type> & graph,
					const GraphFunctor::EdgeWeighter<Type> & getCost,
					const GraphTypes::Algorithms::OptimizationType & optimizationType)
{
  typename Graph<Type>::EdgeIterator it;
  GraphTypes::node_id pred, succ;
  GraphTypes::Cost new_distance;
  bool optimal;

  for(it = graph.edges_begin(); it != graph.edges_end(); ++it)
    {
      pred = it->source();
      succ = it->target();

      GraphTypes::Cost & distance = _distance_from_source[succ];
      std::list<GraphTypes::node_id> & pred_list = _best_predecessors[succ];

      new_distance = _distance_from_source[pred] + getCost(graph, pred,succ);


      optimal = (optimizationType == GraphTypes::Algorithms::MINIMIZE) ? (new_distance < distance) : (new_distance > distance);

      if(optimal)
	{
	  distance = new_distance;

	  pred_list.clear();
	  pred_list.push_back(pred);
	}

      else if(new_distance == distance)
	{
	  pred_list.push_back(pred);
	}

    }
}

template <typename Type>
void XPathFinding<Type>::_build_result_graph(const Graph<Type> & graph,
					     const GraphFunctor::EdgeWeighter<Type> & getCost,
					     const GraphTypes::node_id & sourceNode)
{
  std::map<GraphTypes::node_id, std::list<GraphTypes::node_id> >::const_iterator it;
  std::list<GraphTypes::node_id>::const_iterator pred;

  for(it = _best_predecessors.begin(); it != _best_predecessors.end(); ++it)
    {
      const GraphTypes::node_id & succ = it->first;
      const std::list<GraphTypes::node_id> & pred_list = it->second;

      for(pred = pred_list.begin(); pred != pred_list.end(); ++pred)
	{

	  if(succ != sourceNode)
	    {
	      _resultGraph.add_edge( *pred, succ, getCost(graph, *pred, succ) );
	    }

	}

    }
}

template <typename Type>
void XPathFinding<Type>::_dynamic_bellman(const Graph<Type> & graph,
					  const GraphFunctor::EdgeWeighter<Type> & getCost,
					  const GraphTypes::node_id & sourceNode,
					  const GraphTypes::Algorithms::OptimizationType & optimizationType)
{
  int i, size;

  _init(graph, sourceNode, optimizationType);

  size = graph.nodes_size();

  for(i=0; i < size; ++i)
    {
      _update_tables(graph, getCost, optimizationType);
    }

  _build_result_graph(graph, getCost, sourceNode);

}

template <typename Type>
void XPathFinding<Type>::Xbellman(const Graph<Type> & graph,
				  const GraphFunctor::EdgeWeighter<Type> & getCost,
				  const GraphTypes::node_id & sourceNode,
				  const GraphTypes::Algorithms::AlgorithmicClass & algoClass,
				  const GraphTypes::Algorithms::OptimizationType & optimizationType
				  ) throw(GraphException::InvalidOperation)
{

  if( !graph.is_directed() )
    {
      throw GraphException::InvalidOperation("This implemention of Bellman's algorithm has been designed for directed graphs", __LINE__, __FILE__, "XPathFinding<Type>::Xbellman(const Graph<Type>&,const GraphTypes::node_id&,const GraphTypes::Algorithms::AlgorithmicClass&,const GraphTypes::Algorithms::OptimizationType&)");
    }

  if(algoClass == GraphTypes::Algorithms::DYNAMIC)
    {
      return _dynamic_bellman(graph, getCost, sourceNode, optimizationType);
    }

  else
    {
      return _greedy_bellman(graph, getCost, sourceNode, optimizationType);
    }

}

template <typename Type>
void XPathFinding<Type>::Xbellman(const Graph<Type> & graph,
				  const GraphTypes::node_id & sourceNode,
				  const GraphTypes::Algorithms::AlgorithmicClass & algoClass,
				  const GraphTypes::Algorithms::OptimizationType & optimizationType
				  ) throw(GraphException::InvalidOperation)
{
  GraphFunctor::DefaultEdgeWeighter<Type> getCost;

  Xbellman(graph, getCost, sourceNode, algoClass, optimizationType);
}

template <typename Type>
void XPathFinding<Type>::dual_Xbellman(Graph<Type> & graph,
				       const GraphFunctor::EdgeWeighter<Type> & getCost,
				       const GraphTypes::node_id & targetNode,
				       const GraphTypes::Algorithms::AlgorithmicClass & algoClass,
				       const GraphTypes::Algorithms::OptimizationType & optimizationType
				       ) throw(GraphException::InvalidOperation)
{
  graph.reverse_edges();

  Xbellman(graph, getCost, targetNode, algoClass, optimizationType);

  graph.reverse_edges();
  _resultGraph.reverse_edges();
}

template <typename Type>
void XPathFinding<Type>::dual_Xbellman(Graph<Type> & graph,
				  const GraphTypes::node_id & sourceNode,
				  const GraphTypes::Algorithms::AlgorithmicClass & algoClass,
				  const GraphTypes::Algorithms::OptimizationType & optimizationType
				  ) throw(GraphException::InvalidOperation)
{
  GraphFunctor::DefaultEdgeWeighter<Type> getCost;

  dual_Xbellman(graph, getCost, sourceNode, algoClass, optimizationType);
}

template <typename Type>
std::list<GraphTypes::Path> XPathFinding<Type>::_paths_to(const GraphTypes::node_id & target)
{
  typename Graph<Type>::NodeIterator pred;
  std::list<GraphTypes::Path> foundPaths, until_pred;
  std::list<GraphTypes::Path>::iterator onePath;

  if( !_resultGraph.is_directed() )
    {
      throw GraphException::InvalidOperation("This method is designed for directed graphs.", __LINE__, __FILE__, "PathFinding<Type>::Xpaths_to(const Graph<>&,const GraphTypes::node_id&");
    }

  if( _resultGraph.has_node(target) )
    {

      pred = _resultGraph.predecessors_begin(target);

      while(pred != _resultGraph.predecessors_end(target) )
	{
	  until_pred = paths_to(*pred);

	  foundPaths.insert(foundPaths.begin(), until_pred.begin(), until_pred.end() );

	  ++pred;
	}

      if( foundPaths.size() > 0 )
	{

	  for(onePath = foundPaths.begin(); onePath != foundPaths.end(); ++onePath)
	    {
	      onePath->push_back(target);
	    }
	}

      else
	{

	  foundPaths.push_back( std::list<GraphTypes::node_id>() );

	  onePath = foundPaths.begin();
	  onePath->push_back(target);
	}

    }

  return foundPaths;
}

template <typename Type>
const std::list<GraphTypes::Path> & XPathFinding<Type>::paths_to(const GraphTypes::node_id & target) throw(GraphException::InvalidOperation)
{
  _foundPaths = _paths_to(target);

  return _foundPaths;
}

template <typename Type>
const std::list<GraphTypes::Path> & XPathFinding<Type>::Xbetween(const Graph<Type> & graph,
								 const GraphFunctor::EdgeWeighter<Type> & getCost,
								 const GraphTypes::node_id & source,
								 const GraphTypes::node_id & target,
								 const GraphTypes::Algorithms::SearchAlgorithm & algo
								 ) throw(GraphException::InvalidOperation)
{
  (algo == GraphTypes::Algorithms::DIJKSTRA) ? dijkstra(graph, getCost, source) : bellman(graph, getCost, source);
  
  return paths_to(target);
}

template <typename Type>
const std::list<GraphTypes::Path> & XPathFinding<Type>::Xbetween(const Graph<Type> & graph,
								 const GraphTypes::node_id & source,
								 const GraphTypes::node_id & target,
								 const GraphTypes::Algorithms::SearchAlgorithm & algo
								 ) throw(GraphException::InvalidOperation)
{
  GraphFunctor::DefaultEdgeWeighter<Type> getCost;

  return Xbetween(graph, source, target, algo);
}

template <typename Type>
const std::map<GraphTypes::node_id, GraphTypes::Cost> & XPathFinding<Type>::distances()const
{
  return _distance_from_source;
}

template <typename Type>
const std::map<GraphTypes::node_id, GraphTypes::node_id> & XPathFinding<Type>::predecessors()const
{
  return _best_predecessors;
}

template <typename Type>
const Graph<Type> & XPathFinding<Type>::resultGraph()const
{
  return _resultGraph;
}

template <typename Type>
const std::list<GraphTypes::Path> & XPathFinding<Type>::foundPaths()const
{
  return _foundPaths;
}
