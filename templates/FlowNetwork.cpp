
template<typename Type>
void FlowNetwork::_add_node_capacity(const GraphTypes::node_id & node, const GraphTypes::Flow & capacity)
{

  if(capacity != 0)
    _nodesCapacities[node] = capacity;
}

template<typename Type>
void FlowNetwork::_clean_capacity_map(std::map<Edge, GraphTypes::Flow> & capacityMap, const GraphTypes::node_id & node)
{
  for(std::map<Edge, GraphTypes::Flow>::iterator it = capacityMap.begin();
      it != capacityMap.end();
      ++it)
    {
      const GraphTypes::node_id & sourceNode = it->first.source();
      const GraphTypes::node_id & targetNode = it->first.target();

      if(sourceNode == node || targetNode == node)
	{
	  capacityMap.erase(it++);
	}
    }
}

template<typename Type>
void FlowNetwork::_add_edge_capacities(const GraphTypes::node_id & sourceNode,
				       const GraphTypes::node_id & targetNode,
				       const GraphTypes::Flow & minCapacity,
				       const GraphTypes::Flow & maxCapacity)
{
  if(_minCapacity != 0)
    _minCapacities[ Edge(sourceNode, targetNode) ] = minCapacity;

  _maxCapacities[ Edge(sourceNode, targetNode) ] = maxCapacity;
}

template<typename Type>
void FlowNetwork::_remove_edge_capacities(const GraphTypes::node_id & sourceNode,
					  const GraphTypes::node_id & targetNode)
{
  _minCapacities.erase( Edge(sourceNode, targetNode) );

  _maxCapacities.erase( Edge(sourceNode, targetNode) );
}

GraphTypes::node_id _find_free_node_id()
{
  GraphTypes::node_id id = * --flowGraph().nodes_end();

  while( flowGraph().has_node(id) ) ++id;

  return id;
}

template<typename Type>
FlowNetwork::FlowNetwork(const GraphTypes::node_id & sourceNode,
			 const GraphTypes::node_id & sinkNode,
			 const GraphTypes::NodeType & nodeType=GraphTypes::NOCONTENT)
  throw(GraphException::InvalidOperation)
{
  try
    {
      CanonicalNetwork(sourceNode, sinkNode, GraphTypes::WEIGHTED, nodeType);
    }

  catch(const GraphException::InvalidOperation&)
    {
      throw GraphTypes::InvalidOperation("Container graph : you need to map nodes to a content. Consider using FlowNetwork<Type>::FlowNetwork(const GraphTypes::node_id&, const Type&, const GraphTypes::node_id&, const Type&, const GraphTypes::NodeType&=GraphTypes::NOCONTENT).", __LINE__, __FILE__, "FlowNetwork<Type>::FlowNetwork(const GraphTypes::node_id&, const GraphTypes::node_id&, const GraphTypes::NodeType&=GraphTypes::NOCONTENT)");
    }
}

template<typename Type>
FlowNetwork::FlowNetwork(const GraphTypes::NodeType & nodeType=GraphTypes::NOCONTENT)
  throw(GraphException::InvalidOperation)
{
  try
    {
      CanonicalNetwork(GraphTypes::WEIGHTED, nodeType);
    }

  catch(const GraphException::InvalidOperation&)
    {
      throw GraphTypes::InvalidOperation("Container graph : you need to map nodes to a content. Consider using FlowNetwork<Type>::FlowNetwork(const Type&, const Type&, const GraphTypes::NodeType&=GraphTypes::NOCONTENT).", __LINE__, __FILE__, "FlowNetwork<Type>::FlowNetwork(const GraphTypes::NodeType&=GraphTypes::NOCONTENT)");
    }
}

template<typename Type>
FlowNetwork::FlowNetwork(const GraphTypes::node_id & sourceNode,
			 const Type & sourceNodeContent,
			 const GraphTypes::node_id & sinkNode,
			 const Type & sinkNodeContent,
			 const GraphTypes::NodeType & nodeType=GraphTypes::NOCONTENT)
  :CanonicalNetwork(sourceNode, sinkNode, GraphTypes::WEIGHTED, nodeType)
{}

