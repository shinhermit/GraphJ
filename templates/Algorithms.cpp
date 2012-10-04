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

  if( graph.size() > 0 ){
    node = graph.first_node();
    size = graph.size();
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

  if( graph.size() > 0 ){
    node = graph.first_node();
    size = graph.size();
    for(i=0; i < size; i++){
      if( !marker.count(node) )
	depth_visit(graph, node, visitor, marker);
      node = graph.next_node();
    }
  }
}
