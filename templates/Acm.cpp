template<typename Type>
std::map<Node::node_id, unsigned long> Acm<Type>::_color_each_node(Graph<Type> & graph){
  std::map<Node::node_id, int> colored;
  Node::node_id node;
  unsigned long nodes_size, color;

  nodes_size = graph.nodes_size();
  node = graph.first_node();
  color = 0;

  while( color < nodes_size ){

    colored.insert(node, color);

    node = graph.next_node();
    color++;
  }

  return colored;
}

template<typename Type>
void Acm<Type>::_update_colors(Graph<Type> & graph, Graph<Type> & acm, std::map<Node::node_id, unsigned long> & color_mapper, Node::node_id node1, Node::node_id node2){
    unsigned long col1, col2, master_col, slave_col, acm_size;
    bool has1, has2;
    Node::node_id node;
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

    acm_size = acm.size();
    node = acm.first_node();
    while( !acm.at_nodes_end() ){
      it = color_mapper.find(node);
      if(it->second == slave_col){
	it->second = master_col;
      }

      node = acm.next_node();
    }
  }
}

template<typename Type>
std::set<WeightedEdge> Acm<Type>::_sort_edges_by_weights(Graph<Type> & graph){
  std::set<WeightedEdge> sorted_edges;
  std::set<Node::node_id> successors;
  std::set<Node::node_id>::iterator it;
  Node::node_id node;
  GraphTypes::Cost cost;
  unsigned long i, graph_size;

  node = graph.first_node();
  graph_size = graph.nodes_size();
  i = 0;

  while(i < graph_size){

    successors = graph.successors(node);

    for(it = successors.begin(); it != successors.end(); it++){

      cost = graph.getCost(node, *it);

      if( graph.is_oriented() ){
	sorted_edges.insert( WeightedEdge(node, *it, cost) );
      }
      else{
	if( !graph.has_edge(*it, node) ){
	  sorted_edges.insert( WeightedEdge(node, *it, cost) );
	}
      }

    }
    i++;
    node = graph.next_node();
  }

  return sorted_edges;
}

template<typename Type>
std::set<WeightedEdge> Acm<Type>::_weightedNeighboursFromSuccessors(Graph<Type> graph, Node::node_id node){
  std::set<WeightedEdge> weightedNeighbours;
  std::set<Node::node_id> successors;
  std::set<Node::node_id>::iterator it ;

  successors = graph.successors(node);

  for(it = successors.begin(); it != successors.end(); it++){    
    weightedNeighbours.insert( WeightedEdge( node, *it, graph.getCost(node, *it) ) );
  }

  return weightedNeighbours;
}

template<typename Type>
Graph<Type> Acm<Type>::kruskal(Graph<Type> & graph){
  std::map<Node::node_id, unsigned long> color_mapper;
  std::set<WeightedEdge> sorted_edges;
  std::set<WeightedEdge>::iterator it;
  Graph<Type> acm; //il faudrait récupérer les options de graph ( is_directed(), is_weighted() )
  Node::node_id node1, node2;
  Type node1_content, node2_content;
  unsigned long i, graph_size, node1_color, node2_color;
  GraphTypes::Cost cost;

  color_mapper = _color_each_node(graph);

  sorted_edges = _sort_edges_by_weights(graph);

  graph_size = graph.nodes_size();
  it = sorted_edges.begin();

  while( it != sorted_edges.end() && acm.nodes_size() < graph_size ){
    node1 = it->source();
    node1_content = graph.getContent(node1);

    node2 = it->target();
    node2_content = graph.getContent(node2);

    cost = it->cost();

    node1_color = color_mapper[node1];
    node2_color = color_mapper[node2];

    if( node1_color != node2_color ){
      _update_colors(graph, acm, color_mapper, node1, node2);

      acm.add_edge( node1, node1_content, node2, node2_content, cost );
    }

    it++;
  }

  return acm;
}

template<typename Type>
Graph<Type> Acm<Type>::prim(Graph<Type> & graph){
  std::set<WeightedEdge> fusion, newNeighbours;
  Graph<Type> alterableCopy;
  Graph<Type> acm;
  WeightedEdge min_edge;
  Node::node_id first_node, source_node, target_node;
  Type content;
  GraphTypes::Cost cost;

  alterableCopy = graph;

  first_node = alterableCopy.first_node();
  acm.add_node( first_node, alterableCopy.getContent(first_node) );

  fusion = _weightedNeighboursFromSuccessors(alterableCopy, first_node);
  
  alterableCopy.remove_node(first_node);

  while( alterableCopy.size() > 0 ){
    min_edge = *fusion.begin();

    source_node = min_edge.source();
    target_node = min_edge.target();
    cost = min_edge.cost();
    content = alterableCopy.getContent(target_node);

    acm.add_node(target_node, content);
    acm.add_edge(source_node, target_node, cost);

    fusion.erase( fusion.begin() );

    newNeighbours = _weightedNeighboursFromSuccessors(alterableCopy, target_node);

    fusion.insert( newNeighbours.begin(), newNeighbours.end() );

    alterableCopy.remove_node(target_node);
  }

  return acm;
}