template<typename Type>
FlowNetwork::FlowNetwork(const Type & sourceNodeContent,
			 const Type & sinkNodeContent,
			 const GraphTypes::NodeType & nodeType=GraphTypes::NOCONTENT)
  :CanonicalNetwork(sourceNode, sinkNode, GraphTypes::WEIGHTED, nodeType)
{}

template<typename Type>
FlowNetwork::FlowNetwork(const FlowNetwork & source)
{
  CanonicalNetwork::operator=(source);

  _minCapacities = source._minCapacities;
  _maxCapacities = source._maxCapacities;

  return *this;
}


template<typename Type>
void FlowNetwork::add_node(const GraphTypes::node_id & node) 
  throw(GraphException::InvalidOperation)
{
  try
    {
      flowGraph().add_node(node);
    }

  catch(const GraphException::InvalidOperation&)
    {
      throw GraphException::InvalidOperation("Container FlowNetwork : you need to map nodes to a content. Consider using FlowNetwork<Type>::add_node(const GraphTypes::node_id&, const Type&).", __LINE__, __FILE__, "FlowNetwork<Type>::add_node(const GraphTypes::node_id&)");
    }
}

template<typename Type>
void FlowNetwork::add_node(const GraphTypes::node_id & node,
			   const Type & content)
{
  flowGraph().add_node(node, content);
}

template<typename Type>
void FlowNetwork::add_node(const GraphTypes::node_id & node,
			   const Type & content,
			   const GraphTypes::Flow & capacity)
{
  this->add_node(node, content);

  _add_node_capacity(node, capacity);
}

template<typename Type>
void FlowNetwork::add_node(const GraphTypes::node_id & node,
			   const GraphTypes::Flow & capacity) throw(GraphException::InvalidOperation)
{
  FlowNetwork::add_node(node);

  _add_node_capacity(node, capacity);
}

template<typename Type>
void FlowNetwork::remove_node(const GraphTypes::node_id & node)
{
  flowGraph().remove_node(node);

  _nodesCapacities.erase(node);

  _clean_capacity_map(_minCapacity);
  _clean_capacity_map(_maxCapacity);
}

//add_flow without nodes capacities
template<typename Type>
void FlowNetwork::add_flow(const GraphTypes::node_id & sourceNode,
			   const GraphTypes::node_id & targetNode,
			   const GraphTypes::Flow & minCapacity,
			   const GraphTypes::Flow & flowValue,
			   const GraphTypes::Flow & maxCapacity)
  throw(GraphException::InvalidOperation)
{
  try
    {
      flowGraph().add_edge(sourceNode, targetNode, flowValue);

      _add_edge_capacities(sourceNode, targetNode, minCapacity, maxCapacity);
    }

  catch(const GraphException::InvalidOperation&)
    {
      throw GraphException::InvalidOperation("Given node IDs must already be in the FlowNetwork.\n Consider using:\n FlowNetwork<Type>::add_edge(const GraphTypes::node_id&, const Type&, const GraphTypes::node_id&, const Type&, const GraphTypes::Flow&, const GraphTypes::Flow&, const GraphTypes::Flow&).", __LINE__, __FILE__, "FlowNetwork<Type>::add_edge(const GraphTypes::node_id&, const GraphTypes::node_id&, const GraphTypes::Flow&, const GraphTypes::Flow&, const GraphTypes::Flow&)");
    }
}

template<typename Type>
void FlowNetwork::add_flow(const GraphTypes::node_id & sourceNode,
			   const GraphTypes::node_id & targetNode,
			   const GraphTypes::Flow & flowValue,
			   const GraphTypes::Flow & maxCapacity)
  throw(GraphException::InvalidOperation)
{
  add_flow(sourceNode, targetNode, 0, flowValue, maxCapacity);
}

template<typename Type>
void FlowNetwork::add_flow(const GraphTypes::node_id & sourceNode,
			   const Type & sourceNodeConent,
			   const GraphTypes::node_id & targetNode,
			   const Type & targetNodeConent,
			   const GraphTypes::Flow & minCapacity,
			   const GraphTypes::Flow & flowValue,
			   const GraphTypes::Flow & maxCapacity)
{
  flowGraph().add_edge(sourceNode, sourceNodeContent, targetNode, targetNodeContent, flowValue);

  _add_edge_capacities(sourceNode, targetNode, minCapacity, maxCapacity);
}

