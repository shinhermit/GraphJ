template<typename Type>
FnResidualBuilder<Type>::FnResidualBuilder(const FlowNetwork<Type> & network):
  _network(network),
  _residualGraph(GraphTypes::DIRECTED, GraphTypes::WEIGHTED, GraphTypes::NOCONTENT)
{}

template<typename Type>
void FnResidualBuilder<Type>::_copy_nodes()
{
  for(typename Graph<Type>::NodeIterator node = _network.flowGraph().nodes_begin();
      node != _network.flowGraph().nodes_end();
      ++node)
    {
      _residualGraph.add_node(*node);
    }
}

template<typename Type>
void FnResidualBuilder<Type>::build()
{
  GraphTypes::Flow directResidual, inverseResidual;

  _copy_nodes();

  for(typename Graph<Type>::EdgeIterator edge = _network.flowGraph().edges_begin();
      edge != _network.flowGraph().edges_end();
      ++edge)
    {
      const GraphTypes::node_id & source = edge->source();
      const GraphTypes::node_id & target = edge->target();

      directResidual = _network.maxCapacity(source, target) - _network.flow(source, target);

      inverseResidual = _network.flow(source, target) - _network.minCapacity(source, target);

      if(directResidual > 0)
	_residualGraph.add_edge(source, target, directResidual);

      if(inverseResidual > 0)
	_residualGraph.add_edge(target, source, inverseResidual);
    }
}

template<typename Type>
const Graph<> & FnResidualBuilder<Type>::residualGraph()
{
  return _residualGraph;
}
