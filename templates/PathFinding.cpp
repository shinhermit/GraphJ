template <typename Type>
PathFinding<Type>::PathFinding()
  :_resultGraph(GraphTypes::DIRECTED, GraphTypes::WEIGHTED, GraphTypes::NOCONTENT)
{}

template <typename Type>
void PathFinding<Type>::_reset()
{

  if(_distance_from_source.size() != 0)
    _distance_from_source.clear();

  if(_best_predecessor.size() != 0)
    _best_predecessor.clear();

  if(_resultGraph.nodes_size() != 0)
    _resultGraph = Graph<>(GraphTypes::DIRECTED, GraphTypes::WEIGHTED, GraphTypes::NOCONTENT);

  if(_foundPaths.size() != 0)
    _foundPaths.clear();
}

template <typename Type>
void PathFinding<Type>::_init(const Graph<Type> & graph,
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
      _best_predecessor[*it] = sourceNode;

      if(*it != sourceNode){
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
const GraphTypes::node_id & PathFinding<Type>::_closest(const std::list<GraphTypes::node_id> & candidates)
{
  GraphTypes::Cost d_closest, new_distance;
  std::list<GraphTypes::node_id>::const_iterator closest;
  std::list<GraphTypes::node_id>::const_iterator node;

  node = candidates.begin();

  closest = node;
  d_closest = _distance_from_source.find(*closest)->second;

  ++node;

  while( node != candidates.end() )
    {

      new_distance = _distance_from_source.find(*node)->second;

      if( new_distance < d_closest )
	{
	  d_closest = new_distance;

	  closest = node;
	}

      ++node;

    }

  return *closest;
}

template <typename Type>
void PathFinding<Type>::_update_tables(const Graph<Type> & graph,
				       const GraphFunctor::EdgeWeighter<Type> & getCost,
				       const GraphTypes::node_id & closest)
{
  typename Graph<Type>::NodeIterator succ;
  GraphTypes::Cost distance, new_distance;

  for(succ = graph.successors_begin(closest); succ != graph.successors_end(closest); ++succ)
    {

      if( !_resultGraph.has_node(*succ) )
	{
	  distance = _distance_from_source[*succ];
	  new_distance = _distance_from_source[closest] + getCost(graph, closest, *succ);

	  if(new_distance < distance)
	    {
	      _distance_from_source[*succ] = new_distance;

	      _best_predecessor[*succ] = closest;
	    }
	}

    }

}

template <typename Type>
void PathFinding<Type>::dijkstra(const Graph<Type> & graph,
				 const GraphFunctor::EdgeWeighter<Type> & getCost,
				 const GraphTypes::node_id & sourceNode
				 ) throw(GraphException::InvalidOperation)
{
  std::list<GraphTypes::node_id> candidates;
  GraphTypes::node_id closest, bestPred;
  bool allInfinite;

  if( !graph.is_directed() )
    {
      throw GraphException::InvalidOperation("This implemention of Dijkstra'algorithm has been designed for directed graphs", __LINE__, __FILE__, "PathFinding<Type>::dijkstra(const Graph<Type>&, const GraphTypes::node_id&)");
    }

  //initialisation des tables
  _init(graph, getCost, sourceNode, candidates);

  //début de l'algorithme
  allInfinite = false;
  while( _resultGraph.nodes_size() < graph.nodes_size() && !allInfinite )
    {
      closest = _closest(candidates);

      if(_distance_from_source[closest] == GraphTypes::Algorithms::POSITIVE_INFINITY)
	{
	  allInfinite = true;
	}

      else
	{
	  _update_tables(graph, getCost, closest);

	  bestPred = _best_predecessor[closest];
	  _resultGraph.add_edge( bestPred, closest, getCost(graph, bestPred, closest) );

	  candidates.remove(closest);
	}
    }
}

template <typename Type>
void PathFinding<Type>::dijkstra(const Graph<Type> & graph,
				 const GraphTypes::node_id & sourceNode
				 ) throw(GraphException::InvalidOperation)
{
  GraphFunctor::DefaultEdgeWeighter<Type> getCost;

  dijkstra(graph, getCost, sourceNode);
}

template <typename Type>
void PathFinding<Type>::dual_dijkstra(Graph<Type> & graph,
				      const GraphFunctor::EdgeWeighter<Type> & getCost,
				      const GraphTypes::node_id & targetNode
				      ) throw(GraphException::InvalidOperation)
{
  graph.reverse_edges();

  dijkstra(graph, getCost, targetNode);

  graph.reverse_edges();
  _resultGraph.reverse_edges();
}

template <typename Type>
void PathFinding<Type>::dual_dijkstra(Graph<Type> & graph,
				      const GraphTypes::node_id & targetNode
				      ) throw(GraphException::InvalidOperation)
{
  GraphFunctor::DefaultEdgeWeighter<Type> getCost;

  dual_dijstra(graph, getCost, targetNode);
}

template <typename Type>
void PathFinding<Type>::_init(const Graph<Type> & graph,
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
std::deque<GraphTypes::node_id> PathFinding<Type>::_coupe(const Graph<Type> & graph,
							  const std::list<GraphTypes::node_id> & candidates)
{
  std::list<GraphTypes::node_id>::const_iterator s;
  typename Graph<Type>::NodeIterator pred;
  std::deque<GraphTypes::node_id> relaxed;
  bool relaxable;

  s = candidates.begin();

  while( s != candidates.end() )
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
void PathFinding<Type>::_update_tables(const Graph<Type> & graph,
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
      GraphTypes::node_id & s_best_pred = _best_predecessor[*s];
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

		  s_best_pred = *pred;
		}

	    }
	}

    }
}

