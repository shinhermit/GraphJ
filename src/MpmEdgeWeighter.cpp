#include "MpmEdgeWeighter.hpp"

using namespace GraphFunctor;

GraphTypes::Cost MpmEdgeWeighter::operator()(const Graph<MpmTask> & graph,
					     const GraphTypes::node_id & sourceNode,
					     const GraphTypes::node_id & targetNode)
{
  return (GraphTypes::Cost) graph.get_node_content(sourceNode).duration();
}