template<typename Type>
void FlowNetwork::add_flow(const GraphTypes::node_id & sourceNode,
			   const Type & sourceNodeConent,
			   const GraphTypes::node_id & targetNode,
			   const Type & targetNodeConent,
			   const GraphTypes::Flow & flowValue,
			   const GraphTypes::Flow & maxCapacity)
{
  add_flow(sourceNode, sourceNodeContent, targetNode, targetNodeContent, 0, flowValue, maxCapacity);
}

//add_flow with nodes capacities
template<typename Type>
void FlowNetwork::add_flow(const GraphTypes::node_id & sourceNode,
			   const GraphTypes::Fow & sourceNodeCapacity,
			   const GraphTypes::node_id & targetNode,
			   const GraphTypes::Fow & targetNodeCapacity,
			   const GraphTypes::Flow & minCapacity,
			   const GraphTypes::Flow & flowValue,
			   const GraphTypes::Flow & maxCapacity) throw(GraphException::InvalidOperation)
{
  add_flow(sourceNode, targetNode, minCapacity, flowValue, maxCapacity);

  _add_edge_capacities(sourceNode, targetNode, minCapacity, maxCapacity);
}

template<typename Type>
void FlowNetwork::add_flow(const GraphTypes::node_id & sourceNode,
			   const GraphTypes::Fow & sourceNodeCapacity,
			   const GraphTypes::node_id & targetNode,
			   const GraphTypes::Fow & targetNodeCapacity,
			   const GraphTypes::Flow & flowValue,
			   const GraphTypes::Flow & maxCapacity) throw(GraphException::InvalidOperation)
{
  add_flow(sourceNode, targetNode, flowValue, maxCapacity);

  _add_edge_capacities(sourceNode, targetNode, minCapacity, maxCapacity);
}

template<typename Type>
void FlowNetwork::add_flow(const GraphTypes::node_id & sourceNode,
			   const Type & sourceNodeConent,
			   const GraphTypes::Fow & sourceNodeCapacity,
			   const GraphTypes::node_id & targetNode,
			   const Type & targetNodeConent,
			   const GraphTypes::Fow & targetNodeCapacity,
			   const GraphTypes::Flow & minCapacity,
			   const GraphTypes::Flow & flowValue,
			   const GraphTypes::Flow & maxCapacity)
{
  add_flow(sourceNode, sourceNodeContent, targetNode, targetNodeContent, minCapacity, flowValue, maxCapacity);

  _add_edge_capacities(sourceNode, targetNode, minCapacity, maxCapacity);
}

template<typename Type>
void FlowNetwork::add_flow(const GraphTypes::node_id & sourceNode,
			   const Type & sourceNodeConent,
			   const GraphTypes::Fow & sourceNodeCapacity,
			   const GraphTypes::node_id & targetNode,
			   const Type & targetNodeConent,
			   const GraphTypes::Fow & targetNodeCapacity,
			   const GraphTypes::Flow & flowValue,
			   const GraphTypes::Flow & maxCapacity)
{
  add_flow(sourceNode, sourceNodeContent, targetNode, targetNodeContent, flowValue, maxCapacity);

  _add_edge_capacities(sourceNode, targetNode, minCapacity, maxCapacity);
}

template<typename Type>
void FlowNetwork::remove_flow(const GraphTypes::node_id & sourceNode,
			      const GraphTypes::node_id & targetNode)
{
  std::map<GraphTypes::node_id, GraphTypes::Flow>::iterator it;

  flowGraph().remove_edge(sourceNode, targetNode);

  _remove_edge_capacities(sourceNode, targetNode);
}

template<typename Type>
void FlowNetwork<Type>::setNodeCapacity(const GraphTypes::node_id & node,
					const GraphTypes::Flow & capacity)
{
  if( flowGraph().has_node(node) )
    {
      _nodesCapacities[node] = capacity;
    }

  else
    {
      throw GraphException::InvalidNodeID(node, "Invalid node ID.", __LINE__, __FILE__, "FlowNetwork<Type>::setNodeCapacity(const GraphTypes::node_id&, const GraphTypes::Flow&)");
    }
}

