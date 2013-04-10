template<typename Content>
FordFulkerson<Content>::FordFulkerson(FlowNetwork<Content> & network):
  _network(network),
  _residualBuilder(_network),
  _traverser( _residualBuilder.residualGraph() ),
  _violation(GraphTypes::FlowTypes::Violation::UNDEFINED)
{}

template<typename Content>
bool FordFulkerson<Content>::checkCompatibility()
{
  _violation = GraphTypes::FlowTypes::Violation::NOVIOLATION;

  _check_flow_conservation();
  _check_interval_neutrality();
  _check_flow_limits_compliance();

  return _compatible();
}

template<typename Content>
const GraphTypes::FlowTypes::Violation &  FordFulkerson<Content>::violation()const
{
  return _violation;
}

template<typename Content>
void FordFulkerson<Content>::maximizeFlow()  throw(GraphException::IncompatibleNetwork)
{
  GraphTypes::FlowTypes::Flow delta;
  bool compatible = checkCompatibility();

  if( !compatible )
    throw GraphException::IncompatibleNetwork(_violation, "FordFulkerson<Content>::maximizeFlow()");

  // _network.normalize();
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
void FordFulkerson<Content>::_check_flow_conservation()
{
  if(_network.contribution(_network.source()) + _network.contribution(_network.sink()) != 0)
    _violation = GraphTypes::FlowTypes::Violation::CONSERVATION_VIOLATION;

}

template<typename Content>
void FordFulkerson<Content>::_check_interval_neutrality()
{

  typename Graph<Content>::NodeIterator node = _network.flowGraph().nodes_begin();

  while( node != _network.flowGraph().nodes_end() && _compatible() )
    {
      if(*node != _network.source() && *node != _network.sink() && _network.contribution(*node) != 0)
	_violation = GraphTypes::FlowTypes::Violation::INTERNAL_NEUTRALITY_VIOLATION;

      ++node;
    }
}

template<typename Content>
void FordFulkerson<Content>::_check_flow_limits_compliance()
{

  GraphTypes::node_id source, target;
  typename Graph<Content>::EdgeIterator edge = _network.flowGraph().edges_begin();

 while( edge != _network.flowGraph().edges_end() && _compatible() )
    {
      source = edge->source();
      target = edge->target();

      if( _network.flow(source, target) < _network.minCapacity(source, target)
	  ||
	  _network.flow(source, target) > _network.maxCapacity(source, target) )
	_violation = GraphTypes::FlowTypes::Violation::FLOW_LIMITS_VIOLATION;
	
      ++edge;
    }
}

template<typename Content>
bool FordFulkerson<Content>::_compatible()const
{
  return _violation == GraphTypes::FlowTypes::Violation::NOVIOLATION;
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

  _traverser.breadth_once( _network.source(), _noaction );


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
GraphTypes::FlowTypes::Flow FordFulkerson<Content>::_min_residual_on_path()
{
  GraphTypes::Cost min;
  std::list<GraphTypes::node_id>::iterator pred, succ;
  const Graph<> & traversing = _traverser.traversingGraph();

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

  return (GraphTypes::FlowTypes::Flow) min;
}

template<typename Content>
void FordFulkerson<Content>::_change_flow(const GraphTypes::FlowTypes::Flow & delta)
{
  std::list<GraphTypes::node_id>::iterator pred, succ;
  GraphTypes::FlowTypes::Flow oldFlow, newFlow;
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

    }
}
