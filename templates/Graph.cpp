
template <typename Type>
Graph<Type>::Graph(GraphTypes::EdgeType edgeType, GraphTypes::EdgeState state):PonderableGraph(edgeType, state){}

template <typename Type>
Graph<Type>::Graph(const Graph<Type> & source):PonderableGraph::PonderableGraph(source), _contents(source._contents){}

template <typename Type>
Graph<Type> & Graph<Type>::operator=(const Graph<Type> & source){

  PonderableGraph::operator=(source);

  _contents = source._contents;
  return *this;
}

template <typename Type>
void Graph<Type>::add_node(Node::node_id id, Type content){

  PonderableGraph::add_node(id);

  _contents.insert( std::pair<Node::node_id, Type>(id, content) );
}

template <typename Type>
void Graph<Type>::remove_node(Node::node_id id){

  PonderableGraph::remove_node(id);

  _contents.erase(id);
}

template <typename Type>
void Graph<Type>::add_edge(Node::node_id src_node, Type content1, Node::node_id target_node, Type content2, GraphTypes::Cost cost){

  PonderableGraph::add_edge(src_node, target_node, cost);

  _contents.insert( std::pair<Node::node_id, Type>(src_node, content1) );
  _contents.insert( std::pair<Node::node_id, Type>(target_node, content2) );
}

template <typename Type>
void Graph<Type>::add_edge(Node::node_id existing_src, Node::node_id existing_target, GraphTypes::Cost cost) throw(std::invalid_argument){

  if( has_node(existing_src) && has_node(existing_target) ){
    PonderableGraph::add_edge(existing_src, existing_target, cost);
  }
  else{
    throw std::invalid_argument("Graph<Type>::add_edge(node::node_id, node::node_id, PonderableGraph::Cost=1.F) : given nodes must already be in the Graph.\n Consider using:\n Graph<Type>::add_edge(node::node_id, Type, node::node_id, Type, PonderableGraph::Cost=1.F)");
  }
}

template <typename Type>
void Graph<Type>::remove_edge(Node::node_id src_node, Node::node_id target_node){

  PonderableGraph::remove_edge(src_node, target_node);

  _contents.erase(src_node);
  _contents.erase(target_node);  
}

template <typename Type>
void Graph<Type>::set_node_content(Node::node_id id, Type content) throw(std::invalid_argument){
  if( has_node(id) ){
    _contents[id] = content;
  }
  else{
    throw std::invalid_argument("Graph<Type>::set_node_content(node::node_id, Type) : given id does not refer to a valid node");
  }
}

template <typename Type>
Type Graph<Type>::get_node_content(Node::node_id id) throw(std::logic_error, std::invalid_argument){
  typename std::map<Node::node_id, Type>::iterator it;

  if( has_node(id) ){
    it = _contents.find(id);
    if( it != _contents.end() ){
      return it->second;
    }
    else{
      throw std::logic_error("Graph<Type>::get_node_content(node_id) : possible conception error <-- Graph has a node which is not mapped to any content");
    }
  }
  else{
    throw std::invalid_argument("Graph<Type>::get_node_content(node_id) : given value is not an id of any node of the Graph");
  }
}
