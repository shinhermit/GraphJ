#ifndef _FordFulkerson
#define _FordFulkerson

#include "FlowNetwork.hpp"
#include "Traverse.hpp"
#include "FnResidualBuilder.hpp"

template<typename Content=GraphTypes::Default>
class FordFulkerson
{
public:
  FordFulkerson(FlowNetwork<Content> & network);

  void maximize();

private:
  FlowNetwork<Content> & _network;
  FnResidualBuilder<Content> _builder;
  Traverse<Content> _traverser;
  std::list<GraphTypes::node_id> _path;

  void _nil_flow();

  bool _exists_path_to_sink()const;

  void _extract_path_to_sink();

  GraphTypes::Flow _min_residual_on_path();

  void _change_flow(const GraphTypes::Flow & delta);
};

template<typename Content>
FordFulkerson<Content>::FordFulkerson(const FlowNetwork<Content> & network):
  _network(network),
  _builder(_network),
  _traverser( _builder.residualGraph() )
{}

template<typename Content>
void FordFulkerson<Content>::maximize()
{
  GraphTypes::Flow delta;

  _nil_flow();

  _builder.build();
  _traverser.breadth_once( _network.source() );

  while( _exists_path_to_sink() )
    {
      _extract_path_to_sink();

      delta = _min_residual_on_path();

      _change_flow(delta);

      _builder.build();
      _traverser.breadth_once( _network.source() );
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
bool FordFulkerson<Content>::_exists_path_to_sink()const
{
  return _traverser.traversingGraph().has_node( _network.sink() );
}

template<typename Content>
void FordFulkerson<Content>::_extract_path_to_sink()
{
  GraphTypes::node_id currentNode, predecessor;
  const Graph<> & traversing = _traverser.traversingGraph();

  _path.clear();

  currentNode = _network.sink();
  _path.push_front(currentNode);

  while( traversing.predecessors_begin(currentNode) != traversing.predecessors_end(currentNode) )
    {
      currentNode = *predecessors_begin(currentNode);
      _path.push_front(currentNode);
    }
}

template<typename Content>
GraphTypes::Flow FordFulkerson<Content>::_min_residual_on_path()
{
  GraphTypes::Cost min;
  std::list<GraphTypes::node_id>::iterator pred, succ;

  min = 0;

  succ = _path.begin();
  while( succ != _path.end() )
    {
      pred = succ++ ;

      if( succ != _path.end() )
	{
	  GraphTypes::Cost cost = traversing.getCost(*pred, *succ);
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

  succ = _path.begin();
  while( succ != _path.end() )
    {
      pred
      ++succ;
    }
}

#endif
