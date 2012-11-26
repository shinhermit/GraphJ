template<typename Type>
MathVisitor<Type>::MathVisitor():_S_buffer(""), _A_buffer(""), _C_buffer(""){}

template<typename Type>
MathVisitor<Type>::~MathVisitor(){}

template<typename Type>
void MathVisitor<Type>::treat(Graph<Type> & graph, Node::node_id node){
  std::set<Node::node_id> successors;
  std::set<Node::node_id>::iterator it;
  std::ostringstream oss1;
  std::ostringstream oss2;
  std::ostringstream oss3;

  _visited.insert(node);

  //Set S of vertices
  if( _S_buffer.size() > 0 )
    oss1 << ", ";

  oss1 << node;

  _S_buffer += oss1.str();

  //Sets A of edges, and C of weights
  successors = graph.successors(node);

  for(it = successors.begin(); it != successors.end(); it++){

    if( graph.is_directed() || (!graph.is_directed() && !_visited.count(*it)) ){

      oss2 << "(";
      oss3 << "coût(";

      oss2 << node << ", " << *it;
      oss3 << node << ", " << *it;
 
      oss2 << "), ";
      oss3 << ")=" << graph.getCost(node, *it) << "; ";
    }
  }

  _A_buffer += oss2.str();
  _C_buffer += oss3.str();
}

template<typename Type>
std::string MathVisitor<Type>::math_representation()const{
  std::ostringstream oss;

  oss << "S = {" << _S_buffer << "}" << std::endl;
  oss << "A = {" << _A_buffer << "}" << std::endl;
  oss << "Coûts:" << std::endl << _C_buffer;

  return oss.str();
}

template<typename Type>
void MathVisitor<Type>::flush(){
  _S_buffer = "";
  _A_buffer = "";
  _C_buffer = "";
}
