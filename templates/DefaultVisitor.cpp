template<typename Type>
DefaultVisitor<Type>::DefaultVisitor(GraphTypes::What what_to_treat):_what(what_to_treat), _buffer(""){}

template<typename Type>
DefaultVisitor<Type>::~DefaultVisitor(){}

template<typename Type>
void DefaultVisitor<Type>::treat(Graph<Type> graph, Node::node_id node){
  std::set<Node::node_id> successors;
  std::set<Node::node_id>::iterator it;
  std::ostringstream oss;

  if( _what == GraphTypes::CONTENTS ){
    successors = graph.successors(node);

    oss << graph.get_node_content(node) << ": ";

    for(it = successors.begin(); it != successors.end(); it++){
      oss << graph.get_node_content(*it) << ", ";
    }

    oss << std::endl;

    _buffer += oss.str();
  }
  else{
    if( graph.has_node(node) ){
      successors = graph.successors(node);

      oss << "n" << node << ": ";

      for(it = successors.begin(); it != successors.end(); it++){
	oss << "n" << *it << " ";
      }

      oss << std::endl;

      _buffer += oss.str();
    }
    else{
      oss << "0 n" << node << std::endl;
    }
  }
}

template<typename Type>
void DefaultVisitor<Type>::print_what(GraphTypes::What what){
  _what = what;
}

template<typename Type>
std::string DefaultVisitor<Type>::nodes_representation()const{
  return _buffer;
}

template<typename Type>
void DefaultVisitor<Type>::flush(){
  _buffer = "";
}
