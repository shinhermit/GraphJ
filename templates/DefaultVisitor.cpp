template<typename Type>
DefaultVisitor<Type>::DefaultVisitor():_buffer(""){}

template<typename Type>
DefaultVisitor<Type>::~DefaultVisitor(){}

//Attention: cette méthode a été spécialisée pour les std::string
template<typename Type>
void DefaultVisitor<Type>::treat(Graph<Type> & graph, GraphTypes::node_id node){
  std::set<GraphTypes::node_id> successors;
  std::set<GraphTypes::node_id>::iterator it;
  std::ostringstream oss;

  successors = graph.successors(node);

  oss << "n" << node << ": ";

  for(it = successors.begin(); it != successors.end(); it++){
    if( graph.is_directed() || (!graph.is_directed() && !_visited.count(*it)) ){

      oss << "n" << *it << " ";
    }
  }

  oss << std::endl;

  _buffer += oss.str();
}

//Spécialisation pour les std::string
template<>
void DefaultVisitor<std::string>::treat(Graph<std::string> & graph, GraphTypes::node_id node){
  std::set<GraphTypes::node_id> successors;
  std::set<GraphTypes::node_id>::iterator it;
  std::ostringstream oss;
  std::string linkSymbol;

  linkSymbol = graph.is_directed() ? " -> " : " -- ";

  successors = graph.successors(node);

  oss << graph.get_node_content(node) << linkSymbol;

  for(it = successors.begin(); it != successors.end(); it++){
    if( graph.is_directed() || (!graph.is_directed() && !_visited.count(*it)) ){

      oss << graph.get_node_content(*it) << "; ";
    }
  }

  oss << std::endl;

  _buffer += oss.str();
}

template<typename Type>
std::string DefaultVisitor<Type>::nodes_representation()const{
  return _buffer;
}

template<typename Type>
void DefaultVisitor<Type>::flush(){
  _buffer = "";
}
