template<typename Type>
GraphvizVisitor<Type>::GraphvizVisitor(): _buffer(""){}

template<typename Type>
GraphvizVisitor<Type>::~GraphvizVisitor(){}

template<typename Type>
void GraphvizVisitor<Type>::treat(Graph<Type> graph, Node::node_id node){
  std::set<Node::node_id> successors;
  std::set<Node::node_id>::iterator it;
  std::ostringstream oss;
  std::string linkSymbol;

  _visited.insert(node);


  successors = graph.successors(node);
    
  if( graph.is_directed() )
    linkSymbol = " -> " ;
  else
    linkSymbol = " -- " ;
    
  for(it = successors.begin(); it != successors.end(); it++){

    if( graph.is_directed() || (!graph.is_directed() && !_visited.count(*it)) ){
      oss << node << linkSymbol << *it;

      if( graph.is_weighted() )
	oss << " [label=\"" << graph.getCost(node, *it) << "\"]";

      oss << std::endl;
    }
  }

  _buffer += oss.str();
}

template<typename Type>
std::string GraphvizVisitor<Type>::nodes_representation()const{
  return _buffer;
}

template<typename Type>
void GraphvizVisitor<Type>::flush(){
  _buffer = "";
}