template<typename Type>
void FlowNetwork<Type>::setMinCapacity(const GraphTypes::node_id & sourceNode,
				       const GraphTypes::node_id & targetNode,
				       const GraphTypes::Flow & capacity)
{
  if( flowGraph().has_edge(sourceNode, targetNode) )
    {
      _minCapacities[ Edge(sourceNode,targetNode) ] = capacity;
    }

  else
    {
      throw GraphException::InvalidEdge(origin, target, "Given node_ids do not refer to a valid edge", __LINE__, __FILE__, "FlowNetwork<Type>::setMinCapacity(const GraphTypes::node_id&, const GraphTypes::node_id&, const GraphTypes::Flow&)");
    }
}

template<typename Type>
void FlowNetwork<Type>::setFlow(const GraphTypes::node_id & sourceNode,
				const GraphTypes::node_id & targetNode,
				const GraphTypes::Flow & flow)
{
  try
    {
      flowGraph.setCost(sourceNode,targetNode, capacity);
    }

  catch(const GraphException::InvalidEdge&)
    {
      throw GraphException::InvalidEdge(origin, target, "Given node_ids do not refer to a valid edge", __LINE__, __FILE__, "FlowNetwork<Type>::setFlow(const GraphTypes::node_id&, const GraphTypes::node_id&, const GraphTypes::Flow&)");
    }
}

template<typename Type>
void FlowNetwork<Type>::setMaxCapacity(const GraphTypes::node_id & sourceNode,
				       const GraphTypes::node_id & targetNode,
				       const GraphTypes::Flow & capacity)
{
  if( flowGraph().has_edge(sourceNode, targetNode) )
    {
      _maxCapacities[ Edge(sourceNode,targetNode) ] = capacity;
    }

  else
    {
      throw GraphException::InvalidEdge(origin, target, "Given node_ids do not refer to a valid edge", __LINE__, __FILE__, "FlowNetwork<Type>::setMaxCapacity(const GraphTypes::node_id&, const GraphTypes::node_id&, const GraphTypes::Flow&)");
    }
}

template<typename Type>
const GraphTypes::Flow & FlowNetwork<Type>::nodeCapacity(const GraphTypes::node_id & node)
  throw(GraphException::InvalidNodeID)
{
  if( flowGraph().has_node(node) )
    {
      std::map<GraphTypes::node_id, GraphTypes::Flow>::iterator it = _nodesCapacities.find(node);

      if( it != _nodesCapacities.end() )
	return *it;

      else
	return 0;
    }

  else
    {
      throw GraphException::InvalidNodeID(node, "Invalid node ID.", __LINE__, __FILE__, "FlowNetwork<Type>::nodeCapacity(const GraphTypes::node_id&)");
    }
}

template<typename Type>
GraphTypes::Flow FlowNetwork<Type>::contribution(const GraphTypes::node_id & node) 
  throw(GraphException::InvalidNodeID)
{
  if( flowGraph().has_node(node) )
    {
      GraphTypes::Flow contribution = 0;

      for(typename Graph<Type>::NodeIterator pred = flowGraph().predecessors_begin(node);
	  pred != flowGraph().predecessors_begin(node);
	  ++pred)
	{
	  contribution -= flow(*pred, node);
	}

      for(typename Graph<Type>::NodeIterator succ = flowGraph().succecessors_begin(node);
	  succ != flowGraph().succecessors_begin(node);
	  ++succ)
	{
	  contribution += flow(node, *succ);
	}

      return contribution;
    }

  else
    {
      throw GraphException::InvalidNodeID(node, "Invalid node ID.", __LINE__, __FILE__, "FlowNetwork<Type>::contribution(const GraphTypes::node_id&)");
    }
}

template<typename Type>
const GraphTypes::Flow & FlowNetwork<Type>::minCapacity(const GraphTypes::node_id & sourceNode,
							const GraphTypes::node_id & targetNode)
  throw(GraphException::InvalidEdge)
{
  if( flowGraph().has_edge(sourceNode, targetNode) )
    {
      std::map<Edge, GraphTypes::Flow>::iterator it = _minCapacities.find( Edge(sourceNode, targetNode) );

      if( it != _minCapacities.end() )
	return *it;

      else
	return 0;
    }

  else
    {
      throw GraphException::InvalidEdge(origin, target, "Given node_ids do not refer to a valid edge", __LINE__, __FILE__, "FlowNetwork<Type>::minCapacity(const GraphTypes::node_id&, const GraphTypes::node_id&)");
    }
}

