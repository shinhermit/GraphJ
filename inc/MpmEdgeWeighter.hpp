#ifndef _MpmEdgeWeighter
#define _MpmEdgeWeighter

#include "EdgeWeighter.hpp"
#include "MpmTask.hpp"
#include "GraphTypes.hpp"

namespace GraphFunctor
{

  class MpmEdgeWeighter : public EdgeWeighter<MpmTask>
  {
  public:
    MpmEdgeWeighter(const GraphTypes::Planning::EdgeDirection & edgeDirection=GraphTypes::Planning::DIRECT);

    GraphTypes::Cost operator()(const Graph<MpmTask> & graph,
				const GraphTypes::node_id & sourceNode,
				const GraphTypes::node_id & targetNode)const;


    const GraphTypes::Planning::EdgeDirection & edgeDirection()const;

    void SetEdgeDirection(const GraphTypes::Planning::EdgeDirection & edgeDirection);

  private:
    GraphTypes::Planning::EdgeDirection _edge_direction;
  };

};

#endif
