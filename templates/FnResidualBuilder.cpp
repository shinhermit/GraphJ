template<typename Type>
FnResidualBuilder<Type>::FnResidualBuilder(const FlowNetwork<Type> & network):
  _network(network),
  _residualGraph(GraphTypes::DIRECTED, GraphTypes::WEIGHTED, GraphTypes::NOCONTENT)
{}

template<typename Type>
void FnResidualBuilder<Type>::build()
{
  GraphTypes::FlowTypes::Flow directResidual, inverseResidual;

  if(_residualGraph.nodes_size() != 0)
    _residualGraph = Graph<>(GraphTypes::DIRECTED, GraphTypes::WEIGHTED, GraphTypes::NOCONTENT);

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
	_residualGraph.add_edge(target, source, 0-inverseResidual); //le signe indique le sens de parcours
    }
}

template<typename Type>
Graph<> & FnResidualBuilder<Type>::residualGraph()
{
  return _residualGraph;
}
