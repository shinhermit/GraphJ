template <typename Type>
XPathFinding<Type>::XPathFinding():_validity(GraphTypes::UNDEFINED){}

template <typename Type>
GraphTypes::ComputingValidity XPathFinding<Type>::_check_computing_validity(Graph<Type> & graph, std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source)
{
  typename Graph<Type>::EdgeIterator it;
  Edge edge(0,0);
  GraphTypes::node_id pred, succ;
  GraphTypes::ComputingValidity validity;

  validity = GraphTypes::VALID;
  for(it = graph.edges_begin(); it != graph.edges_end(); it++){
    edge = *it;
    pred = edge.source();
    succ = edge.target();
    if( distance_from_source[succ] > distance_from_source[pred] + graph.getCost(pred,succ) ){
      validity = GraphTypes::INVALID;
    }
  }

  return validity;
}

template <typename Type>
void XPathFinding<Type>::_init(Graph<Type> & graph, Graph<> & paths, GraphTypes::node_id sourceNode, std::list<GraphTypes::node_id> & candidates, std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source, std::map<GraphTypes::node_id, std::list<GraphTypes::node_id> > & best_predecessors)
{
  typename Graph<Type>::NodeIterator it;
  GraphTypes::Cost distance;

  distance_from_source[sourceNode] = 0;
  paths.add_node(sourceNode);

  for(it = graph.nodes_begin(); it != graph.nodes_end(); it++){
    best_predecessors[*it] = std::list<GraphTypes::node_id>();
    best_predecessors[*it].push_back(sourceNode);

    if(*it != sourceNode){
      candidates.push_back(*it);

      if( graph.has_edge(sourceNode, *it) ){
	distance = graph.getCost(sourceNode, *it);
      }
      else{
	distance = GraphTypes::POSITIVE_INFINITY;
      }

      distance_from_source[*it] = distance;
    }

  }
}

template <typename Type>
std::list<GraphTypes::node_id> XPathFinding<Type>::_allClosest(std::list<GraphTypes::node_id> & candidates, std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source)
{
  GraphTypes::node_id closest;
  GraphTypes::Cost d_closest, new_distance;
  std::list<GraphTypes::node_id>::iterator node;
  std::list<GraphTypes::node_id> allClosest;

  node = candidates.begin();

  closest = *node;
  d_closest = distance_from_source[closest];
  allClosest.push_back(closest);

  node++;
  while( node != candidates.end() ){
    new_distance = distance_from_source[*node];
    if( new_distance < d_closest ){
      d_closest = new_distance;
      closest = *node;
      allClosest.clear();
      allClosest.push_back(closest);
    }
    else if(new_distance == d_closest){
      allClosest.push_back(*node);
    }
    node++;
  }

  return allClosest;
}

template <typename Type>
void XPathFinding<Type>::_add_edges(Graph<Type> & graph, Graph<> & paths, std::map<GraphTypes::node_id, std::list<GraphTypes::node_id> > & best_predecessors, std::list<GraphTypes::node_id> allClosest)
{
  std::list<GraphTypes::node_id> best_preds;
  std::list<GraphTypes::node_id>::iterator closest, pred;

  for(closest = allClosest.begin(); closest != allClosest.end(); closest++){
    best_preds = best_predecessors[*closest];

    for(pred = best_preds.begin(); pred != best_preds.end(); pred++){
      paths.add_edge( *pred, *closest, graph.getCost(*pred, *closest) );
    }
  }
}

template <typename Type>
void XPathFinding<Type>::_remove_nodes(std::list<GraphTypes::node_id> & candidates, std::list<GraphTypes::node_id> allClosest)
{
  std::list<GraphTypes::node_id>::iterator closest;

  for(closest = allClosest.begin(); closest != allClosest.end(); closest++){
    candidates.remove(*closest);
  }
}

