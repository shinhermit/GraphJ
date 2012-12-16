template <typename Type>
void PathFinding<Type>::_init(Graph<Type> & graph, Graph<> & paths, GraphTypes::node_id sourceNode, std::list<GraphTypes::node_id> & candidates, std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source, std::map<GraphTypes::node_id, GraphTypes::node_id> & best_predecessor)
{
  typename Graph<Type>::NodeIterator it;
  GraphTypes::Cost distance;

  distance_from_source[sourceNode] = 0;
  paths.add_node(sourceNode);

  for(it = graph.nodes_begin(); it != graph.nodes_end(); it++){
    best_predecessor[*it] = sourceNode;

    if(*it != sourceNode){
      candidates.push_back(*it);

      if( graph.has_edge(sourceNode, *it) ){
	distance = graph.getCost(sourceNode, *it);
      }
      else{
	distance = GraphTypes::INFINITY;
      }

      distance_from_source[*it] = distance;
    }

  }
}

template <typename Type>
GraphTypes::node_id PathFinding<Type>::_closest(std::list<GraphTypes::node_id> & candidates, std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source)
{
  GraphTypes::node_id closest;
  GraphTypes::Cost d_closest, new_distance;
  std::list<GraphTypes::node_id>::iterator node;

  node = candidates.begin();

  closest = *node;
  d_closest = distance_from_source[closest];

  node++;
  while( node != candidates.end() ){

    new_distance = distance_from_source[*node];
    if( new_distance < d_closest ){

      d_closest = new_distance;
      closest = *node;
    }

    node++;
  }

  return closest;
}

template <typename Type>
void PathFinding<Type>::_update_tables(Graph<Type> & graph, Graph<> & paths, GraphTypes::node_id closest, std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source, std::map<GraphTypes::node_id, GraphTypes::node_id> & best_predecessor)
{
  std::set<GraphTypes::node_id> successors;
  std::set<GraphTypes::node_id>::iterator succ;
  GraphTypes::Cost distance, new_distance;

  successors = graph.successors(closest);

  for(succ = successors.begin(); succ != successors.end(); succ++){

    if( !paths.has_node(*succ) ){
      distance = distance_from_source[*succ];
      new_distance = distance_from_source[closest] + graph.getCost(closest, *succ);

      if(new_distance < distance){
	distance_from_source[*succ] = new_distance;
	best_predecessor[*succ] = closest;
      }
    }

  }

}

template <typename Type>
Graph<> PathFinding<Type>::dijkstra(Graph<Type> & graph, GraphTypes::node_id sourceNode)
{
  std::map<GraphTypes::node_id, GraphTypes::Cost> distance_from_source;
  std::map<GraphTypes::node_id, GraphTypes::node_id> best_predecessor;
  std::list<GraphTypes::node_id> candidates;
  typename Graph<Type>::NodeIterator it;
  Graph<> paths(GraphTypes::DIRECTED, GraphTypes::WEIGHTED, GraphTypes::NOCONTENT);
  GraphTypes::node_id closest, bestPred;
  bool allInfinite;

  //initialisation des tables
  _init(graph, paths, sourceNode, candidates, distance_from_source, best_predecessor);

  //début de l'algorithme
  allInfinite = false;
  while( paths.nodes_size() < graph.nodes_size() && !allInfinite ){
    closest = _closest(candidates, distance_from_source);

    if(distance_from_source[closest] == GraphTypes::INFINITY){
      allInfinite = true;
    }
    else{
      _update_tables(graph, paths, closest, distance_from_source, best_predecessor);

      bestPred = best_predecessor[closest];
      paths.add_edge( bestPred, closest, graph.getCost(bestPred, closest) );

      candidates.remove(closest);
    }
  }

  return paths;
}

template <typename Type>
std::deque<GraphTypes::node_id> PathFinding<Type>::_relaxation(Graph<Type> & graph, Graph<> & paths, std::list<GraphTypes::node_id> & candidates)
{
  std::list<GraphTypes::node_id>::iterator s;
  std::deque<GraphTypes::node_id> relaxed;
  std::set<GraphTypes::node_id> predecessors;
  std::set<GraphTypes::node_id>::iterator pred;
  bool relaxable;

  s = candidates.begin();
  while(s != candidates.end()){

    predecessors = graph.predecessors(*s);

    relaxable = true;
    pred = predecessors.begin();
    while(pred != predecessors.end() && relaxable){
      if( !paths.has_node(*pred) ){
	relaxable = false;
      }
      pred++;
    }

    if(relaxable){
      relaxed.push_back(*s);
    }

    s++;
  }

  return relaxed;
}

