template<typename Content>
FordFulkerson<Content>::FordFulkerson(FlowNetwork<Content> & network):
  _network(network),
  _residualBuilder(_network),
  _traverser( _residualBuilder.residualGraph() )
{}

template<typename Content>
void FordFulkerson<Content>::maximizeFlow()
{
  GraphTypes::Flow delta;

  _nil_flow();

  _residualBuilder.build();
  _traverser.breadth_once( _network.source(), _noaction );

  while( _exists_path_to_sink() )
    {
      _extract_path_to_sink();

      delta = _min_residual_on_path();

      _change_flow(delta);

      _residualBuilder.build();
      _traverser.breadth_once( _network.source(), _noaction );
    }
}

template<typename Content>
void FordFulkerson<Content>::_nil_flow()
{
  for(typename Graph<Content>::EdgeIterator edge = _network.flowGraph().edges_begin();
      edge != _network.flowGraph().edges_end();
      ++edge)
    {
      _network.setFlow(edge->source(), edge->target(), 0);
    }
}

template<typename Content>
bool FordFulkerson<Content>::_exists_path_to_sink()
{
  return _traverser.traversingGraph().has_node( _network.sink() );
}

template<typename Content>
void FordFulkerson<Content>::_extract_path_to_sink()
{
  GraphTypes::node_id currentNode, predecessor;
  const Graph<> & traversing = _traverser.traversingGraph();

  if( _path.size() > 0 )
    _path.clear();

  currentNode = _network.sink();
  _path.push_front(currentNode);

  while( traversing.predecessors_begin(currentNode) != traversing.predecessors_end(currentNode) )
    {
      currentNode = *traversing.predecessors_begin(currentNode);
      _path.push_front(currentNode);
    }
}

template<typename Content>
GraphTypes::Flow FordFulkerson<Content>::_min_residual_on_path()
{
  GraphTypes::Cost min;
  std::list<GraphTypes::node_id>::iterator pred, succ;
  const Graph<> & traversing = _traverser.traversingGraph();

  if( _path.begin() != _path.end() && ++_path.begin() != _path.end() )
    min = ::abs( traversing.getCost(*_path.begin(), *++_path.begin()) );

  succ = _path.begin();
  while( succ != _path.end() )
    {
      pred = succ++ ;

      if( succ != _path.end() )
	{
	  GraphTypes::Cost cost = ::abs( traversing.getCost(*pred, *succ) );
	  if(cost < min)
	    min = cost;

	  ++succ;
	}
    }

  return (GraphTypes::Flow) min;
}

template<typename Content>
void FordFulkerson<Content>::_change_flow(const GraphTypes::Flow & delta)
{
  std::list<GraphTypes::node_id>::iterator pred, succ;
  GraphTypes::Flow oldFlow, newFlow;
  GraphTypes::Cost residual;

  succ = _path.begin();
  while( succ != _path.end() )
    {
      pred = succ++;

      if( succ != _path.end() )
	{
	  oldFlow = _network.flow(*pred, *succ);

	  residual = _residualBuilder.residualGraph().getCost(*pred, *succ);

	  newFlow = oldFlow + ( residual / ::abs(residual) ) * delta;

	  _network.setFlow(*pred, *succ, newFlow);
	}

      ++succ;
    }
}
