template<typename Type>
GraphvizVisitor<Type>::GraphvizVisitor(GraphTypes::What what_to_display):_what(what_to_display), _buffer(""){}

template<typename Type>
GraphvizVisitor<Type>::~GraphvizVisitor(){}

template<typename Type>
void GraphvizVisitor<Type>::treat(Graph<Type> graph, Node::node_id node){
  std::set<Node::node_id> successors;
  std::set<Node::node_id>::iterator it;
  std::ostringstream oss;

  _visited.insert(node);

  if(_what==GraphTypes::CONTENTS){
    successors = graph.successors(node);
    
    if( graph.is_directed() )
      oss << graph.get_node_content(node) << " -> {" ;
    else
      oss << graph.get_node_content(node) << " -- {" ;
    
    for(it = successors.begin(); it != successors.end(); it++){
	if( !graph.is_directed() && !_visited.count(*it) ){
	oss << graph.get_node_content(*it) << "; ";
      }
    }

    oss << "}" << std::endl;

    _buffer += oss.str();
  }
  
  else{
    
    if( graph.has_node(node) ){
      successors = graph.successors(node);
      if( graph.is_directed() )
	oss << node << " -> {";
      else
	oss << node << " -- {";
      
      for(it = successors.begin(); it != successors.end(); it++){
	if( !graph.is_directed() && !_visited.count(*it) ){
	  oss << *it << "; ";
	}
      }
      
      oss << "}" << std::endl;

      _buffer += oss.str();
    }
    else{
      std::cout << "0 n" << node << std::endl;
    }
  }
}

template<typename Type>
void GraphvizVisitor<Type>::display_what(GraphTypes::What what){
  _what = what;
}

template<typename Type>
std::string GraphvizVisitor<Type>::nodes_representation()const{
  return _buffer;
}

template<typename Type>
void GraphvizVisitor<Type>::flush(){
  _buffer = "";
}
