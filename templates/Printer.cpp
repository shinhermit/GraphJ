template<typename Type>
Printer<Type>::Printer(GraphTypes::What what_to_treat):_what(what_to_treat){}

template<typename Type>
Printer<Type>::~Printer(){}

template<typename Type>
void Printer<Type>::treat(Graph<Type> graph, Node::node_id node){
  std::set<Node::node_id> successors;
  std::set<Node::node_id>::iterator it;

  if( _what == GraphTypes::CONTENTS ){
    try{
      successors = graph.successors(node);

      std::cout << graph.get_node_content(node) << ": ";

      for(it = successors.begin(); it != successors.end(); it++){
	std::cout << graph.get_node_content(*it) << ", ";
      }

      std::cout << std::endl;
    }
    catch(std::string e ){
      std::cout << "0 n" << node << std::endl << e << std::endl;
    }
  }
  else{
    if( graph.has_node(node) ){
      successors = graph.successors(node);

      std::cout << "n" << node << ": ";

      for(it = successors.begin(); it != successors.end(); it++){
	std::cout << "n" << *it << " ";
      }

      std::cout << std::endl;
    }
    else{
      std::cout << "0 n" << node << std::endl;
    }
  }
}

template<typename Type>
void Printer<Type>::print_what(GraphTypes::What what){
  _what = what;
}
