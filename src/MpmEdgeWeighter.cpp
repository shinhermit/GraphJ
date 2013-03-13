#include "MpmEdgeWeighter.hpp"

using namespace GraphFunctor;

MpmEdgeWeighter::MpmEdgeWeighter(const GraphTypes::Planning::EdgeDirection & edgeDirection)
  :_edge_direction(edgeDirection)
{}

GraphTypes::Cost MpmEdgeWeighter::operator()(const Graph<MpmTask> & graph,
					     const GraphTypes::node_id & sourceNode,
					     const GraphTypes::node_id & targetNode)const
{
  if(_edge_direction == GraphTypes::Planning::DIRECT)
    return (GraphTypes::Cost) graph.get_node_content(sourceNode).duration();

  else 
    return (GraphTypes::Cost) graph.get_node_content(targetNode).duration();
}

const GraphTypes::Planning::EdgeDirection & MpmEdgeWeighter::edgeDirection()const
{
  return _edge_direction;
}

void MpmEdgeWeighter::SetEdgeDirection(const GraphTypes::Planning::EdgeDirection & edgeDirection)
{
  _edge_direction = edgeDirection;
}