template <typename Type>
void XPathFinding<Type>::_update_tables(Graph<Type> & graph, Graph<> & paths, std::list<GraphTypes::node_id> allClosest, std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source, std::map<GraphTypes::node_id, std::list<GraphTypes::node_id> > & best_predecessors)
{
  std::set<GraphTypes::node_id> successors;
  std::set<GraphTypes::node_id>::iterator succ;
  std::list<GraphTypes::node_id>::iterator closest;
  GraphTypes::Cost distance, new_distance;

  for(closest = allClosest.begin(); closest != allClosest.end(); closest++){
    successors = graph.successors(*closest);

    for(succ = successors.begin(); succ != successors.end(); succ++){

      if( !paths.has_node(*succ) ){
	distance = distance_from_source[*succ];
	new_distance = distance_from_source[*closest] + graph.getCost(*closest, *succ);

	if(new_distance < distance){
	  distance_from_source[*succ] = new_distance;
	  best_predecessors[*succ].clear();
	  best_predecessors[*succ].push_back(*closest);
	}
	else if(new_distance == distance){
	  best_predecessors[*succ].push_back(*closest);
	}

      }
    }

  }
}

template <typename Type>
Graph<> XPathFinding<Type>::Xdijkstra(Graph<Type> & graph, GraphTypes::node_id sourceNode)
{
  std::map<GraphTypes::node_id, GraphTypes::Cost> distance_from_source;
  std::map<GraphTypes::node_id, std::list<GraphTypes::node_id> > best_predecessors;
  std::list<GraphTypes::node_id> candidates, allClosest;
  Graph<> paths(GraphTypes::DIRECTED, GraphTypes::WEIGHTED, GraphTypes::NOCONTENT);
  GraphTypes::node_id closest;
  bool allInfinite;

  //initialisation des tables
  _init(graph, paths, sourceNode, candidates, distance_from_source, best_predecessors);

  //début de l'algorithme
  allInfinite = false;
  while( paths.nodes_size() < graph.nodes_size() && !allInfinite ){
    allClosest = _allClosest(candidates, distance_from_source);

    closest = *allClosest.begin();
    if(distance_from_source[closest] == GraphTypes::POSITIVE_INFINITY){
      allInfinite = true;
    }
    else{
      _update_tables(graph, paths, allClosest, distance_from_source, best_predecessors);
      _add_edges(graph, paths, best_predecessors, allClosest);
      _remove_nodes(candidates, allClosest);
    }
  }

  return paths;
}

template <typename Type>
void XPathFinding<Type>::_init(Graph<Type> & graph, Graph<> & paths, GraphTypes::node_id sourceNode, std::list<GraphTypes::node_id> & candidates, std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source, GraphTypes::OptimizationType optimizationType)
{
  typename Graph<Type>::NodeIterator it;
  GraphTypes::Cost infinite;

  infinite = (optimizationType == GraphTypes::MINIMIZE) ? GraphTypes::POSITIVE_INFINITY : GraphTypes::NEGATIVE_INFINITY;

  distance_from_source[sourceNode] = 0;
  paths.add_node(sourceNode);

  for(it = graph.nodes_begin(); it != graph.nodes_end(); it++){

    if(*it != sourceNode){

      distance_from_source[*it] = infinite;
      candidates.push_back(*it);
    }
  }
}

template <typename Type>
std::deque<GraphTypes::node_id> XPathFinding<Type>::_coupe(Graph<Type> & graph, Graph<> & paths, std::list<GraphTypes::node_id> & candidates)
{
  std::list<GraphTypes::node_id>::iterator s;
  std::deque<GraphTypes::node_id> relaxed;
  std::set<GraphTypes::node_id> predecessors;
  std::set<GraphTypes::node_id>::iterator pred;
  bool relaxable;

  s = candidates.begin();
  while(s != candidates.end()){

    predecessors = graph.predecessors(*s);

    relaxable = false;

    if( predecessors.size() > 0 ){
      relaxable = true;
      pred = predecessors.begin();
      while(pred != predecessors.end() && relaxable){
	if( !paths.has_node(*pred) ){
	  relaxable = false;
	}
	pred++;
      }
    }

    if(relaxable){
      relaxed.push_back(*s);
    }

    s++;
  }

  return relaxed;
}

