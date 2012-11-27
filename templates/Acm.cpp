template<typename Type>
std::map<Node::node_id, unsigned long> Acm<Type>::_color_each_node(Graph<Type> & graph){
  std::map<Node::node_id, unsigned long> colored;
  unsigned long nodes_size, color;
  typename Graph<Type>::NodeIterator nodeIt;

  color = 0;
  nodes_size = graph.nodes_size();

  nodeIt = graph.nodes_begin();
  while( color < nodes_size ){

    colored.insert( std::pair<Node::node_id, unsigned long>(*nodeIt, color) );

    nodeIt++;
    color++;
  }

  return colored;
}

template<typename Type>
void Acm<Type>::_update_colors(Graph<Type> & graph, Graph<> & acm, std::map<Node::node_id, unsigned long> & color_mapper, Node::node_id node1, Node::node_id node2){
  unsigned long col1, col2, master_col, slave_col;
  bool has1, has2;
  typename Graph<Type>::NodeIterator nIt;
  std::map<Node::node_id, unsigned long>::iterator it, it_col1, it_col2;

  has1 = acm.has_node(node1);
  has2 = acm.has_node(node2);

  //On évite d'utiliser les crochets,
  //pour faire la recherche une seule fois
  it_col1 = color_mapper.find(node1);
  it_col2 = color_mapper.find(node2);

  col1 = it_col1->second;
  col2 = it_col2->second;

  if(!has1 && !has2){
    master_col = col1;

    it_col1->second = master_col;
    it_col2->second = master_col;
  }
  else if(has1 && !has2){
    it_col2->second = col1;
  }
  else if(has2 && !has1){
    it_col1->second = col2;
  }
  else{
    //contrairement à la version en pseudo-code,
    //on ne tient pas compte de la taille des classes
    //car cela reviendrait à exécuter 2 fois la boucle ci-dessous
    master_col = col1;
    slave_col = col2;

    nIt = acm.nodes_begin();
    while( nIt != acm.nodes_end() ){
      it = color_mapper.find(*nIt);
      if(it->second == slave_col){
	it->second = master_col;
      }

      nIt++;
    }
  }
}

template<typename Type>
std::set<WeightedEdge> Acm<Type>::_sort_edges_by_weights(Graph<Type> & graph){
  std::set<WeightedEdge> sorted_edges;
  std::set<Node::node_id> successors;
  std::set<Node::node_id>::iterator it;
  typename Graph<Type>::NodeIterator node;
  GraphTypes::Cost cost;

  node = graph.nodes_begin();

  while( node != graph.nodes_end() ){

    successors = graph.successors(*node);

    for(it = successors.begin(); it != successors.end(); it++){

      cost = graph.getCost(*node, *it);

	sorted_edges.insert( WeightedEdge(*node, *it, cost) );
      // if( graph.is_directed() ){
      // 	sorted_edges.insert( WeightedEdge(node, *it, cost) );
      // }
      // else{
      // 	if( !graph.has_edge(*it, node) ){
      // 	  sorted_edges.insert( WeightedEdge(node, *it, cost) );
      // 	}
      // }

    }
    node++;
  }

  return sorted_edges;
}

template<typename Type>
std::set<WeightedEdge> Acm<Type>::_weightedNeighboursFromSuccessors(Graph<Type> graph, Node::node_id node){
  std::set<WeightedEdge> weightedNeighbours;
  std::set<Node::node_id> successors, predecessors;
  std::set<Node::node_id>::iterator it ;

  successors = graph.successors(node);

  for(it = successors.begin(); it != successors.end(); it++){    
    weightedNeighbours.insert( WeightedEdge( node, *it, graph.getCost(node, *it) ) );
  }

  if( graph.is_directed() ){

    predecessors = graph.predecessors(node);

    for(it = predecessors.begin(); it != predecessors.end(); it++){    
      weightedNeighbours.insert( WeightedEdge( node, *it, graph.getCost(*it, node) ) );
    }
  }

  return weightedNeighbours;
}

template<typename Type>
Graph<> Acm<Type>::kruskal(Graph<Type> & graph){
  std::map<Node::node_id, unsigned long> color_mapper;
  std::set<WeightedEdge> sorted_edges;
  std::set<WeightedEdge>::iterator it;
  Graph<> acm(graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT);
  Node::node_id node1, node2;
  unsigned long graph_size, node1_color, node2_color;
  GraphTypes::Cost cost;

  color_mapper = _color_each_node(graph);

  sorted_edges = _sort_edges_by_weights(graph);

  graph_size = graph.nodes_size();
  it = sorted_edges.begin();

  while( it != sorted_edges.end() && acm.nodes_size() < graph_size ){
    node1 = it->source();
    node2 = it->target();
    cost = it->cost();

    node1_color = color_mapper[node1];
    node2_color = color_mapper[node2];

    if( node1_color != node2_color ){
      _update_colors(graph, acm, color_mapper, node1, node2);

      acm.add_edge(node1, node2, cost);
    }

    it++;
  }

  return acm;
}

template<typename Type>
Graph<> Acm<Type>::prim(Graph<Type> & graph){
  std::set<WeightedEdge> fusion, newNeighbours;
  Graph<Type> alterableCopy;
  Graph<> acm( graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT );
  WeightedEdge min_edge(0,0,0);
  Node::node_id first_node, source_node, target_node;
  GraphTypes::Cost cost;

  alterableCopy = graph;

  first_node = *alterableCopy.nodes_begin();
  acm.add_node(first_node);

  fusion = _weightedNeighboursFromSuccessors(alterableCopy, first_node);
  
  alterableCopy.remove_node(first_node);

  while( alterableCopy.nodes_size() > 0 ){
    min_edge = *fusion.begin();
    fusion.erase( fusion.begin() );

    source_node = min_edge.source();
    target_node = min_edge.target();
    cost = min_edge.cost();

    if( alterableCopy.has_node(target_node) ){
      acm.add_edge(source_node, target_node, cost);

      newNeighbours = _weightedNeighboursFromSuccessors(alterableCopy, target_node);

      fusion.insert( newNeighbours.begin(), newNeighbours.end() );

      alterableCopy.remove_node(target_node);
    }
  }

  return acm;
}
