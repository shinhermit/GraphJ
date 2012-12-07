template <typename Type>
Node::node_id PathFinding<Type>::_closest(std::map<Node::node_id, GraphTypes::Cost> & distances)
{
  Node::node_id s, closest;
  GraphTypes::Cost d, d_closest;
  std::map<Node::node_id, GraphTypes::Cost>::iterator it;

  it = distances.begin();
  closest = it->first;
  d_closest = it->second;

  it++;
  while( it != distances.end() ){
    s = it->first;
    d = it->second;

    if(d < d_closest){
      closest = s;
      d_closest = d;
    }

    it++;
  }

  return closest;
}

template <typename Type>
void PathFinding<Type>::_update_tables(Graph<Type> & graph, Graph<> & paths, Node::node_id closest, std::map<Node::node_id, GraphTypes::Cost> & distance_from_source, std::map<Node::node_id, Node::node_id> & best_predecessor)
{
  std::set<Node::node_id> successors;
  std::set<Node::node_id>::iterator it;
  GraphTypes::Cost new_distance;

  successors = graph.successors(closest);

  for(it = successors.begin(); it != successors.end(); it++){
    if( !paths.has_node(*it) ){

      new_distance = distance_from_source[closest] + graph.getCost(closest, *it);

      if(new_distance < distance_from_source[*it]){
	distance_from_source[*it] = new_distance;
	best_predecessor[*it] = closest;
      }
    }

  }
}

template <typename Type>
Graph<> PathFinding<Type>::dijkstra(Graph<Type> & graph, Node::node_id sourceNode)
{
  std::map<Node::node_id, GraphTypes::Cost> distance_from_source;
  std::map<Node::node_id, Node::node_id> best_predecessor;
  typename Graph<Type>::NodeIterator it;
  Graph<> paths(graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT);
  Node::node_id closest, bestPred;
  GraphTypes::Cost distance;
  bool allInfinite;

  //initialisations
  for(it = graph.nodes_begin(); it != graph.nodes_end(); it++){
    best_predecessor[*it] = sourceNode;

    if( graph.has_edge(sourceNode, *it) ){
      distance = graph.getCost(sourceNode, *it);
    }
    else{
      distance = GraphTypes::INFINITY;
    }
    distance_from_source[*it] = distance;
  }

  distance_from_source.erase(sourceNode);
  paths.add_node(sourceNode);

  //début de l'algorithme
  allInfinite = false;
  while( distance_from_source.size() > 0 && !allInfinite ){
    closest = _closest(distance_from_source);

    if(distance_from_source[closest] == GraphTypes::INFINITY){
      allInfinite = true;
    }
    else{
      bestPred = best_predecessor[closest];
      paths.add_edge( bestPred, closest, graph.getCost(bestPred, closest) );
      _update_tables(graph, paths, closest, distance_from_source, best_predecessor);
      distance_from_source.erase(closest);
    }
  }

  return paths;
}

template <typename Type>
std::deque<Node::node_id> PathFinding<Type>::_relaxation(Graph<Type> & graph, Graph<> & paths, std::list<Node::node_id> & candidates)
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
void PathFinding<Type>::_add_relaxed_nodes(Graph<Type> & graph, Graph<> & paths, std::deque<Node::node_id> & waiting_for_insertion, std::map<Node::node_id, Node::node_id> & best_predecessor)
{
  Node::node_id s, pred;

  while( waiting_for_insertion.size() > 0 ){
    s  = waiting_for_insertion.front();
    pred = best_predecessor[s];
    paths.add_edge( pred, s, graph.getCost(pred,s) );
    waiting_for_insertion.pop_front();
  }
}

template <typename Type>
void PathFinding<Type>::_update_tables(Graph<Type> & graph, std::deque<Node::node_id> & waiting_for_insertion, std::map<Node::node_id, GraphTypes::Cost> & distance_from_source, std::map<Node::node_id, Node::node_id> & best_predecessor)
{
  std::set<Node::node_id> predecessors;
  std::set<Node::node_id>::iterator candidate;
  std::deque<Node::node_id>::iterator s;
  Node::node_id closest;
  GraphTypes::Cost d_pred, d_closest;

  for(s = waiting_for_insertion.begin(); s != waiting_for_insertion.end(); s++){
    predecessors = graph.predecessors(*s);

    closest = *predecessors.begin();
    d_closest = graph.getCost(closest, *s);
    for(candidate = predecessors.begin(); candidate != predecessors.end(); candidate++){

      d_pred = graph.getCost(*candidate, *s);
      if(d_pred < d_closest){
	closest = *candidate;
	d_closest = d_pred;
      }

    }

    best_predecessor[*s] = closest;
    distance_from_source[*s] = d_closest;
  }
}

template <typename Type>
Graph<> PathFinding<Type>::bellman(Graph<Type> & graph, Node::node_id sourceNode)
{
  Graph<> paths(graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT);
  typename Graph<Type>::NodeIterator it;
  std::map<Node::node_id, GraphTypes::Cost> distance_from_source;
  std::map<Node::node_id, Node::node_id> best_predecessor;
  std::list<Node::node_id> candidates;
  std::deque<Node::node_id> waiting_for_insertion;

  //initialisations
  for(it = graph.nodes_begin(); it != graph.nodes_end(); it++){
    distance_from_source[*it] = GraphTypes::INFINITY;
    if(*it != sourceNode) candidates.push_back(*it);
  }

  paths.add_node(sourceNode);
  candidates.remove(sourceNode);

  //début de l'algorithme
  waiting_for_insertion = _relaxation(graph, paths, candidates);
  while( waiting_for_insertion.size() > 0 ){
    _update_tables(graph, waiting_for_insertion, distance_from_source, best_predecessor);
    _add_relaxed_nodes(graph, paths, waiting_for_insertion, best_predecessor);
    waiting_for_insertion = _relaxation(graph, paths, candidates);
  }

  return paths;
}

template <typename Type>
Graph<> PathFinding<Type>::bellman_dual(Graph<Type> & graph, Node::node_id targetNode)
{
  Graph<> paths(graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT);

  return paths;
}