template <typename Type>
void XPathFinding<Type>::_update_tables(Graph<Type> & graph, Graph<> & paths, std::deque<GraphTypes::node_id> & waiting_for_insertion, std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source, std::map<GraphTypes::node_id, std::list<GraphTypes::node_id> > & best_predecessors, GraphTypes::OptimizationType optimizationType)
{
  std::set<GraphTypes::node_id> predecessors;
  std::set<GraphTypes::node_id>::iterator pred;
  std::deque<GraphTypes::node_id>::iterator s;
  GraphTypes::Cost new_distance;
  bool optimal;

  for(s = waiting_for_insertion.begin(); s != waiting_for_insertion.end(); s++){
    predecessors = graph.predecessors(*s);
    std::list<GraphTypes::node_id> & s_best_preds = best_predecessors[*s];
    GraphTypes::Cost & s_distance = distance_from_source[*s];

    for(pred = predecessors.begin(); pred != predecessors.end(); pred++){

      if( paths.has_node(*pred) ){

	new_distance = distance_from_source[*pred] + graph.getCost(*pred, *s);

	optimal = (optimizationType == GraphTypes::MINIMIZE) ? (new_distance < s_distance) : (new_distance > s_distance);
	if(optimal){
	  s_distance = new_distance;
	  s_best_preds.clear();
	  s_best_preds.push_back(*pred);
	}
	else if(new_distance == s_distance){
	  s_best_preds.push_back(*pred);	
	}

      }
    }

  }
}

