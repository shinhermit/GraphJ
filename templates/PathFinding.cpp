template <typename Type>
PathFinding<Type>::PathFinding():_validity(GraphTypes::Algorithms::UNDEFINED){}

template <typename Type>
GraphTypes::Algorithms::ComputingValidity PathFinding<Type>::_check_computing_validity(const Graph<Type> & graph,
										       const std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source)
{
  typename Graph<Type>::EdgeIterator it;
  GraphTypes::Algorithms::ComputingValidity validity;

  validity = GraphTypes::Algorithms::VALID;

  it = graph.edges_begin();

  while( it != graph.edges_end() && validity == GraphTypes::Algorithms::VALID )
    {
      const GraphTypes::node_id & pred = it->source();
      const GraphTypes::node_id & succ = it->target();

      const GraphTypes::Cost & min_distance = distance_from_source.find(succ)->second;
      const GraphTypes::Cost & distance_from_pred = distance_from_source.find(pred)->second + graph.getCost(pred,succ);

      if( min_distance > distance_from_pred )
	{
	  validity = GraphTypes::Algorithms::INVALID;
	}

      ++it;
    }

  return validity;
}

template <typename Type>
void PathFinding<Type>::_init(const Graph<Type> & graph,
			      Graph<> & paths,
			      const GraphTypes::node_id & sourceNode,
			      std::list<GraphTypes::node_id> & candidates,
			      std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source,
			      std::map<GraphTypes::node_id, GraphTypes::node_id> & best_predecessor)
{
  typename Graph<Type>::NodeIterator it;
  GraphTypes::Cost distance;

  distance_from_source[sourceNode] = 0;
  paths.add_node(sourceNode);

  for(it = graph.nodes_begin(); it != graph.nodes_end(); ++it)
    {
      best_predecessor[*it] = sourceNode;

      if(*it != sourceNode){
	candidates.push_back(*it);

	if( graph.has_edge(sourceNode, *it) )
	  {
	    distance = graph.getCost(sourceNode, *it);
	  }

	else
	  {
	    distance = GraphTypes::Algorithms::POSITIVE_INFINITY;
	  }

	distance_from_source[*it] = distance;
      }

    }
}

