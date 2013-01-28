using namespace GraphFunctor;

template<typename Type>
GreaterDegreeComparator<Type>::GreaterDegreeComparator(const Graph<Type> & graph):_graph(graph){}

template<typename Type>
bool GreaterDegreeComparator<Type>::operator()(const GraphTypes::node_id & node1,
					       const GraphTypes::node_id & node2)
{
  return _graph.degree(node1) > _graph.degree(node2);
}

