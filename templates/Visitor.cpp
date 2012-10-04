template<typename Type>
Visitor<Type>::Visitor(){}

template<typename Type>
Visitor<Type>::~Visitor(){}

template<typename Type>
void Visitor<Type>::treat(Graph<Type> graph, Node::node_id node){
  std::cout << "calling abstract Visitor<Type>::treat()";
}
