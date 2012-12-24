template <typename Type>
PathFinding<Type>::PathFinding():_validity(GraphTypes::UNDEFINED){}

template <typename Type>
GraphTypes::ComputingValidity PathFinding<Type>::_check_computing_validity(Graph<Type> & graph, std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source)
{
  typename Graph<Type>::EdgeIterator it;
  Edge edge(0,0);
  GraphTypes::node_id pred, succ;
  GraphTypes::ComputingValidity validity;

  validity = GraphTypes::VALID;
  it = graph.edges_begin();
  while( it != graph.edges_end() && validity == GraphTypes::VALID ){
    edge = *it;
    pred = edge.source();
    succ = edge.target();

    if( distance_from_source[succ] > distance_from_source[pred] + graph.getCost(pred,succ) ){
      validity = GraphTypes::INVALID;
    }

    it++;
  }

  return validity;
}

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

  _validity = _check_computing_validity(graph, distance_from_source);

  return paths;
}

template <typename Type>
void PathFinding<Type>::_init(Graph<Type> & graph, Graph<> & paths, GraphTypes::node_id sourceNode, std::list<GraphTypes::node_id> & candidates, std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source)
{
  typename Graph<Type>::NodeIterator it;

  distance_from_source[sourceNode] = 0;
  paths.add_node(sourceNode);

  for(it = graph.nodes_begin(); it != graph.nodes_end(); it++){

    if(*it != sourceNode){

      distance_from_source[*it] = GraphTypes::INFINITY;
      candidates.push_back(*it);
    }
  }
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
void PathFinding<Type>::_remove_nodes(std::list<GraphTypes::node_id> & candidates, std::deque<GraphTypes::node_id> & waiting_for_insertion)
{
  std::deque<GraphTypes::node_id>::iterator node;

  for(node = waiting_for_insertion.begin(); node != waiting_for_insertion.end(); node++){
    candidates.remove(*node);
  }
}

template <typename Type>
Graph<> PathFinding<Type>::_greedy_bellman(Graph<Type> & graph, GraphTypes::node_id sourceNode)
{
  Graph<> paths(graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT);
  std::map<GraphTypes::node_id, GraphTypes::Cost> distance_from_source;
  std::map<GraphTypes::node_id, GraphTypes::node_id> best_predecessor;
  std::list<GraphTypes::node_id> candidates;
  std::deque<GraphTypes::node_id> waiting_for_insertion;

  _init(graph, paths, sourceNode, candidates, distance_from_source);

  waiting_for_insertion = _relaxation(graph, paths, candidates);
  while( waiting_for_insertion.size() > 0 ){
    _update_tables(graph, paths, waiting_for_insertion, distance_from_source, best_predecessor);
    _remove_nodes(candidates, waiting_for_insertion);
    _insert_waiting_nodes(graph, paths, waiting_for_insertion, best_predecessor);
    waiting_for_insertion = _relaxation(graph, paths, candidates);
  }

  _validity = _check_computing_validity(graph, distance_from_source);

  return paths;
}

template <typename Type>
void PathFinding<Type>::_init(Graph<Type> & graph, Graph<> & paths, GraphTypes::node_id sourceNode, std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source)
{
  typename Graph<Type>::NodeIterator node;

  distance_from_source[sourceNode] = 0;
  paths.add_node(sourceNode);

  for(node = graph.nodes_begin(); node != graph.nodes_end(); node++){

    if(*node != sourceNode){

      distance_from_source[*node] = GraphTypes::INFINITY;
    }
  }
}

template <typename Type>
void PathFinding<Type>::_update_tables(Graph<Type> & graph, std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source, std::map<GraphTypes::node_id, GraphTypes::node_id> & best_predecessor)
{
  typename Graph<Type>::EdgeIterator it;
  Edge edge(0,0);
  GraphTypes::node_id pred, succ;
  GraphTypes::Cost distance, new_distance;

  for(it = graph.edges_begin(); it != graph.edges_end(); it++){
    edge = *it;
    pred = edge.source();
    succ = edge.target();
    distance = distance_from_source[succ];
    new_distance = distance_from_source[pred] + graph.getCost(pred,succ);

    if(new_distance < distance){
      distance_from_source[succ] = new_distance;
      best_predecessor[succ] = pred;
    }

  }
}

template <typename Type>
void PathFinding<Type>::_build_paths_graph(Graph<Type> & graph, Graph<> & paths, std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source, std::map<GraphTypes::node_id, GraphTypes::node_id> & best_predecessor)
{
  std::map<GraphTypes::node_id, GraphTypes::node_id>::iterator it;
  GraphTypes::node_id pred, succ;

  for(it = best_predecessor.begin(); it != best_predecessor.end(); it++){
    succ = it->first;
    pred = it->second;
    paths.add_edge( pred, succ, graph.getCost(pred, succ) );
  }
}

template <typename Type>
Graph<> PathFinding<Type>::_dynamic_bellman(Graph<Type> & graph, GraphTypes::node_id sourceNode)
{
  Graph<> paths(graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT);
  std::map<GraphTypes::node_id, GraphTypes::Cost> distance_from_source;
  std::map<GraphTypes::node_id, GraphTypes::node_id> best_predecessor;
  std::pair<Graph<Type>, bool> result;
  int i, size;

  _init(graph, paths, sourceNode, distance_from_source);

  size = graph.nodes_size();
  for(i=0; i < size; i++){
    _update_tables(graph, distance_from_source, best_predecessor);
  }

  _build_paths_graph(graph, paths, distance_from_source, best_predecessor);

  _validity = _check_computing_validity(graph, distance_from_source);

  return paths;
}

template <typename Type>
Graph<> PathFinding<Type>::bellman(Graph<Type> & graph, GraphTypes::node_id sourceNode, GraphTypes::AlgorithmicClass algoClass)
{
  if(algoClass == GraphTypes::DYNAMIC){
    return _dynamic_bellman(graph, sourceNode);
  }
  else{
    return _greedy_bellman(graph, sourceNode);
  }
}

template <typename Type>
std::list<GraphTypes::Path> PathFinding<Type>::paths_to(Graph<> & allPaths, GraphTypes::node_id target) throw(std::logic_error)
{
  std::list<GraphTypes::Path> paths, until_pred;
  std::set<GraphTypes::node_id> predecessors;
  std::set<GraphTypes::node_id>::iterator pred;
  std::list<GraphTypes::Path>::iterator onePath;

  if( !allPaths.is_directed() ){
    throw std::logic_error("Unsafe usage of XPathFinding<Type>::paths_to(Graph<>&, GraphTypes::node_id) with an undirected graph. Maybe you should convert the original graph before.");
  }

  predecessors = allPaths.predecessors(target);
  if( predecessors.size() > 0 ){

    for(pred = predecessors.begin(); pred != predecessors.end(); pred++){
      until_pred = paths_to(allPaths, *pred);
      paths.insert(paths.begin(), until_pred.begin(), until_pred.end() );
    }
  }

  if( paths.size() > 0 ){

    for(onePath = paths.begin(); onePath != paths.end(); onePath++){
      onePath->push_back(target);
    }
  }
  else{

    paths.push_back( std::list<GraphTypes::node_id>() );
    onePath = paths.begin();
    onePath->push_back(target);
  }

  return paths;
}

template <typename Type>
std::list<GraphTypes::Path> PathFinding<Type>::between(Graph<Type> & graph, GraphTypes::node_id source, GraphTypes::node_id target, GraphTypes::SearchAlgorithm algo) throw(std::logic_error)
{
  std::list<GraphTypes::Path> to_target;
  Graph<> allPaths(graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT);

  allPaths = (algo == GraphTypes::DIJKSTRA) ? dijkstra(graph, source) : bellman(graph, source);

  to_target = paths_to(allPaths, target);

  return to_target;
}

template <typename Type>
GraphTypes::ComputingValidity PathFinding<Type>::validity()const
{
  return _validity;
}