template <typename Type>
void PathFinding<Type>::_insert_waiting_nodes(const Graph<Type> & graph,
					      const GraphFunctor::EdgeWeighter<Type> & getCost,
					      std::deque<GraphTypes::node_id> & waiting_for_insertion)
{
  GraphTypes::node_id s, pred;

  while( waiting_for_insertion.size() > 0 )
    {
      s  = waiting_for_insertion.front();

      pred = _best_predecessor.find(s)->second;

      _resultGraph.add_edge( pred, s, getCost(graph, pred,s) );

      waiting_for_insertion.pop_front();
    }
}

template <typename Type>
void PathFinding<Type>::_remove_nodes(std::list<GraphTypes::node_id> & candidates,
				      const std::deque<GraphTypes::node_id> & waiting_for_insertion)
{
  std::deque<GraphTypes::node_id>::const_iterator node;

  for(node = waiting_for_insertion.begin(); node != waiting_for_insertion.end(); ++node)
    {
      candidates.remove(*node);
    }
}

template <typename Type>
void PathFinding<Type>::_greedy_bellman(const Graph<Type> & graph,
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
void PathFinding<Type>::_init(const Graph<Type> & graph,
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
void PathFinding<Type>::_update_tables(const Graph<Type> & graph,
				       const GraphFunctor::EdgeWeighter<Type> & getCost,
				       const GraphTypes::Algorithms::OptimizationType & optimizationType)
{
  typename Graph<Type>::EdgeIterator it;
  Edge edge;
  GraphTypes::node_id pred, succ;
  GraphTypes::Cost distance, new_distance;
  bool optimal;

  for(it = graph.edges_begin(); it != graph.edges_end(); ++it)
    {
      pred = it->source();
      succ = it->target();

      distance = _distance_from_source[succ];
      new_distance = _distance_from_source[pred] + getCost(graph, pred,succ);

      optimal = (optimizationType == GraphTypes::Algorithms::MINIMIZE) ? (new_distance < distance) : (new_distance > distance);

      if(optimal)
	{
	  _distance_from_source[succ] = new_distance;

	  _best_predecessor[succ] = pred;
	}

    }
}

template <typename Type>
void PathFinding<Type>::_build_result_graph(const Graph<Type> & graph,
					    const GraphFunctor::EdgeWeighter<Type> & getCost,
					    const GraphTypes::node_id & sourceNode)
{
  std::map<GraphTypes::node_id, GraphTypes::node_id>::const_iterator it;
  GraphTypes::node_id pred, succ;

  for(it = _best_predecessor.begin(); it != _best_predecessor.end(); ++it)
    {
      succ = it->first;
      pred = it->second;

      if(succ != sourceNode)
	{
	  _resultGraph.add_edge( pred, succ, getCost(graph, pred, succ) );
	}

    }
}

template <typename Type>
void PathFinding<Type>::_dynamic_bellman(const Graph<Type> & graph,
					 const GraphFunctor::EdgeWeighter<Type> & getCost,
					 const GraphTypes::node_id & sourceNode,
					 const GraphTypes::Algorithms::OptimizationType & optimizationType)
{
  std::map<GraphTypes::node_id, GraphTypes::Cost> _distance_from_source;
  std::map<GraphTypes::node_id, GraphTypes::node_id> _best_predecessor;
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
void PathFinding<Type>::bellman(const Graph<Type> & graph,
				const GraphFunctor::EdgeWeighter<Type> & getCost,
				const GraphTypes::node_id & sourceNode,
				const GraphTypes::Algorithms::AlgorithmicClass & algoClass,
				const GraphTypes::Algorithms::OptimizationType & optimizationType
				) throw(GraphException::InvalidOperation)
{

  if( !graph.is_directed() )
    {
      throw GraphException::InvalidOperation("This implemention of Bellman's algorithm has been designed for directed graphs", __LINE__, __FILE__, "PathFinding<Type>::bellman(const Graph<Type>&,const GraphTypes::node_id&,const GraphTypes::Algorithms::AlgorithmicClass&,const GraphTypes::Algorithms::OptimizationType&)");
    }

  if(algoClass == GraphTypes::Algorithms::DYNAMIC)
    _dynamic_bellman(graph, getCost, sourceNode, optimizationType);

  else
    _greedy_bellman(graph, getCost, sourceNode, optimizationType);
}

template <typename Type>
void PathFinding<Type>::bellman(const Graph<Type> & graph,
				const GraphTypes::node_id & sourceNode,
				const GraphTypes::Algorithms::AlgorithmicClass & algoClass,
				const GraphTypes::Algorithms::OptimizationType & optimizationType
				) throw(GraphException::InvalidOperation)
{
  GraphFunctor::DefaultEdgeWeighter<Type> getCost;

  bellman(graph, getCost, sourceNode, algoClass, optimizationType);
}

template <typename Type>
void PathFinding<Type>::dual_bellman(Graph<Type> & graph,
				     const GraphFunctor::EdgeWeighter<Type> & getCost,
				     const GraphTypes::node_id & targetNode,
				     const GraphTypes::Algorithms::AlgorithmicClass & algoClass,
				     const GraphTypes::Algorithms::OptimizationType & optimizationType
				     ) throw(GraphException::InvalidOperation)
{
  graph.reverse_edges();

  bellman(graph, getCost, targetNode, algoClass, optimizationType);

  graph.reverse_edges();
  _resultGraph.reverse_edges();
}

template <typename Type>
void PathFinding<Type>::dual_bellman(Graph<Type> & graph,
				     const GraphTypes::node_id & targetNode,
				     const GraphTypes::Algorithms::AlgorithmicClass & algoClass,
				     const GraphTypes::Algorithms::OptimizationType & optimizationType
				     ) throw(GraphException::InvalidOperation)
{
  GraphFunctor::DefaultEdgeWeighter<Type> getCost;

  dual_bellman(graph, getCost, targetNode, algoClass, optimizationType);
}

template <typename Type>
std::list<GraphTypes::Path> PathFinding<Type>::_paths_to(const GraphTypes::node_id & target)
{
  std::list<GraphTypes::Path> foundPaths, until_pred;
  Graph<>::NodeIterator pred;
  std::list<GraphTypes::Path>::iterator onePath;

  if( _resultGraph.has_node(target) )
    {

      pred = _resultGraph.predecessors_begin(target);

      while( pred != _resultGraph.predecessors_end(target) )
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
const std::list<GraphTypes::Path> & PathFinding<Type>::paths_to(const GraphTypes::node_id & target)
{
  _foundPaths = _paths_to(target);

  return _foundPaths;
}

template <typename Type>
const std::list<GraphTypes::Path> & PathFinding<Type>::between(const Graph<Type> & graph,
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
const std::list<GraphTypes::Path> & PathFinding<Type>::between(const Graph<Type> & graph,
							       const GraphTypes::node_id & source,
							       const GraphTypes::node_id & target,
							       const GraphTypes::Algorithms::SearchAlgorithm & algo
							       ) throw(GraphException::InvalidOperation)
{
  GraphFunctor::DefaultEdgeWeighter<Type> getCost;
  
  return between(graph, getCost, source, target, algo);
}

template <typename Type>
const std::map<GraphTypes::node_id, GraphTypes::Cost> & PathFinding<Type>::distances()const
{
  return _distance_from_source;
}

template <typename Type>
const std::map<GraphTypes::node_id, GraphTypes::node_id> & PathFinding<Type>::predecessors()const
{
  return _best_predecessor;
}

template <typename Type>
const Graph<Type> & PathFinding<Type>::resultGraph()const
{
  return _resultGraph;
}

template <typename Type>
const std::list<GraphTypes::Path> & PathFinding<Type>::foundPaths()const
{
  return _foundPaths;
}
