template<typename Type>
void Algorithms::breadth_visit(Graph<Type> & graph, Node::node_id node, Visitor<Type> & visitor, std::set<Node::node_id> & marker){
  Node::node_id son, grand_son;
  std::deque<Node::node_id> waiters, grand_successors;
  std::set<Node::node_id> nodes_set;

  waiters.push_back(node);

  while( waiters.size() > 0 ){
    son = waiters.front();
    waiters.pop_front();
    visitor.treat(graph, son);

    nodes_set = graph.successors(son);
    grand_successors.assign(nodes_set.begin(), nodes_set.end());
    nodes_set.clear();

    while( grand_successors.size() > 0 ){
      grand_son = grand_successors.front();
      if( !marker.count(grand_son) ){
	marker.insert(grand_son);
	waiters.push_back(grand_son);
      }

      grand_successors.pop_front();
    }
  }
}

template<typename Type>
void Algorithms::breadth_first_search(Graph<Type> & graph, Visitor<Type> & visitor){
  unsigned long i, size;
  Node::node_id node;
  std::set<Node::node_id> marker;

  size = graph.nodes_size();
  if(size > 0){
    node = graph.first_node();

    for(i=0; i < size; i++){
      if( !marker.count(node) )
	breadth_visit(graph, node, visitor, marker);

      node = graph.next_node();
    }
  }

}

template<typename Type>
void Algorithms::depth_visit(Graph<Type> & graph, Node::node_id node, Visitor<Type> & visitor, std::set<Node::node_id> & marker){
  Node::node_id curr_node;
  std::deque<Node::node_id> successors;
  std::set<Node::node_id> nodes_set;

  visitor.treat(graph, node);
  marker.insert(node);

  nodes_set = graph.successors(node);
  successors.assign( nodes_set.begin(), nodes_set.end() );
  nodes_set.clear();

  while( successors.size() > 0 ){
    curr_node = successors.front();

    if( !marker.count(curr_node) ){
      depth_visit(graph, curr_node, visitor, marker);
    }

    successors.pop_front();
  }
}

template<typename Type>
void Algorithms::depth_first_search(Graph<Type> & graph, Visitor<Type> & visitor){
  Node::node_id node;
  unsigned long i, size;
  std::set<Node::node_id> marker;

  size = graph.nodes_size();
  if( size > 0 ){

    node = graph.first_node();

    for(i=0; i < size; i++){
      if( !marker.count(node) )
	depth_visit(graph, node, visitor, marker);

      node = graph.next_node();
    }
  }

}

template<typename Type>
std::map<Node::node_id, unsigned long> color_each_node(Graph<Type> & graph){
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
Graph<Type> Algorithms::acm_kruskal(Graph<Type> & graph){
  std::map<Node::node_id, unsigned long> color_mapper;
  std::set<WeightedEdge> sorted_edges;
  std::set<WeightedEdge>::iterator it;
  Graph<Type> acm;
  Node::node_id node1, node2;
  unsigned long i, graph_size, node1_color, node2_color, acm_color;
  GraphTypes::Cost cost;

  color_mapper = color_each_node<Type>(graph);

  {
    WeightedEdgeSorter<Type> weightedEdgeSorter;
    breadth_first_search<Type>(graph, weightedEdgeSorter);
    sorted_edges = weightedEdgeSorter.getEdgeSet();
  }

  graph_size = graph.nodes_size();
  acm_color = color_mapper.size() + 1;
  it = sorted_edges.begin();

  while( it != sorted_edges.end() && acm.nodes_size() < graph_size ){
    node1 = it->source();
    node2 = it->target();
    cost = it->cost();

    node1_color = color_mapper[node1];
    node2_color = color_mapper[node2];

    if( node1_color != node2_color ){
      color_mapper[node1] = acm_color;
      color_mapper[node2] = acm_color;

      acm.add_edge( node1, node2, cost );
    }

    it++;
  }

  return acm;
}


template<typename Type>
Graph<Type> Algorithms::acm_prim(Graph<Type> & graph){
}
