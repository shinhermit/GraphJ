template <typename Type>
void XPathFinding<Type>::_init(Graph<Type> & graph, Graph<> & paths, Node::node_id sourceNode, std::list<Node::node_id> & candidates, std::map<Node::node_id, GraphTypes::Cost> & distance_from_source, std::map<Node::node_id, std::list<Node::node_id> > & best_predecessors)
{
  typename Graph<Type>::NodeIterator it;
  GraphTypes::Cost distance;

  distance_from_source[sourceNode] = 0;
  paths.add_node(sourceNode);

  for(it = graph.nodes_begin(); it != graph.nodes_end(); it++){
    best_predecessors[*it] = std::list<Node::node_id>();
    best_predecessors[*it].push_back(sourceNode);

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
std::list<Node::node_id> XPathFinding<Type>::_minimals(std::list<Node::node_id> & candidates, std::map<Node::node_id, GraphTypes::Cost> & distance_from_source)
{
  Node::node_id closest;
  GraphTypes::Cost d_closest, new_distance;
  std::list<Node::node_id>::iterator node;
  std::list<Node::node_id> allClosest;

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
void XPathFinding<Type>::_add_edges(Graph<Type> & graph, Graph<> & paths, std::map<Node::node_id, std::list<Node::node_id> > & best_predecessors, std::list<Node::node_id> allClosest)
{
  std::list<Node::node_id> best_preds;
  std::list<Node::node_id>::iterator closest, pred;

  for(closest = allClosest.begin(); closest != allClosest.end(); closest++){
    best_preds = best_predecessors[*closest];

    for(pred = best_preds.begin(); pred != best_preds.end(); pred++){
      paths.add_edge( *pred, *closest, graph.getCost(*pred, *closest) );
    }
  }
}

template <typename Type>
void XPathFinding<Type>::_remove_nodes(std::list<Node::node_id> & candidates, std::list<Node::node_id> allClosest)
{
  std::list<Node::node_id>::iterator closest;

  for(closest = allClosest.begin(); closest != allClosest.end(); closest++){
    candidates.remove(*closest);
  }
}

template <typename Type>
void XPathFinding<Type>::_update_tables(Graph<Type> & graph, Graph<> & paths, std::list<Node::node_id> allClosest, std::map<Node::node_id, GraphTypes::Cost> & distance_from_source, std::map<Node::node_id, std::list<Node::node_id> > & best_predecessors)
{
  std::set<Node::node_id> successors;
  std::set<Node::node_id>::iterator succ;
  std::list<Node::node_id>::iterator closest;
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
Graph<> XPathFinding<Type>::Xdijkstra(Graph<Type> & graph, Node::node_id sourceNode)
{
  std::map<Node::node_id, GraphTypes::Cost> distance_from_source;
  std::map<Node::node_id, std::list<Node::node_id> > best_predecessors;
  std::list<Node::node_id> candidates, allClosest;
  Graph<> paths(graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT);
  Node::node_id closest;
  bool allInfinite;

  //initialisation des tables
  _init(graph, paths, sourceNode, candidates, distance_from_source, best_predecessors);

  //début de l'algorithme
  allInfinite = false;
  while( paths.nodes_size() < graph.nodes_size() && !allInfinite ){
    allClosest = _minimals(candidates, distance_from_source);

    closest = *allClosest.begin();
    if(distance_from_source[closest] == GraphTypes::INFINITY){
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
std::deque<Node::node_id> XPathFinding<Type>::_relaxation(Graph<Type> & graph, Graph<> & paths, std::list<Node::node_id> & candidates)
{
  std::list<Node::node_id>::iterator s;
  std::deque<Node::node_id> relaxed;
  std::set<Node::node_id> predecessors;
  std::set<Node::node_id>::iterator pred;
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
      candidates.erase(s++);
    }
    else{
      s++;
    }

  }

  return relaxed;
}

template <typename Type>
void XPathFinding<Type>::_update_tables(Graph<Type> & graph, Graph<> & paths, std::deque<Node::node_id> & waiting_for_insertion, std::map<Node::node_id, GraphTypes::Cost> & distance_from_source, std::map<Node::node_id, std::list<Node::node_id> > & best_predecessors)
{
  std::set<Node::node_id> predecessors;
  std::set<Node::node_id>::iterator pred;
  std::deque<Node::node_id>::iterator s;
  GraphTypes::Cost new_distance;

  for(s = waiting_for_insertion.begin(); s != waiting_for_insertion.end(); s++){
    predecessors = graph.predecessors(*s);
    std::list<Node::node_id> & s_best_preds = best_predecessors[*s]; //possible issue
    GraphTypes::Cost & s_distance = distance_from_source[*s]; //possible issue

    for(pred = predecessors.begin(); pred != predecessors.end(); pred++){

      if( paths.has_node(*pred) ){

	new_distance = distance_from_source[*pred] + graph.getCost(*pred, *s);
	if(new_distance < s_distance){
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
void XPathFinding<Type>::_add_relaxed_nodes(Graph<Type> & graph, Graph<> & paths, std::deque<Node::node_id> & waiting_for_insertion, std::map<Node::node_id, std::list<Node::node_id> > & best_predecessors)
{
  std::list<Node::node_id>::iterator pred;
  Node::node_id s;

  while( waiting_for_insertion.size() > 0 ){
    s  = waiting_for_insertion.front();

    std::list<Node::node_id> & predecessors = best_predecessors[s];

    for(pred = predecessors.begin(); pred != predecessors.end(); pred++){
      paths.add_edge( *pred, s, graph.getCost(*pred, s) );
    }

    waiting_for_insertion.pop_front();
  }
}

template <typename Type>
Graph<> XPathFinding<Type>::Xbellman(Graph<Type> & graph, Node::node_id sourceNode)
{
  Graph<> paths(graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT);
  typename Graph<Type>::NodeIterator it;
  std::map<Node::node_id, GraphTypes::Cost> distance_from_source;
  std::map<Node::node_id, std::list<Node::node_id> > best_predecessors;
  std::list<Node::node_id> candidates;
  std::deque<Node::node_id> waiting_for_insertion;

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
    _update_tables(graph, paths, waiting_for_insertion, distance_from_source, best_predecessors);
    _add_relaxed_nodes(graph, paths, waiting_for_insertion, best_predecessors);
    waiting_for_insertion = _relaxation(graph, paths, candidates);
  }

  return paths;
}

template <typename Type>
std::list<Path> XPathFinding<Type>::paths_to(Graph<Type> & graph, Graph<> & allPaths, Node::node_id target)
{
  std::list<Path> paths, until_pred;
  std::set<Node::node_id> predecessors;
  std::set<Node::node_id>::iterator pred;
  std::list<Path>::iterator onePath;

  predecessors = graph.predecessors(target);
  if( predecessors.size() > 0 ){

    for(pred = predecessors.begin(); pred != predecessors.end(); pred++){
      until_pred = paths_to(graph, allPaths, *pred);
      paths.insert(paths.end(), until_pred.begin(), until_pred.end() );
    }
  }

  if( paths.size() > 0 ){

    for(onePath = paths.begin(); onePath != paths.end(); onePath++){
      onePath->push_back(target);
    }
  }
  else{

    paths.push_back( std::list<Node::node_id>() );
    onePath = paths.begin();
    onePath->push_back(target);
  }

  return paths;
}

template <typename Type>
std::list<Path> XPathFinding<Type>::Xbetween(Graph<Type> & graph, Node::node_id source, Node::node_id target, GraphTypes::SearchAlgorithm algo)
{
  std::list<Path> to_target;
  Graph<> allPaths(graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT);

  allPaths = (algo == GraphTypes::DIJKSTRA) ? dijkstra(graph, source) : bellman(graph, source);

  to_target = paths_to(graph, allPaths, target);

  return to_target;
}
