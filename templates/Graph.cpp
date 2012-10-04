template <typename Type>
Graph<Type>::Graph():Graph0::Graph0(){}

template <typename Type>
Graph<Type>::Graph(const Graph & source):Graph0::Graph0(source){

  _contents = source._contents;

}

template <typename Type>
Graph<Type>::~Graph(){}

template <typename Type>
Graph<Type> & Graph<Type>::operator=(const Graph<Type> & source){

  Graph0::operator=(source);

  _contents = source._contents;
  return *this;
}

template <typename Type>
bool Graph<Type>::is_empty(){
  return Graph0::is_empty();
}

template <typename Type>
bool Graph<Type>::has_node(Node::node_id id){
  return Graph0::has_node(id);
}

template <typename Type>
bool Graph<Type>::has_edge(Node::node_id src_node, Node::node_id target_node){
  return Graph0::has_edge(src_node, target_node);
}

template <typename Type>
void Graph<Type>::add_node(Node::node_id id, Type content){

  Graph0::add_node(id);

  _contents.insert( std::pair<Node::node_id, Type>(id, content) );
}

template <typename Type>
void Graph<Type>::remove_node(Node::node_id id){

  Graph0::remove_node(id);

  _contents.erase(id);
}

template <typename Type>
void Graph<Type>::add_edge(Node::node_id src_node, Type content1, Node::node_id target_node, Type content2){

  Graph0::add_edge(src_node, target_node);

  _contents.insert( std::pair<Node::node_id, Type>(src_node, content1) );
  _contents.insert( std::pair<Node::node_id, Type>(target_node, content2) );
}

template <typename Type>
void Graph<Type>::add_edge(Node::node_id existing_src, Node::node_id existing_target){

  if( _nodes.count(existing_src) && _nodes.count(existing_target) ){
    Graph0::add_edge(existing_src, existing_target);
  }
  else{
    throw std::string("Graph<Type>::add_edge(Node::node_id, Node::node_id) : use Graph<Type>::add_edge(Node::node_id, Type, Node::node_id, Type) to add edge with non-existing nodes");
  }
}

template <typename Type>
void Graph<Type>::remove_edge(Node::node_id src_node, Node::node_id target_node){

  Graph0::remove_edge(src_node, target_node);

  _contents.erase(src_node);
  _contents.erase(target_node);  
}

template <typename Type>
unsigned long Graph<Type>::size()const{
  return Graph0::size();
}

template <typename Type>
std::set<Node::node_id> Graph<Type>::successors(Node::node_id node){
  return Graph0::successors(node);
}

template <typename Type>
Node::node_id Graph<Type>::first_node(){
  try{
    return Graph0::first_node();
  }
  catch(std::string){
    throw std::string("Graph<Type>::first_node() : Attempt to acces empty Graph");
  }
}

template <typename Type>
Node::node_id Graph<Type>::next_node(){
  try{
    return Graph0::next_node();
  }
  catch(std::string){
    throw std::string("Graph<Type>::next_node() : Attempt to acces empty Graph");
  }
}

template <typename Type>
Node::node_id Graph<Type>::previous_node(){
  try{
    return Graph0::previous_node();
  }
  catch(std::string){
    throw std::string("Graph<Type>::previous_node() : Attempt to acces empty Graph");
  }
}

template <typename Type>
Node::node_id Graph<Type>::last_node(){
  try{
    return Graph0::last_node();
  }
  catch(std::string){
    throw std::string("Graph<Type>::last_node() : Attempt to acces empty Graph");
  }
}

template <typename Type>
Type Graph<Type>::get_node_content(Node::node_id id){
  typename std::map<Node::node_id,Type>::iterator it;

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

template<typename Type>
unsigned long Graph<Type>::internally(Node::node_id node){
  try{
    return Graph0::internally(node);
  }
  catch(std::string){
    throw std::string("Graph<Type>::internally(Node::node_id) : given node not in the graph");
  }
}

template<typename Type>
unsigned long Graph<Type>::externally(Node::node_id node){
  try{
    return Graph0::externally(node);
  }
  catch(std::string){
    throw std::string("Graph<Type>::externally(Node::node_id) : given node not in the graph");
  }
}
