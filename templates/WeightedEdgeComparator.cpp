using namespace GraphFunctor;

template<typename Type>
WeightedEdgeComparator<Type>::WeightedEdgeComparator(const Graph<Type> & graph):_graph(graph){}

template<typename Type>
bool WeightedEdgeComparator<Type>::operator()(const Edge & edge1,
					      const Edge & edge2)
{
  return _graph.getCost(edge1) < _graph.getCost(edge2);
}
