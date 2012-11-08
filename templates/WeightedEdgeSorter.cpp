
template<typename Type>
WeightedEdgeSorter<Type>::WeightedEdgeSorter(){}

template<typename Type>
WeightedEdgeSorter<Type>::~WeightedEdgeSorter(){}

template<typename Type>
void WeightedEdgeSorter<Type>::treat(Graph<Type> graph, Node::node_id node){
  std::set<Node::node_id> successors;
  std::set<Node::node_id>::iterator it;
  GraphTypes::Cost cost;

  successors = graph.successors(node);

  if( successors.size() > 0 ){

    for(it = successors.begin(); it != successors.end(); it++){

      cost = graph.getCost(node, *it);

      if( graph.is_oriented() ){
	_edgeSet.insert( WeightedEdge(node, *it, cost) );
      }
      else{
	if( !graph.has_edge(*it, node) ){
	  _edgeSet.insert( WeightedEdge(node, *it, cost) );
	}
      }

    }

  }
}

template<typename Type>
std::set<WeightedEdge> WeightedEdgeSorter<Type>::getEdgeSet(){
  return _edgeSet;
}