template <typename Type>
void PathFinding<Type>::_update_tables(Graph<Type> & graph, Graph<> & paths, std::deque<GraphTypes::node_id> & waiting_for_insertion, std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source, std::map<GraphTypes::node_id, GraphTypes::node_id> & best_predecessor)
{
  std::set<GraphTypes::node_id> predecessors;
  std::set<GraphTypes::node_id>::iterator pred;
  std::deque<GraphTypes::node_id>::iterator s;
  GraphTypes::Cost new_distance;

  for(s = waiting_for_insertion.begin(); s != waiting_for_insertion.end(); s++){
    predecessors = graph.predecessors(*s);
    GraphTypes::node_id & s_best_pred = best_predecessor[*s];
    GraphTypes::Cost & s_distance = distance_from_source[*s];

    for(pred = predecessors.begin(); pred != predecessors.end(); pred++){

      if( paths.has_node(*pred) ){

	new_distance = distance_from_source[*pred] + graph.getCost(*pred, *s);
	if(new_distance < s_distance){

	  s_distance = new_distance;
	  s_best_pred = *pred;
	}
      }
    }

  }
}

template <typename Type>
void PathFinding<Type>::_insert_waiting_nodes(Graph<Type> & graph, Graph<> & paths, std::deque<GraphTypes::node_id> & waiting_for_insertion, std::map<GraphTypes::node_id, GraphTypes::node_id> & best_predecessor)
{
  GraphTypes::node_id s, pred;

  while( waiting_for_insertion.size() > 0 ){
    s  = waiting_for_insertion.front();
    pred = best_predecessor[s];
    paths.add_edge( pred, s, graph.getCost(pred,s) );
    waiting_for_insertion.pop_front();
  }
}

template <typename Type>
void XPathFinding<Type>::_remove_nodes(std::list<GraphTypes::node_id> & candidates, std::deque<GraphTypes::node_id> & waiting_for_insertion)
{
  std::deque<GraphTypes::node_id>::iterator node;

  for(node = waiting_for_insertion.begin(); node != waiting_for_insertion.end(); node++){
    candidates.remove(*node);
  }
}

template <typename Type>
Graph<> PathFinding<Type>::bellman(Graph<Type> & graph, GraphTypes::node_id sourceNode)
{
  Graph<> paths(graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT);
  typename Graph<Type>::NodeIterator it;
  std::map<GraphTypes::node_id, GraphTypes::Cost> distance_from_source;
  std::map<GraphTypes::node_id, GraphTypes::node_id> best_predecessor;
  std::list<GraphTypes::node_id> candidates;
  std::deque<GraphTypes::node_id> waiting_for_insertion;

  //initialisations
  distance_from_source[sourceNode] = 0;
  paths.add_node(sourceNode);

  for(it = graph.nodes_begin(); it != graph.nodes_end(); it++){

    if(*it != sourceNode){

      distance_from_source[*it] = GraphTypes::INFINITY;
      candidates.push_back(*it);
    }
  }

  //début de l'algorithme
  waiting_for_insertion = _relaxation(graph, paths, candidates);
  while( waiting_for_insertion.size() > 0 ){
    _update_tables(graph, paths, waiting_for_insertion, distance_from_source, best_predecessor);
    _remove_nodes(candidates, waiting_for_insertion);
    _insert_waiting_nodes(graph, paths, waiting_for_insertion, best_predecessor);
    waiting_for_insertion = _relaxation(graph, paths, candidates);
  }

  return paths;
}

template <typename Type>
Graph<> PathFinding<Type>::between(Graph<Type> & graph, GraphTypes::node_id source, GraphTypes::node_id target, GraphTypes::SearchAlgorithm algo)
{
  Traverse<> traverse;
  PathBuilderVisitor<> pathBuilder;
  std::set<GraphTypes::node_id> marker;
  Graph<> paths(graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT);

  paths = (algo == GraphTypes::DIJKSTRA) ? dijkstra(graph, source) : bellman(graph, source);

  traverse.reverse_breadth_once(paths, target, pathBuilder, marker);

  return pathBuilder.path();
}
