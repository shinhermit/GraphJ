template <typename Type>
XPathFinding<Type>::XPathFinding():_validity(GraphTypes::Algorithms::UNDEFINED){}

template <typename Type>
GraphTypes::Algorithms::ComputingValidity XPathFinding<Type>::_check_computing_validity(const Graph<Type> & graph,
											const std::map<GraphTypes::node_id,GraphTypes::Cost> & distance_from_source)
{
  typename Graph<Type>::EdgeIterator it;
  GraphTypes::Algorithms::ComputingValidity validity;

  validity = GraphTypes::Algorithms::VALID;

  for(it = graph.edges_begin(); it != graph.edges_end(); ++it)
    {

      const GraphTypes::node_id & pred = it->source();
      const GraphTypes::node_id & succ = it->target();

      const GraphTypes::Cost & min_distance = distance_from_source.find(succ)->second;
      const GraphTypes::Cost & distance_from_pred = distance_from_source.find(pred)->second + graph.getCost(pred,succ);

      if( min_distance > distance_from_pred )
	{
	  validity = GraphTypes::Algorithms::INVALID;
	}

    }

  return validity;
}

template <typename Type>
void XPathFinding<Type>::_init(const Graph<Type> & graph,
			       Graph<> & paths,
			       const GraphTypes::node_id & sourceNode,
			       std::list<GraphTypes::node_id> & candidates,
			       std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source,
			       std::map<GraphTypes::node_id, std::list<GraphTypes::node_id> > & best_predecessors)
{
  typename Graph<Type>::NodeIterator it;
  GraphTypes::Cost distance;

  distance_from_source[sourceNode] = 0;
  paths.add_node(sourceNode);

  for(it = graph.nodes_begin(); it != graph.nodes_end(); ++it)
    {
      best_predecessors[*it] = std::list<GraphTypes::node_id>();
      best_predecessors[*it].push_back(sourceNode);

      if(*it != sourceNode)
	{
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
std::list<GraphTypes::node_id> XPathFinding<Type>::_allClosest(const std::list<GraphTypes::node_id> & candidates,
							       const std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source)
{
  GraphTypes::node_id closest;
  GraphTypes::Cost d_closest, new_distance;
  std::list<GraphTypes::node_id>::const_iterator node;
  std::list<GraphTypes::node_id> allClosest;

  node = candidates.begin();

  closest = *node;
  d_closest = distance_from_source.find(closest)->second;
  allClosest.push_back(closest);

  ++node;
  while( node != candidates.end() )
    {

      new_distance = distance_from_source.find(*node)->second;

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
				    Graph<> & paths,
				    const std::map<GraphTypes::node_id, std::list<GraphTypes::node_id> > & best_predecessors,
				    const std::list<GraphTypes::node_id> allClosest)
{
  std::list<GraphTypes::node_id> best_preds;
  std::list<GraphTypes::node_id>::const_iterator closest, pred;

  for(closest = allClosest.begin(); closest != allClosest.end(); ++closest)
    {

      best_preds = best_predecessors.find(*closest)->second;

      for(pred = best_preds.begin(); pred != best_preds.end(); ++pred)
	{
	  paths.add_edge( *pred, *closest, graph.getCost(*pred, *closest) );
	}

    }
}

template <typename Type>
void XPathFinding<Type>::_remove_nodes(std::list<GraphTypes::node_id> & candidates,
				       const std::list<GraphTypes::node_id> allClosest)
{
  std::list<GraphTypes::node_id>::const_iterator closest;

  for(closest = allClosest.begin(); closest != allClosest.end(); ++closest)
    {
      candidates.remove(*closest);
    }
}

template <typename Type>
void XPathFinding<Type>::_update_tables(const Graph<Type> & graph,
					const Graph<> & paths,
					const std::list<GraphTypes::node_id> allClosest,
					std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source,
					std::map<GraphTypes::node_id, std::list<GraphTypes::node_id> > & best_predecessors)
{
  typename Graph<Type>::NodeIterator succ;
  std::list<GraphTypes::node_id>::const_iterator closest;
  GraphTypes::Cost distance, new_distance;

  for(closest = allClosest.begin(); closest != allClosest.end(); ++closest)
    {

      for(succ = graph.successors_begin(*closest); succ != graph.successors_end(*closest); ++succ)
	{

	  if( !paths.has_node(*succ) )
	    {
	      distance = distance_from_source[*succ];
	      new_distance = distance_from_source[*closest] + graph.getCost(*closest, *succ);

	      if(new_distance < distance)
		{
		  distance_from_source[*succ] = new_distance;

		  best_predecessors[*succ].clear();
		  best_predecessors[*succ].push_back(*closest);
		}

	      else if(new_distance == distance)
		{
		  best_predecessors[*succ].push_back(*closest);
		}

	    }
	}

    }
}

template <typename Type>
Graph<> XPathFinding<Type>::Xdijkstra(const Graph<Type> & graph,
				      const GraphTypes::node_id & sourceNode
				      ) throw(GraphException::InvalidOperation)
{
  std::map<GraphTypes::node_id, GraphTypes::Cost> distance_from_source;
  std::map<GraphTypes::node_id, std::list<GraphTypes::node_id> > best_predecessors;
  std::list<GraphTypes::node_id> candidates, allClosest;
  Graph<> paths(GraphTypes::DIRECTED, GraphTypes::WEIGHTED, GraphTypes::NOCONTENT);
  GraphTypes::node_id closest;
  bool allInfinite;


  if( !graph.is_directed() || !graph.is_weighted() )
    {
      throw GraphException::InvalidOperation("This implemention of Dijkstra'algorithm has been designed for directed weighted graphs", __LINE__, __FILE__, "XPathFinding<Type>::Xdijkstra(const Graph<Type>&, const GraphTypes::node_id&)");
    }

  //initialisation des tables
  _init(graph, paths, sourceNode, candidates, distance_from_source, best_predecessors);

  //début de l'algorithme
  allInfinite = false;

  while( paths.nodes_size() < graph.nodes_size() && !allInfinite )
    {
      allClosest = _allClosest(candidates, distance_from_source);

      closest = *allClosest.begin();

      if(distance_from_source[closest] == GraphTypes::Algorithms::POSITIVE_INFINITY)
	{
	  allInfinite = true;
	}

      else
	{
	  _update_tables(graph, paths, allClosest, distance_from_source, best_predecessors);

	  _add_edges(graph, paths, best_predecessors, allClosest);

	  _remove_nodes(candidates, allClosest);
	}

    }

  return paths;
}

template <typename Type>
void XPathFinding<Type>::_init(const Graph<Type> & graph,
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
std::deque<GraphTypes::node_id> XPathFinding<Type>::_coupe(const Graph<Type> & graph,
							   const Graph<> & paths,
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
void XPathFinding<Type>::_update_tables(const Graph<Type> & graph,
					const Graph<> & paths,
					const std::deque<GraphTypes::node_id> & waiting_for_insertion,
					std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source,
					std::map<GraphTypes::node_id, std::list<GraphTypes::node_id> > & best_predecessors,
					const GraphTypes::Algorithms::OptimizationType & optimizationType)
{
  typename Graph<Type>::NodeIterator pred;
  std::deque<GraphTypes::node_id>::const_iterator s;
  GraphTypes::Cost new_distance;
  bool optimal;

  for(s = waiting_for_insertion.begin(); s != waiting_for_insertion.end(); ++s)
    {

      std::list<GraphTypes::node_id> & s_best_preds = best_predecessors[*s];
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
					       Graph<> & paths,
					       std::deque<GraphTypes::node_id> & waiting_for_insertion,
					       const std::map<GraphTypes::node_id, std::list<GraphTypes::node_id> > & best_predecessors)
{
  std::list<GraphTypes::node_id>::const_iterator pred;
  GraphTypes::node_id s;

  while( waiting_for_insertion.size() > 0 )
    {

      s  = waiting_for_insertion.front();

      const std::list<GraphTypes::node_id> & predecessors = best_predecessors.find(s)->second;

      for(pred = predecessors.begin(); pred != predecessors.end(); ++pred)
	{
	  paths.add_edge( *pred, s, graph.getCost(*pred, s) );
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
Graph<> XPathFinding<Type>::_greedy_bellman(const Graph<Type> & graph,
					    const GraphTypes::node_id & sourceNode,
					    const GraphTypes::Algorithms::OptimizationType & optimizationType)
{
  Graph<> paths(graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT);
  std::map<GraphTypes::node_id, GraphTypes::Cost> distance_from_source;
  std::map<GraphTypes::node_id, std::list<GraphTypes::node_id> > best_predecessors;
  std::list<GraphTypes::node_id> candidates;
  std::deque<GraphTypes::node_id> waiting_for_insertion;

  _init(graph, paths, sourceNode, candidates, distance_from_source, optimizationType);

  waiting_for_insertion = _coupe(graph, paths, candidates);

  while( waiting_for_insertion.size() > 0 )
    {

      _update_tables(graph, paths, waiting_for_insertion, distance_from_source, best_predecessors, optimizationType);

      _remove_nodes(candidates, waiting_for_insertion);

      _insert_waiting_nodes(graph, paths, waiting_for_insertion, best_predecessors);

      waiting_for_insertion = _coupe(graph, paths, candidates);

    }

  return paths;
}

template <typename Type>
void XPathFinding<Type>::_init(const Graph<Type> & graph,
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
void XPathFinding<Type>::_update_tables(const Graph<Type> & graph,
					std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source,
					std::map<GraphTypes::node_id, std::list<GraphTypes::node_id> > & best_predecessors,
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

      GraphTypes::Cost & distance = distance_from_source[succ];
      std::list<GraphTypes::node_id> & pred_list = best_predecessors[succ];

      new_distance = distance_from_source[pred] + graph.getCost(pred,succ);


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
void XPathFinding<Type>::_build_paths_graph(const Graph<Type> & graph,
					    Graph<> & paths,
					    const GraphTypes::node_id & sourceNode,
					    const std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source,
					    const std::map<GraphTypes::node_id, std::list<GraphTypes::node_id> > & best_predecessors)
{
  std::map<GraphTypes::node_id, std::list<GraphTypes::node_id> >::const_iterator it;
  std::list<GraphTypes::node_id>::const_iterator pred;

  for(it = best_predecessors.begin(); it != best_predecessors.end(); ++it)
    {
      const GraphTypes::node_id & succ = it->first;
      const std::list<GraphTypes::node_id> & pred_list = it->second;

      for(pred = pred_list.begin(); pred != pred_list.end(); ++pred)
	{

	  if(succ != sourceNode)
	    {
	      paths.add_edge( *pred, succ, graph.getCost(*pred, succ) );
	    }

	}

    }
}

template <typename Type>
Graph<> XPathFinding<Type>::_dynamic_bellman(const Graph<Type> & graph,
					     const GraphTypes::node_id & sourceNode,
					     const GraphTypes::Algorithms::OptimizationType & optimizationType)
{
  Graph<> paths(graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT);
  std::map<GraphTypes::node_id, GraphTypes::Cost> distance_from_source;
  std::map<GraphTypes::node_id, std::list<GraphTypes::node_id> > best_predecessors;
  std::pair<Graph<Type>, bool> result;
  int i, size;

  _init(graph, paths, sourceNode, distance_from_source, optimizationType);

  size = graph.nodes_size();

  for(i=0; i < size; ++i)
    {
      _update_tables(graph, distance_from_source, best_predecessors, optimizationType);
    }

  _build_paths_graph(graph, paths, sourceNode, distance_from_source, best_predecessors);

  _validity = _check_computing_validity(graph, distance_from_source);

  return paths;
}

template <typename Type>
Graph<> XPathFinding<Type>::Xbellman(const Graph<Type> & graph,
				     const GraphTypes::node_id & sourceNode,
				     const GraphTypes::Algorithms::AlgorithmicClass & algoClass,
				     const GraphTypes::Algorithms::OptimizationType & optimizationType
				     ) throw(GraphException::InvalidOperation)
{

  if( !graph.is_directed() || !graph.is_weighted() )
    {
      throw GraphException::InvalidOperation("This implemention of Bellman's algorithm has been designed for directed weighted graphs", __LINE__, __FILE__, "XPathFinding<Type>::Xbellman(const Graph<Type>&,const GraphTypes::node_id&,const GraphTypes::Algorithms::AlgorithmicClass&,const GraphTypes::Algorithms::OptimizationType&)");
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
std::list<GraphTypes::Path> XPathFinding<Type>::paths_to(const Graph<> & allPaths,
							 const GraphTypes::node_id & target
							 ) throw(GraphException::InvalidOperation)
{
  typename Graph<Type>::NodeIterator pred;
  std::list<GraphTypes::Path> paths, until_pred;
  std::list<GraphTypes::Path>::iterator onePath;

  if( !allPaths.is_directed() )
    {
      throw GraphException::InvalidOperation("This method is designed for directed graphs.", __LINE__, __FILE__, "PathFinding<Type>::Xpaths_to(const Graph<>&,const GraphTypes::node_id&");
    }

  if( allPaths.has_node(target) )
    {

      pred = allPaths.predecessors_begin(target);

      while(pred != allPaths.predecessors_end(target) )
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
std::list<GraphTypes::Path> XPathFinding<Type>::Xbetween(const Graph<Type> & graph,
							 const GraphTypes::node_id & source,
							 const GraphTypes::node_id & target,
							 const GraphTypes::Algorithms::SearchAlgorithm & algo
							 ) throw(GraphException::InvalidOperation)
{

  Graph<> allPaths(graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT);

  allPaths = (algo == GraphTypes::Algorithms::DIJKSTRA) ? Xdijkstra(graph, source) : Xbellman(graph, source);

  return paths_to(allPaths, target);

}