template <typename Type>
void XPathFinding<Type>::_insert_waiting_nodes(Graph<Type> & graph, Graph<> & paths, std::deque<GraphTypes::node_id> & waiting_for_insertion, std::map<GraphTypes::node_id, std::list<GraphTypes::node_id> > & best_predecessors)
{
  std::list<GraphTypes::node_id>::iterator pred;
  GraphTypes::node_id s;

  while( waiting_for_insertion.size() > 0 ){
    s  = waiting_for_insertion.front();

    std::list<GraphTypes::node_id> & predecessors = best_predecessors[s];

    for(pred = predecessors.begin(); pred != predecessors.end(); pred++){
      paths.add_edge( *pred, s, graph.getCost(*pred, s) );
    }

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
Graph<> XPathFinding<Type>::_greedy_bellman(Graph<Type> & graph, GraphTypes::node_id sourceNode, GraphTypes::OptimizationType optimizationType)
{
  Graph<> paths(graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT);
  std::map<GraphTypes::node_id, GraphTypes::Cost> distance_from_source;
  std::map<GraphTypes::node_id, std::list<GraphTypes::node_id> > best_predecessors;
  std::list<GraphTypes::node_id> candidates;
  std::deque<GraphTypes::node_id> waiting_for_insertion;

  _init(graph, paths, sourceNode, candidates, distance_from_source, optimizationType);

  waiting_for_insertion = _coupe(graph, paths, candidates);
  while( waiting_for_insertion.size() > 0 ){
    _update_tables(graph, paths, waiting_for_insertion, distance_from_source, best_predecessors, optimizationType);
    _remove_nodes(candidates, waiting_for_insertion);
    _insert_waiting_nodes(graph, paths, waiting_for_insertion, best_predecessors);
    waiting_for_insertion = _coupe(graph, paths, candidates);
  }

  return paths;
}

template <typename Type>
void XPathFinding<Type>::_init(Graph<Type> & graph, Graph<> & paths, GraphTypes::node_id sourceNode, std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source, GraphTypes::OptimizationType optimizationType)
{
  typename Graph<Type>::NodeIterator node;
  GraphTypes::Cost infinite;

  infinite = (optimizationType == GraphTypes::MINIMIZE) ? GraphTypes::POSITIVE_INFINITY : GraphTypes::NEGATIVE_INFINITY;

  distance_from_source[sourceNode] = 0;
  paths.add_node(sourceNode);

  for(node = graph.nodes_begin(); node != graph.nodes_end(); node++){

    if(*node != sourceNode){

      distance_from_source[*node] = infinite;
    }
  }
}

template <typename Type>
void XPathFinding<Type>::_update_tables(Graph<Type> & graph, std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source, std::map<GraphTypes::node_id, std::list<GraphTypes::node_id> > & best_predecessors, GraphTypes::OptimizationType optimizationType)
{
  typename Graph<Type>::EdgeIterator it;
  Edge edge(0,0);
  GraphTypes::node_id pred, succ;
  GraphTypes::Cost distance, new_distance;
  bool optimal;

  for(it = graph.edges_begin(); it != graph.edges_end(); it++){
    edge = *it;
    pred = edge.source();
    succ = edge.target();
    GraphTypes::Cost & succ_distance = distance_from_source[succ];
    std::list<GraphTypes::node_id> & succ_pred_list = best_predecessors[succ];

    distance = succ_distance;
    new_distance = distance_from_source[pred] + graph.getCost(pred,succ);


    optimal = (optimizationType == GraphTypes::MINIMIZE) ? (new_distance < distance) : (new_distance > distance);
    if(optimal){
      succ_distance = new_distance;
      succ_pred_list.clear();
      succ_pred_list.push_back(pred);
    }
    else if(new_distance == distance){
      succ_pred_list.push_back(pred);
    }

  }
}

template <typename Type>
void XPathFinding<Type>::_build_paths_graph(Graph<Type> & graph, Graph<> & paths, GraphTypes::node_id sourceNode, std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source, std::map<GraphTypes::node_id, std::list<GraphTypes::node_id> > & best_predecessors)
{
  std::map<GraphTypes::node_id, std::list<GraphTypes::node_id> >::iterator it;
  GraphTypes::node_id succ;
  std::list<GraphTypes::node_id>::iterator pred;

  for(it = best_predecessors.begin(); it != best_predecessors.end(); it++){
    succ = it->first;
    std::list<GraphTypes::node_id> & pred_list = it->second;

    for(pred = pred_list.begin(); pred != pred_list.end(); pred++){
      if(succ != sourceNode){
	paths.add_edge( *pred, succ, graph.getCost(*pred, succ) );
      }
    }

  }
}

template <typename Type>
Graph<> XPathFinding<Type>::_dynamic_bellman(Graph<Type> & graph, GraphTypes::node_id sourceNode, GraphTypes::OptimizationType optimizationType)
{
  Graph<> paths(graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT);
  std::map<GraphTypes::node_id, GraphTypes::Cost> distance_from_source;
  std::map<GraphTypes::node_id, std::list<GraphTypes::node_id> > best_predecessors;
  std::pair<Graph<Type>, bool> result;
  int i, size;

  _init(graph, paths, sourceNode, distance_from_source, optimizationType);

  size = graph.nodes_size();
  for(i=0; i < size; i++){
    _update_tables(graph, distance_from_source, best_predecessors, optimizationType);
  }

  _build_paths_graph(graph, paths, sourceNode, distance_from_source, best_predecessors);

  _validity = _check_computing_validity(graph, distance_from_source);

  return paths;
}

template <typename Type>
Graph<> XPathFinding<Type>::Xbellman(Graph<Type> & graph, GraphTypes::node_id sourceNode, GraphTypes::AlgorithmicClass algoClass, GraphTypes::OptimizationType optimizationType)
{
  if(algoClass == GraphTypes::DYNAMIC){
    return _dynamic_bellman(graph, sourceNode, optimizationType);
  }
  else{
    return _greedy_bellman(graph, sourceNode, optimizationType);
  }
}

template <typename Type>
std::list<GraphTypes::Path> XPathFinding<Type>::paths_to(Graph<> & allPaths, GraphTypes::node_id target) throw(std::logic_error)
{
  std::list<GraphTypes::Path> paths, until_pred;
  std::set<GraphTypes::node_id> predecessors;
  std::set<GraphTypes::node_id>::iterator pred;
  std::list<GraphTypes::Path>::iterator onePath;

  if( !allPaths.is_directed() ){
    throw std::logic_error("Unsafe usage of XPathFinding<Type>::paths_to(Graph<>&, GraphTypes::node_id) with an undirected graph. Maybe you should convert the original graph before.");
  }

  if( allPaths.has_node(target) ){

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

  }

  return paths;
}

template <typename Type>
std::list<GraphTypes::Path> XPathFinding<Type>::Xbetween(Graph<Type> & graph, GraphTypes::node_id source, GraphTypes::node_id target, GraphTypes::SearchAlgorithm algo) throw(std::logic_error)
{
  std::list<GraphTypes::Path> to_target;
  Graph<> allPaths(graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT);

  allPaths = (algo == GraphTypes::DIJKSTRA) ? dijkstra(graph, source) : bellman(graph, source);

  to_target = paths_to(allPaths, target);

  return to_target;
}
