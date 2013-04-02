#ifndef _FlowNetwork
#define _FlowNetwork

#include "GraphTypes.hpp"
#include "CanonicalNetwork.hpp"
#include "Edge.hpp"

template<typename Type=GraphTypes::Default>
class FlowNetwork : public CanonicalNetwork<Type>
{
public:
  FlowNetwork(const GraphTypes::node_id & sourceNode,
	      const GraphTypes::node_id & sinkNode,
	      const GraphTypes::NodeType & nodeType=GraphTypes::NOCONTENT)
    throw(GraphException::InvalidOperation);

  FlowNetwork(const GraphTypes::NodeType & nodeType=GraphTypes::NOCONTENT)
    throw(GraphException::InvalidOperation);

  FlowNetwork(const GraphTypes::node_id & sourceNode,
	      const Type & sourceNodeContent,
	      const GraphTypes::node_id & sinkNode,
	      const Type & sinkNodeContent,
	      const GraphTypes::NodeType & nodeType=GraphTypes::NOCONTENT);

  FlowNetwork(const Type & sourceNodeContent,
	      const Type & sinkNodeContent,
	      const GraphTypes::NodeType & nodeType=GraphTypes::NOCONTENT);

  FlowNetwork(const FlowNetwork & source);

  FlowNetwork & operator=(const FlowNetwork & source);

  void add_node(const GraphTypes::node_id & node,
		const Type & content);

  void add_node(const GraphTypes::node_id & node) throw(GraphException::InvalidOperation);

  void add_node(const GraphTypes::node_id & node,
		const Type & content,
		const GraphTypes::Flow & capacity);

  void add_node(const GraphTypes::node_id & node,
		const GraphTypes::Flow & capacity) throw(GraphException::InvalidOperation);

  void remove_node(const GraphTypes::node_id & node);

  //add_flow without node Capacity
  void add_flow(const GraphTypes::node_id & sourceNode,
		const GraphTypes::node_id & targetNode,
		const GraphTypes::Flow & minCapacity,
		const GraphTypes::Flow & flowValue,
		const GraphTypes::Flow & maxCapacity) throw(GraphException::InvalidOperation);

  void add_flow(const GraphTypes::node_id & sourceNode,
		const GraphTypes::node_id & targetNode,
		const GraphTypes::Flow & flowValue,
		const GraphTypes::Flow & maxCapacity) throw(GraphException::InvalidOperation);

  void add_flow(const GraphTypes::node_id & sourceNode,
		const Type & sourceNodeConent,
		const GraphTypes::node_id & targetNode,
		const Type & targetNodeConent,
		const GraphTypes::Flow & minCapacity,
		const GraphTypes::Flow & flowValue,
		const GraphTypes::Flow & maxCapacity);

  void add_flow(const GraphTypes::node_id & sourceNode,
		const Type & sourceNodeConent,
		const GraphTypes::node_id & targetNode,
		const Type & targetNodeConent,
		const GraphTypes::Flow & flowValue,
		const GraphTypes::Flow & maxCapacity);

  //add_flow with node Capacities
  void add_flow(const GraphTypes::node_id & sourceNode,
		const GraphTypes::Flow & sourceNodeCapacity,
		const GraphTypes::node_id & targetNode,
		const GraphTypes::Flow & targetNodeCapacity,
		const GraphTypes::Flow & minCapacity,
		const GraphTypes::Flow & flowValue,
		const GraphTypes::Flow & maxCapacity) throw(GraphException::InvalidOperation);

  void add_flow(const GraphTypes::node_id & sourceNode,
		const GraphTypes::Flow & sourceNodeCapacity,
		const GraphTypes::node_id & targetNode,
		const GraphTypes::Flow & targetNodeCapacity,
		const GraphTypes::Flow & flowValue,
		const GraphTypes::Flow & maxCapacity) throw(GraphException::InvalidOperation);

  void add_flow(const GraphTypes::node_id & sourceNode,
		const Type & sourceNodeConent,
		const GraphTypes::Flow & sourceNodeCapacity,
		const GraphTypes::node_id & targetNode,
		const Type & targetNodeConent,
		const GraphTypes::Flow & targetNodeCapacity,
		const GraphTypes::Flow & minCapacity,
		const GraphTypes::Flow & flowValue,
		const GraphTypes::Flow & maxCapacity);

  void add_flow(const GraphTypes::node_id & sourceNode,
		const Type & sourceNodeConent,
		const GraphTypes::Flow & sourceNodeCapacity,
		const GraphTypes::node_id & targetNode,
		const Type & targetNodeConent,
		const GraphTypes::Flow & targetNodeCapacity,
		const GraphTypes::Flow & flowValue,
		const GraphTypes::Flow & maxCapacity);

  void remove_flow(const GraphTypes::node_id & sourceNode,
		   const GraphTypes::node_id & targetNode);

  void setNodeCapacity(const GraphTypes::node_id & node,
		       const GraphTypes::Flow & capacity)
    throw(GraphException::InvalidNodeID);

  void setMinCapacity(const GraphTypes::node_id & sourceNode,
		      const GraphTypes::node_id & targetNode,
		      const GraphTypes::Flow & capacity)
    throw(GraphException::InvalidEdge);

  void setFlow(const GraphTypes::node_id & sourceNode,
	       const GraphTypes::node_id & targetNode,
	       const GraphTypes::Flow & flow)
    throw(GraphException::InvalidEdge);

  void setMaxCapacity(const GraphTypes::node_id & sourceNode,
		      const GraphTypes::node_id & targetNode,
		      const GraphTypes::Flow & capacity)
    throw(GraphException::InvalidEdge);

  const GraphTypes::Flow & nodeCapacity(const GraphTypes::node_id & node)
    throw(GraphException::InvalidNodeID);

  GraphTypes::Flow contribution(const GraphTypes::node_id & node)
    throw(GraphException::InvalidNodeID);

  GraphTypes::Flow minCapacity(const GraphTypes::node_id & sourceNode,
				       const GraphTypes::node_id & targetNode) const
    throw(GraphException::InvalidEdge);

  GraphTypes::Flow flow(const GraphTypes::node_id & sourceNode,
				const GraphTypes::node_id & targetNode) const
    throw(GraphException::InvalidEdge);

  GraphTypes::Flow maxCapacity(const GraphTypes::node_id & sourceNode,
				       const GraphTypes::node_id & targetNode) const
    throw(GraphException::InvalidEdge);

  //all min capacities to zero
  void minCapacitiesToZero();

  //No capacities on nodes
  void nodesCapacitiesToFlowCapacities();

  //only one source and only one sink
  void uniqueContributors();

  void normalize();

private:
  std::map<Edge, GraphTypes::Flow> _minCapacities; //only minCap > 0 are stored
  std::map<Edge, GraphTypes::Flow> _maxCapacities;
  std::map<GraphTypes::node_id, GraphTypes::Flow> _nodesCapacities;  //only nodeCap > 0 are stored

  void _add_node_capacity(const GraphTypes::node_id & node,
			  const GraphTypes::Flow & capacity);

  void _clean_capacity_map(std::map<Edge, GraphTypes::Flow> & capacityMap, const GraphTypes::node_id & node);

  void _add_edge_capacities(const GraphTypes::node_id & sourceNode,
			    const GraphTypes::node_id & targetNode,
			    const GraphTypes::Flow & minCapacity,
			    const GraphTypes::Flow & maxCapacity);

  void _remove_edge_capacities(const GraphTypes::node_id & sourceNode,
			       const GraphTypes::node_id & targetNode);

  GraphTypes::node_id _find_free_node_id();
};

#include "FlowNetwork.cpp"

#endif
