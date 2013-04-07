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

  // _network.normalize();
  // _nil_flow();

  _residualBuilder.build();
  _traverser.breadth_once( _network.source(), _noaction );

  Exporter<>::ToGraphviz(_network, Exporter<>::SetFnCapacities(_network), "bin/initial.graph");
  ::system("dot -Tpng bin/initial.graph -o bin/initial.png");

  while( _exists_path_to_sink() )
    {
      _extract_path_to_sink();

      delta = _min_residual_on_path();

      _change_flow(delta);

      std::cout << "path: ";
      for(std::list<GraphTypes::node_id>::iterator it=_path.begin(); it!=_path.end(); ++it)
	std::cout << *it << " ";
      std::cout << std::endl;

      std::cout << "delta = " << delta <<std::endl;

      Exporter<>::ToGraphviz(_traverser.traversingGraph(), "bin/traversing.graph");
      ::system("dot -Tpng bin/traversing.graph -o bin/traversing.png");
      Exporter<>::ToGraphviz(_residualBuilder.residualGraph(), "bin/residual.graph");
      ::system("dot -Tpng bin/residual.graph -o bin/residual.png");
      Exporter<>::ToGraphviz(_network, Exporter<>::SetFnCapacities(_network), "bin/modified.graph");
      ::system("dot -Tpng bin/modified.graph -o bin/modified.png");

      ::getchar();

      _residualBuilder.build();
      _traverser.breadth_once( _network.source(), _noaction );
    }
  Exporter<>::ToGraphviz(_residualBuilder.residualGraph(), "bin/lastResidual.graph");
  ::system("dot -Tpng bin/lastResidual.graph -o bin/lastResidual.png");
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
GraphTypes::Flow FordFulkerson<Content>::_min_residual_on_path()
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
	  std::cout << "Changing flow between " << *pred << ","<< *succ << " from " << oldFlow << " to " << newFlow << std::endl;

	  _network.setFlow(*pred, *succ, newFlow);
	  ++succ;
	}

    }
}