template <typename Type>
const GraphTypes::node_id & PathFinding<Type>::_closest(const std::list<GraphTypes::node_id> & candidates,
							const std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source)
{
  GraphTypes::Cost d_closest, new_distance;
  std::list<GraphTypes::node_id>::const_iterator closest;
  std::list<GraphTypes::node_id>::const_iterator node;

  node = candidates.begin();

  closest = node;
  d_closest = distance_from_source.find(*closest)->second;

  ++node;

  while( node != candidates.end() )
    {

      new_distance = distance_from_source.find(*node)->second;

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
				       const Graph<> & paths,
				       const GraphTypes::node_id & closest,
				       std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source,
				       std::map<GraphTypes::node_id, GraphTypes::node_id> & best_predecessor)
{
  typename Graph<Type>::NodeIterator succ;
  GraphTypes::Cost distance, new_distance;

  for(succ = graph.successors_begin(closest); succ != graph.successors_end(closest); ++succ)
    {

      if( !paths.has_node(*succ) )
	{
	  distance = distance_from_source[*succ];
	  new_distance = distance_from_source[closest] + graph.getCost(closest, *succ);

	  if(new_distance < distance)
	    {
	      distance_from_source[*succ] = new_distance;

	      best_predecessor[*succ] = closest;
	    }
	}

    }

}

template <typename Type>
Graph<> PathFinding<Type>::dijkstra(const Graph<Type> & graph,
				    const GraphTypes::node_id & sourceNode
				    ) throw(GraphException::InvalidOperation)
{
  std::map<GraphTypes::node_id, GraphTypes::Cost> distance_from_source;
  std::map<GraphTypes::node_id, GraphTypes::node_id> best_predecessor;
  std::list<GraphTypes::node_id> candidates;
  Graph<> paths(GraphTypes::DIRECTED, GraphTypes::WEIGHTED, GraphTypes::NOCONTENT);
  GraphTypes::node_id closest, bestPred;
  bool allInfinite;

  if( !graph.is_directed() || !graph.is_weighted() )
    {
      throw GraphException::InvalidOperation("This implemention of Dijkstra'algorithm has been designed for directed weighted graphs", __LINE__, __FILE__, "PathFinding<Type>::dijkstra(const Graph<Type>&, const GraphTypes::node_id&)");
    }

  //initialisation des tables
  _init(graph, paths, sourceNode, candidates, distance_from_source, best_predecessor);

  //début de l'algorithme
  allInfinite = false;
  while( paths.nodes_size() < graph.nodes_size() && !allInfinite )
    {
      closest = _closest(candidates, distance_from_source);

      if(distance_from_source[closest] == GraphTypes::Algorithms::POSITIVE_INFINITY)
	{
	  allInfinite = true;
	}

      else
	{
	  _update_tables(graph, paths, closest, distance_from_source, best_predecessor);

	  bestPred = best_predecessor[closest];
	  paths.add_edge( bestPred, closest, graph.getCost(bestPred, closest) );

	  candidates.remove(closest);
	}
    }

  _validity = _check_computing_validity(graph, distance_from_source);

  return paths;
}

template <typename Type>
void PathFinding<Type>::_init(const Graph<Type> & graph,
			      Graph<> & paths,
			      const GraphTypes::node_id & sourceNode,
			      std::list<GraphTypes::node_id> & candidates,
			      std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source,
			      const GraphTypes::Algorithms::OptimizationType & optimizationType)
{
  typename Graph<Type>::NodeIterator it;
  GraphTypes::Cost infinite;

  infinite = (optimizationType == GraphTypes::Algorithms::MINIMIZE) ? GraphTypes::Algorithms::POSITIVE_INFINITY : GraphTypes::Algorithms::NEGATIVE_INFINITY;

  distance_from_source[sourceNode] = 0;
  paths.add_node(sourceNode);

  for(it = graph.nodes_begin(); it != graph.nodes_end(); ++it)
    {

      if(*it != sourceNode)
	{
	  distance_from_source[*it] = infinite;

	  candidates.push_back(*it);
	}
    }
}

template <typename Type>
std::deque<GraphTypes::node_id> PathFinding<Type>::_coupe(const Graph<Type> & graph,
							  const Graph<> & paths,
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

	      if( !paths.has_node(*pred) )
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
				       const Graph<> & paths,
				       const std::deque<GraphTypes::node_id> & waiting_for_insertion,
				       std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source,
				       std::map<GraphTypes::node_id, GraphTypes::node_id> & best_predecessor,
				       const GraphTypes::Algorithms::OptimizationType & optimizationType)
{
  typename Graph<Type>::NodeIterator pred;
  std::deque<GraphTypes::node_id>::const_iterator s;
  GraphTypes::Cost new_distance;
  bool optimal;

  for(s = waiting_for_insertion.begin(); s != waiting_for_insertion.end(); ++s)
    {
      GraphTypes::node_id & s_best_pred = best_predecessor[*s];
      GraphTypes::Cost & s_distance = distance_from_source[*s];

      for(pred = graph.predecessors_begin(*s); pred != graph.predecessors_end(*s); ++pred)
	{

	  if( paths.has_node(*pred) )
	    {

	      new_distance = distance_from_source[*pred] + graph.getCost(*pred, *s);

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
					      Graph<> & paths,
					      std::deque<GraphTypes::node_id> & waiting_for_insertion,
					      const std::map<GraphTypes::node_id, GraphTypes::node_id> & best_predecessor)
{
  GraphTypes::node_id s, pred;

  while( waiting_for_insertion.size() > 0 )
    {
      s  = waiting_for_insertion.front();

      pred = best_predecessor.find(s)->second;

      paths.add_edge( pred, s, graph.getCost(pred,s) );

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
Graph<> PathFinding<Type>::_greedy_bellman(const Graph<Type> & graph,
					   const GraphTypes::node_id & sourceNode,
					   const GraphTypes::Algorithms::OptimizationType & optimizationType)
{
  Graph<> paths(GraphTypes::DIRECTED, GraphTypes::WEIGHTED, GraphTypes::NOCONTENT);
  std::map<GraphTypes::node_id, GraphTypes::Cost> distance_from_source;
  std::map<GraphTypes::node_id, GraphTypes::node_id> best_predecessor;
  std::list<GraphTypes::node_id> candidates;
  std::deque<GraphTypes::node_id> waiting_for_insertion;

  _init(graph, paths, sourceNode, candidates, distance_from_source, optimizationType);

  waiting_for_insertion = _coupe(graph, paths, candidates);

  while( waiting_for_insertion.size() > 0 )
    {
      _update_tables(graph, paths, waiting_for_insertion, distance_from_source, best_predecessor, optimizationType);

      _remove_nodes(candidates, waiting_for_insertion);

      _insert_waiting_nodes(graph, paths, waiting_for_insertion, best_predecessor);

      waiting_for_insertion = _coupe(graph, paths, candidates);
    }

  _validity = _check_computing_validity(graph, distance_from_source);

  return paths;
}

template <typename Type>
void PathFinding<Type>::_init(const Graph<Type> & graph,
			      Graph<> & paths,
			      const GraphTypes::node_id & sourceNode,
			      std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source,
			      const GraphTypes::Algorithms::OptimizationType & optimizationType)
{
  typename Graph<Type>::NodeIterator node;
  GraphTypes::Cost infinite;

  infinite = (optimizationType == GraphTypes::Algorithms::MINIMIZE) ? GraphTypes::Algorithms::POSITIVE_INFINITY : GraphTypes::Algorithms::NEGATIVE_INFINITY;

  distance_from_source[sourceNode] = 0;
  paths.add_node(sourceNode);

  for(node = graph.nodes_begin(); node != graph.nodes_end(); ++node)
    {

      if(*node != sourceNode)
	{
	  distance_from_source[*node] = infinite;
	}

    }
}

template <typename Type>
void PathFinding<Type>::_update_tables(const Graph<Type> & graph,
				       std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source,
				       std::map<GraphTypes::node_id, GraphTypes::node_id> & best_predecessor,
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

      distance = distance_from_source[succ];
      new_distance = distance_from_source[pred] + graph.getCost(pred,succ);

      optimal = (optimizationType == GraphTypes::Algorithms::MINIMIZE) ? (new_distance < distance) : (new_distance > distance);

      if(optimal)
	{
	  distance_from_source[succ] = new_distance;

	  best_predecessor[succ] = pred;
	}

    }
}

template <typename Type>
void PathFinding<Type>::_build_paths_graph(const Graph<Type> & graph,
					   Graph<> & paths,
					   const GraphTypes::node_id & sourceNode,
					   const std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source,
					   const std::map<GraphTypes::node_id, GraphTypes::node_id> & best_predecessor)
{
  std::map<GraphTypes::node_id, GraphTypes::node_id>::const_iterator it;
  GraphTypes::node_id pred, succ;

  for(it = best_predecessor.begin(); it != best_predecessor.end(); ++it)
    {
      succ = it->first;
      pred = it->second;

      if(succ != sourceNode)
	{
	  paths.add_edge( pred, succ, graph.getCost(pred, succ) );
	}

    }
}

template <typename Type>
Graph<> PathFinding<Type>::_dynamic_bellman(const Graph<Type> & graph,
					    const GraphTypes::node_id & sourceNode,
					    const GraphTypes::Algorithms::OptimizationType & optimizationType)
{
  Graph<> paths(graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT);
  std::map<GraphTypes::node_id, GraphTypes::Cost> distance_from_source;
  std::map<GraphTypes::node_id, GraphTypes::node_id> best_predecessor;
  int i, size;

  _init(graph, paths, sourceNode, distance_from_source, optimizationType);

  size = graph.nodes_size();

  for(i=0; i < size; ++i)
    {
      _update_tables(graph, distance_from_source, best_predecessor, optimizationType);
    }

  _build_paths_graph(graph, paths, sourceNode, distance_from_source, best_predecessor);

  _validity = _check_computing_validity(graph, distance_from_source);

  return paths;
}

template <typename Type>
Graph<> PathFinding<Type>::bellman(const Graph<Type> & graph,
				   const GraphTypes::node_id & sourceNode,
				   const GraphTypes::Algorithms::AlgorithmicClass & algoClass,
				   const GraphTypes::Algorithms::OptimizationType & optimizationType
				   ) throw(GraphException::InvalidOperation)
{

  if( !graph.is_directed() || !graph.is_weighted() )
    {
      throw GraphException::InvalidOperation("This implemention of Bellman's algorithm has been designed for directed weighted graphs", __LINE__, __FILE__, "PathFinding<Type>::bellman(const Graph<Type>&,const GraphTypes::node_id&,const GraphTypes::Algorithms::AlgorithmicClass&,const GraphTypes::Algorithms::OptimizationType&)");
    }

  if(algoClass == GraphTypes::Algorithms::DYNAMIC)
    {
      return _dynamic_bellman(graph, sourceNode, optimizationType);
    }

  else
    {
      return _greedy_bellman(graph, sourceNode, optimizationType);
    }
}

template <typename Type>
std::list<GraphTypes::Path> PathFinding<Type>::paths_to(const Graph<> & allPaths,
							const GraphTypes::node_id & target
							) throw(GraphException::InvalidOperation)
{
  std::list<GraphTypes::Path> paths, until_pred;
  Graph<>::NodeIterator pred;
  std::list<GraphTypes::Path>::iterator onePath;

  if( !allPaths.is_directed() )
    {
      throw GraphException::InvalidOperation("This method is designed for directed graphs.", __LINE__, __FILE__, "PathFinding<Type>::paths_to(const Graph<>&,const GraphTypes::node_id&");
    }

  if( allPaths.has_node(target) )
    {

      pred = allPaths.predecessors_begin(target);

      while( pred != allPaths.predecessors_end(target) )
	{
	  until_pred = paths_to(allPaths, *pred);

	  paths.insert(paths.begin(), until_pred.begin(), until_pred.end() );

	  ++pred;
	}

      if( paths.size() > 0 )
	{

	  for(onePath = paths.begin(); onePath != paths.end(); ++onePath)
	    {
	      onePath->push_back(target);
	    }

	}

      else
	{

	  paths.push_back( std::list<GraphTypes::node_id>() );

	  onePath = paths.begin();
	  onePath->push_back(target);

	}

    }

  return paths;
}

template <typename Type>
std::list<GraphTypes::Path> PathFinding<Type>::between(const Graph<Type> & graph,
						       const GraphTypes::node_id & source,
						       const GraphTypes::node_id & target,
						       const GraphTypes::Algorithms::SearchAlgorithm & algo
						       ) throw(GraphException::InvalidOperation)
{
  Graph<> allPaths(GraphTypes::DIRECTED, graph.edgeState(), GraphTypes::NOCONTENT);

  allPaths = (algo == GraphTypes::Algorithms::DIJKSTRA) ? dijkstra(graph, source) : bellman(graph, source);
  
  return paths_to(allPaths, target);
}

template <typename Type>
const GraphTypes::Algorithms::ComputingValidity & PathFinding<Type>::validity()const
{
  return _validity;
}