template<typename Type>
const GraphTypes::Flow & FlowNetwork<Type>::flow(const GraphTypes::node_id & sourceNode,
						 const GraphTypes::node_id & targetNode)
  throw(GraphException::InvalidEdge)
{
  try
    {
      return (GraphTypes::Flow &) flowGraph().getCost(sourceNode, targetNode);
    }

  catch(const GraphException::InvalidEdge&)
    {
      throw GraphException::InvalidEdge(origin, target, "Given node_ids do not refer to a valid edge", __LINE__, __FILE__, "FlowNetwork<Type>::flow(const GraphTypes::node_id&, const GraphTypes::node_id&)");
    }
}

template<typename Type>
const GraphTypes::Flow & FlowNetwork<Type>::maxCapacity(const GraphTypes::node_id & sourceNode,
							const GraphTypes::node_id & targetNode)
  throw(GraphException::InvalidEdge)
{
  if( flowGraph().has_edge(sourceNode, targetNode) )
    {
      std::map<Edge, GraphTypes::Flow>::iterator it = _maxCapacities.find( Edge(sourceNode, targetNode) );

      if( it != _maxCapacities.end() )
	return *it;

      else
	return 0;
    }

  else
    {
      throw GraphException::InvalidEdge(origin, target, "Given node_ids do not refer to a valid edge", __LINE__, __FILE__, "FlowNetwork<Type>::maxCapacity(const GraphTypes::node_id&, const GraphTypes::node_id&)");
    }
}

//all min capacities to zero
template<typename Type>
void FlowNetwork::minCapacitiesToZero()
{
  for(std::map<Edge, GraphTypes::Flow>::iterator it = _minCapacities.begin();
      it != _minCapacities.end();
      ++it)
    {
      const GraphTypes::node_id & sourceNode = it->first.source();
      const GraphTypes::node_id & targetNode = it->first.target();
      const GraphTypes::Flow & minCapacity = it->second;

      _maxCapacity[Edge(sourceNode, targetNode)] -= minCapacity;

      _minCapacities.erase(it++);
    }
}

//No capacities on nodes
template<typename Type>
void FlowNetwork::nodesCapacitiesToFlowCapacities()
{
  for(std::map<GraphTypes::node_id, GraphTypes::Flow>::iterator it = _nodesCapacities.begin();
      it != _nodesCapacities.end();
      ++it)
    {
      const GraphTypes::node_id & sourceNode = it->first;
      GraphTypes::node_id targetNode = _find_free_node_id();
      const GraphTypes::Flow & capacity = it->second;

      if( flowGraph().is_container() )
	add_node( targetNode, flowGraph().get_node_content(sourceNode) );

      else
	add_node(targetNode);

      for(Graph<Type>::NodeIterator succ = flowGraph().successors_begin(sourceNode);
	  succ != flowGraph().successors_end(sourceNode);
	  ++succ)
	{
	  add_flow(targetNode, *succ, minCapacity(sourceNode, *succ), flow(sourceNode, *succ), maxCapacity(sourceNode, *succ) );

	  remove_flow(sourceNode, *succ);
	}

      add_flow(sourceNode, targetNode, 0, capacity);
    }
}

//only one source and only one sink
template<typename Type>
void FlowNetwork::uniqueContributors()
{
  for(Graph<Type>::NodeIterator node = flowGraph().nodes_begin();
      node != flowGraph().nodes_begin();
      ++node)
    {
      GraphTypes::Flow contribution = contribution(*node);
      if( contribution != 0 )
	{
	  if(contribution > 0)
	    add_flow(source(), *node, 0, contribution);

	  else
	    add_flow(*node, sink(), 0, 0-contribution);
	}
    }
}

template<typename Type>
void FlowNetwork<Type>::normalize()
{
  //all min capacities to zero
  minCapacitiesToZero();

  //No capacities on nodes
  nodesCapacitiesToFlowCapacity();

  //only one source and only one sink
  uniqueContributors();
}
