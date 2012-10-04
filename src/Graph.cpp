template <typename Type>
Graph<Type>::Graph():Graph0::Graph0(){}

template <typename Type>
Graph<Type>::Graph(const Graph<Type> & source):Graph0::Graph0(source){

  _contents = source._contents;

}

template <typename Type>
Graph<Type>::~Graph(){}

template <typename Type>
Graph<Type> & Graph<Type>::operator=(const Graph<Type> & source){

  Graph0::operator=(source);

  _content = source._content;
  return *this;
}

template <typename Type>
bool Graph<Type>::is_empty(){
  return Graph0::is_empty();
}

template <typename Type>
bool Graph<Type>::has_node(node::node_id id){
  return Graph0::has_node(id);
}

template <typename Type>
bool Graph<Type>::has_edge(node::node_id src_node, node::node_id target_node){
  return Graph0::has_edge(src_node, target_node);
}

template <typename Type>
void Graph<Type>::add_node(node::node_id id, Type content){

  Graph0::add_node(id);

  _contents.insert( std::pair<node_id, Type>(id, content) );
}

template <typename Type>
void Graph<Type>::remove_node(node::node_id id){

  Graph0::remove_node(id);

  _contents.erase(id);
}

template <typename Type>
void Graph<Type>::add_edge(node::node_id src_node, Type content1, node::node_id target_node, Type content2){

  Graph0::add_edge(src_node, target_node);

  _contents.insert( std::pair<node_id, Type>(src_node, content1) );
  _contents.insert( std::pair<node_id, Type>(target_node, content2) );
}

template <typename Type>
void Graph<Type>::remove_edge(node::node_id node_src_node, node::node_id node_target_node){

  Graph0::remove_edge(src_node, target_node);

  _contents.erase(src_node);
  _contents.erase(target_node);  
}

template<typename Type>
unsigned long Graph<Type>::size()const{
  return Graph0::size();
}

std::set<Node::node_id> Graph<Type>::successors(Node::node_id node){
  return Graph0::successors(node);
}

template <typename Type>
Node::node_id Graph<Type>::first_node(){
  try{
    return Graph0::first_node();
  }
  catch(std::string){
    throw std::string("Graph<Type>::first_node() : Can not access empty graph");
  }
}

template <typename Type>
Node::node_id Graph<Type>::next_node(){
  try{
    return Graph0::next_node();
  }
  catch(std::string){
    throw std::string("Graph<Type>::next_node() : Can not access empty graph");
  }
}

template <typename Type>
Node::node_id Graph<Type>::previous_node(){
  try{
    return Graph0::previous_node();
  }
  catch(std::string){
    throw std::string("Graph<Type>::previous_node() : Can not access empty graph");
  }
}

template <typename Type>
Node::node_id Graph<Type>::last_node(){
  try{
    return Graph0::last_node();
  }
  catch(std::string){
    throw std::string("Graph<Type>::last_node() : Can not access empty graph");
  }
}

template <typename Type>
Type Graph<Type>::get_node_content(node::node_id id){
  std::map<Node::node_id, Type>::iterator it;

  if( has_node(id) ){
    it = _contents.find(id);
    if( it != _contents.end() ){
      return it->second;
    }
    else{
      throw std::string("Graph<Type>::get_node_content(node_id) : possible conception error <-- Graph has a node which is not mapped to any content");
    }
  }
  else{
    throw std::string("Graph<Type>::get_node_content(node_id) : given value is not an id of any node of the Graph");
  }
}
