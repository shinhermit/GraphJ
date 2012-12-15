template<typename Type>
PathBuilderVisitor<Type>::PathBuilderVisitor(){}

template<typename Type>
PathBuilderVisitor<Type>::~PathBuilderVisitor(){}

template<typename Type>
void PathBuilderVisitor<Type>::treat(Graph<> & graph, GraphTypes::node_id node)
{
  std::set<GraphTypes::node_id> predecessors;
  std::set<GraphTypes::node_id>::iterator it;

  predecessors = graph.predecessors(node);

  for(it = predecessors.begin(); it != predecessors.end(); it++){

    if( graph.is_weighted() )
      _path.add_edge( *it, node, graph.getCost(*it, node) );
    else
      _path.add_edge(*it, node);

  }
}

template<typename Type>
Graph<> PathBuilderVisitor<Type>::path()const
{
  return _path;
}
