template<typename Type>
void Traverse<Type>::nodes(Graph<Type> & graph, Visitor<Type> & visitor){
  typename Graph<Type>::NodeIterator nodeIt;

  nodeIt = graph.nodes_begin();

  while( nodeIt != graph.nodes_end() ){
    visitor.treat(graph, *nodeIt);

    nodeIt++;
  }
}

template<typename Type>
void Traverse<Type>::breadth_once(Graph<Type> & graph, Node::node_id node, Visitor<Type> & visitor, std::set<Node::node_id> & marker){
  Node::node_id son, grand_son;
  std::deque<Node::node_id> waiters, grand_successors;
  std::set<Node::node_id> nodes_set;

  waiters.push_back(node);

  while( waiters.size() > 0 ){
    son = waiters.front();
    waiters.pop_front();
    visitor.treat(graph, son);
    marker.insert(son);

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
void Traverse<Type>::breadth(Graph<Type> & graph, Visitor<Type> & visitor){
  typename Graph<Type>::NodeIterator nodeIt;
  std::set<Node::node_id> marker;

  if( graph.nodes_size() > 0){
    *nodeIt = graph.nodes_begin();

    while( nodeIt != graph.at_nodes_end() ){
      if( !marker.count(*nodeIt) )
	breadth_once(graph, *nodeIt, visitor, marker);

      *nodeIt++;
    }
  }

}

template<typename Type>
void Traverse<Type>::depth_once(Graph<Type> & graph, Node::node_id node, Visitor<Type> & visitor, std::set<Node::node_id> & marker){
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
      depth_once(graph, curr_node, visitor, marker);
    }

    successors.pop_front();
  }
}

template<typename Type>
void Traverse<Type>::depth(Graph<Type> & graph, Visitor<Type> & visitor){
  typename Graph<Type>::NodeIterator nodeIt;
  std::set<Node::node_id> marker;

  if( graph.nodes_size() > 0 ){

    *nodeIt = graph.nodes_begin();

    while( nodeIt != graph.nodes_end() ){
      if( !marker.count(*nodeIt) )
	depth_once(graph, *nodeIt, visitor, marker);

      *nodeIt++;
    }
  }

}

template<typename Type>
void Traverse<Type>::reverse_breadth_once(Graph<Type> & graph, Node::node_id node, Visitor<Type> & visitor, std::set<Node::node_id> & marker){
  Node::node_id father, grand_father;
  std::deque<Node::node_id> waiters, grand_predecessors;
  std::set<Node::node_id> nodes_set;

  waiters.push_back(node);

  while( waiters.size() > 0 ){
    father = waiters.front();
    waiters.pop_front();
    visitor.treat(graph, father);
    marker.insert(father);

    nodes_set = graph.predecessors(father);
    grand_predecessors.assign(nodes_set.begin(), nodes_set.end());
    nodes_set.clear();

    while( grand_predecessors.size() > 0 ){
      grand_father = grand_predecessors.front();
      if( !marker.count(grand_father) ){
	marker.insert(grand_father);
	waiters.push_back(grand_father);
      }

      grand_predecessors.pop_front();
    }
  }
}

template<typename Type>
void Traverse<Type>::reverse_breadth(Graph<Type> & graph, Visitor<Type> & visitor){
  typename Graph<Type>::NodeIterator nodeIt;
  std::set<Node::node_id> marker;

  if( graph.nodes_size() > 0){
    *nodeIt = graph.nodes_begin();

    while( nodeIt != graph.at_nodes_end() ){
      if( !marker.count(*nodeIt) )
	reverse_breadth_once(graph, *nodeIt, visitor, marker);

      *nodeIt++;
    }
  }

}
