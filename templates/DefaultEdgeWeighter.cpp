
using namespace GraphFunctor;

template<typename Type>
GraphTypes::Cost DefaultEdgeWeighter<Type>::operator()(const Graph<Type> & graph,
						       const GraphTypes::node_id & sourceNode,
						       const GraphTypes::node_id & targetNode)const
{
  if( graph.is_weighted() )
    return graph.getCost(sourceNode, targetNode);

  else
    return 1;
}
