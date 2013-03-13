#ifndef _MpmEdgeWeighter
#define _MpmEdgeWeighter

#include "EdgeWeighter.hpp"
#include "MpmTask.hpp"

namespace GraphFunctor
{

  struct MpmEdgeWeighter : public EdgeWeighter<MpmTask>
  {
    GraphTypes::Cost operator()(const Graph<MpmTask> & graph,
				const GraphTypes::node_id & sourceNode,
				const GraphTypes::node_id & targetNode);
  };

};

#endif
