
template<typename Type>
void FlowNetwork<Type>::_add_node_capacity(const GraphTypes::node_id & node, const GraphTypes::FlowTypes::Flow & capacity)
{

  if(capacity != 0)
    _nodesCapacities[node] = capacity;
}

template<typename Type>
void FlowNetwork<Type>::_clean_capacity_map(std::map<Edge, GraphTypes::FlowTypes::Flow> & capacityMap, const GraphTypes::node_id & node)
{
  for(std::map<Edge, GraphTypes::FlowTypes::Flow>::iterator it = capacityMap.begin();
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
void FlowNetwork<Type>::_add_edge_capacities(const GraphTypes::node_id & sourceNode,
				       const GraphTypes::node_id & targetNode,
				       const GraphTypes::FlowTypes::Flow & minCapacity,
				       const GraphTypes::FlowTypes::Flow & maxCapacity)
{
  if(minCapacity != 0)
    _minCapacities[ Edge(sourceNode, targetNode) ] = minCapacity;

  _maxCapacities[ Edge(sourceNode, targetNode) ] = maxCapacity;
}

template<typename Type>
void FlowNetwork<Type>::_remove_edge_capacities(const GraphTypes::node_id & sourceNode,
					  const GraphTypes::node_id & targetNode)
{
  _minCapacities.erase( Edge(sourceNode, targetNode) );

  _maxCapacities.erase( Edge(sourceNode, targetNode) );
}

template<typename Type>
GraphTypes::node_id FlowNetwork<Type>::_find_free_node_id()
{
  GraphTypes::node_id id = * --this->flowGraph().nodes_end();

  while( this->flowGraph().has_node(id) ) ++id;

  return id;
}

template<typename Type>
FlowNetwork<Type>::FlowNetwork(const GraphTypes::node_id & sourceNode,
			 const GraphTypes::node_id & sinkNode,
			 const GraphTypes::NodeType & nodeType)
  throw(GraphException::InvalidOperation)
  :CanonicalNetwork<Type>(sourceNode, sinkNode, GraphTypes::WEIGHTED, nodeType)
{}

template<typename Type>
FlowNetwork<Type>::FlowNetwork(const GraphTypes::NodeType & nodeType)
  throw(GraphException::InvalidOperation)
 :CanonicalNetwork<Type>(GraphTypes::WEIGHTED, nodeType)
{}

template<typename Type>
FlowNetwork<Type>::FlowNetwork(const GraphTypes::node_id & sourceNode,
			 const Type & sourceNodeContent,
			 const GraphTypes::node_id & sinkNode,
			 const Type & sinkNodeContent,
			 const GraphTypes::NodeType & nodeType)
  :CanonicalNetwork<Type>(sourceNode, sourceNodeContent, sinkNode, sinkNodeContent, GraphTypes::WEIGHTED, nodeType)
{}

template<typename Type>
FlowNetwork<Type>::FlowNetwork(const Type & sourceNodeContent,
			 const Type & sinkNodeContent,
			 const GraphTypes::NodeType & nodeType)
  :CanonicalNetwork<Type>(sourceNodeContent, sinkNodeContent, GraphTypes::WEIGHTED, nodeType)
{}

template<typename Type>
FlowNetwork<Type>::FlowNetwork(const FlowNetwork & source)
  :CanonicalNetwork<Type>(source),
   _minCapacities(source._minCapacities),
   _maxCapacities(source._maxCapacities),
   _nodesCapacities(source._nodesCapacities)
{
}

template<typename Type>
FlowNetwork<Type> & FlowNetwork<Type>::operator=(const FlowNetwork & source)
{
  CanonicalNetwork<Type>::operator=(source);

  _minCapacities = source._minCapacities;
  _maxCapacities = source._maxCapacities;
  _nodesCapacities = source._nodesCapacities;

  return *this;
}


template<typename Type>
void FlowNetwork<Type>::add_node(const GraphTypes::node_id & node) 
  throw(GraphException::InvalidOperation)
{
  try
    {
      this->flowGraph().add_node(node);
    }

  catch(const GraphException::InvalidOperation&)
    {
      throw GraphException::InvalidOperation("Container FlowNetwork : you need to map nodes to a content. Consider using FlowNetwork<Type>::add_node(const GraphTypes::node_id&, const Type&).", __LINE__, __FILE__, "FlowNetwork<Type>::add_node(const GraphTypes::node_id&)");
    }
}

template<typename Type>
void FlowNetwork<Type>::add_node(const GraphTypes::node_id & node,
			   const Type & content)
{
  this->flowGraph().add_node(node, content);
}

template<typename Type>
void FlowNetwork<Type>::add_node(const GraphTypes::node_id & node,
			   const Type & content,
			   const GraphTypes::FlowTypes::Flow & capacity)
{
  this->add_node(node, content);

  _add_node_capacity(node, capacity);
}

template<typename Type>
void FlowNetwork<Type>::add_node(const GraphTypes::node_id & node,
			   const GraphTypes::FlowTypes::Flow & capacity) throw(GraphException::InvalidOperation)
{
  FlowNetwork<Type>::add_node(node);

  _add_node_capacity(node, capacity);
}

template<typename Type>
void FlowNetwork<Type>::remove_node(const GraphTypes::node_id & node)
{
  this->flowGraph().remove_node(node);

  _nodesCapacities.erase(node);

  _clean_capacity_map(_minCapacities);
  _clean_capacity_map(_maxCapacities);
}

//add_flow without nodes capacities
template<typename Type>
void FlowNetwork<Type>::add_flow(const GraphTypes::node_id & sourceNode,
			   const GraphTypes::node_id & targetNode,
			   const GraphTypes::FlowTypes::Flow & minCapacity,
			   const GraphTypes::FlowTypes::Flow & flowValue,
			   const GraphTypes::FlowTypes::Flow & maxCapacity)
  throw(GraphException::InvalidOperation)
{
  try
    {
      this->flowGraph().add_edge(sourceNode, targetNode, flowValue);

      _add_edge_capacities(sourceNode, targetNode, minCapacity, maxCapacity);
    }

  catch(const GraphException::InvalidOperation&)
    {
      throw GraphException::InvalidOperation("Given node IDs must already be in the FlowNetwork.\n Consider using:\n FlowNetwork<Type>::add_edge(const GraphTypes::node_id&, const Type&, const GraphTypes::node_id&, const Type&, const GraphTypes::FlowTypes::Flow&, const GraphTypes::FlowTypes::Flow&, const GraphTypes::FlowTypes::Flow&).", __LINE__, __FILE__, "FlowNetwork<Type>::add_edge(const GraphTypes::node_id&, const GraphTypes::node_id&, const GraphTypes::FlowTypes::Flow&, const GraphTypes::FlowTypes::Flow&, const GraphTypes::FlowTypes::Flow&)");
    }
}

template<typename Type>
void FlowNetwork<Type>::add_flow(const GraphTypes::node_id & sourceNode,
			   const GraphTypes::node_id & targetNode,
			   const GraphTypes::FlowTypes::Flow & flowValue,
			   const GraphTypes::FlowTypes::Flow & maxCapacity)
  throw(GraphException::InvalidOperation)
{
  add_flow(sourceNode, targetNode, 0, flowValue, maxCapacity);
}

template<typename Type>
void FlowNetwork<Type>::add_flow(const GraphTypes::node_id & sourceNode,
			   const Type & sourceNodeContent,
			   const GraphTypes::node_id & targetNode,
			   const Type & targetNodeContent,
			   const GraphTypes::FlowTypes::Flow & minCapacity,
			   const GraphTypes::FlowTypes::Flow & flowValue,
			   const GraphTypes::FlowTypes::Flow & maxCapacity)
{
  this->flowGraph().add_edge(sourceNode, sourceNodeContent, targetNode, targetNodeContent, flowValue);

  _add_edge_capacities(sourceNode, targetNode, minCapacity, maxCapacity);
}

template<typename Type>
void FlowNetwork<Type>::add_flow(const GraphTypes::node_id & sourceNode,
			   const Type & sourceNodeContent,
			   const GraphTypes::node_id & targetNode,
			   const Type & targetNodeContent,
			   const GraphTypes::FlowTypes::Flow & flowValue,
			   const GraphTypes::FlowTypes::Flow & maxCapacity)
{
  add_flow(sourceNode, sourceNodeContent, targetNode, targetNodeContent, 0, flowValue, maxCapacity);
}

//add_flow with nodes capacities
template<typename Type>
void FlowNetwork<Type>::add_flow(const GraphTypes::node_id & sourceNode,
			   const GraphTypes::FlowTypes::Flow & sourceNodeCapacity,
			   const GraphTypes::node_id & targetNode,
			   const GraphTypes::FlowTypes::Flow & targetNodeCapacity,
			   const GraphTypes::FlowTypes::Flow & minCapacity,
			   const GraphTypes::FlowTypes::Flow & flowValue,
			   const GraphTypes::FlowTypes::Flow & maxCapacity) throw(GraphException::InvalidOperation)
{
  add_flow(sourceNode, targetNode, minCapacity, flowValue, maxCapacity);

  _add_edge_capacities(sourceNode, targetNode, minCapacity, maxCapacity);
}

template<typename Type>
void FlowNetwork<Type>::add_flow(const GraphTypes::node_id & sourceNode,
			   const GraphTypes::FlowTypes::Flow & sourceNodeCapacity,
			   const GraphTypes::node_id & targetNode,
			   const GraphTypes::FlowTypes::Flow & targetNodeCapacity,
			   const GraphTypes::FlowTypes::Flow & flowValue,
			   const GraphTypes::FlowTypes::Flow & maxCapacity) throw(GraphException::InvalidOperation)
{
  add_flow(sourceNode, targetNode, flowValue, maxCapacity);

  _add_edge_capacities(sourceNode, targetNode, minCapacity, maxCapacity);
}

template<typename Type>
void FlowNetwork<Type>::add_flow(const GraphTypes::node_id & sourceNode,
			   const Type & sourceNodeContent,
			   const GraphTypes::FlowTypes::Flow & sourceNodeCapacity,
			   const GraphTypes::node_id & targetNode,
			   const Type & targetNodeContent,
			   const GraphTypes::FlowTypes::Flow & targetNodeCapacity,
			   const GraphTypes::FlowTypes::Flow & minCapacity,
			   const GraphTypes::FlowTypes::Flow & flowValue,
			   const GraphTypes::FlowTypes::Flow & maxCapacity)
{
  add_flow(sourceNode, sourceNodeContent, targetNode, targetNodeContent, minCapacity, flowValue, maxCapacity);

  _add_edge_capacities(sourceNode, targetNode, minCapacity, maxCapacity);
}

template<typename Type>
void FlowNetwork<Type>::add_flow(const GraphTypes::node_id & sourceNode,
			   const Type & sourceNodeContent,
			   const GraphTypes::FlowTypes::Flow & sourceNodeCapacity,
			   const GraphTypes::node_id & targetNode,
			   const Type & targetNodeContent,
			   const GraphTypes::FlowTypes::Flow & targetNodeCapacity,
			   const GraphTypes::FlowTypes::Flow & flowValue,
			   const GraphTypes::FlowTypes::Flow & maxCapacity)
{
  add_flow(sourceNode, sourceNodeContent, targetNode, targetNodeContent, flowValue, maxCapacity);

  _add_edge_capacities(sourceNode, targetNode, minCapacity, maxCapacity);
}

template<typename Type>
void FlowNetwork<Type>::remove_flow(const GraphTypes::node_id & sourceNode,
			      const GraphTypes::node_id & targetNode)
{
  std::map<GraphTypes::node_id, GraphTypes::FlowTypes::Flow>::iterator it;

  this->flowGraph().remove_edge(sourceNode, targetNode);

  _remove_edge_capacities(sourceNode, targetNode);
}

template<typename Type>
void FlowNetwork<Type>::setNodeCapacity(const GraphTypes::node_id & node,
					const GraphTypes::FlowTypes::Flow & capacity)
    throw(GraphException::InvalidNodeID)
{
  if( this->flowGraph().has_node(node) )
    {
      _nodesCapacities[node] = capacity;
    }

  else
    {
      throw GraphException::InvalidNodeID(node, "Invalid node ID.", __LINE__, __FILE__, "FlowNetwork<Type>::setNodeCapacity(const GraphTypes::node_id&, const GraphTypes::FlowTypes::Flow&)");
    }
}

template<typename Type>
void FlowNetwork<Type>::setMinCapacity(const GraphTypes::node_id & sourceNode,
				       const GraphTypes::node_id & targetNode,
				       const GraphTypes::FlowTypes::Flow & capacity)
  throw(GraphException::InvalidEdge)
{
  if( this->flowGraph().has_edge(sourceNode, targetNode) )
    {
      _minCapacities[ Edge(sourceNode,targetNode) ] = capacity;
    }

  else
    {
      throw GraphException::InvalidEdge(sourceNode, targetNode, "Given node_ids do not refer to a valid edge", __LINE__, __FILE__, "FlowNetwork<Type>::setMinCapacity(const GraphTypes::node_id&, const GraphTypes::node_id&, const GraphTypes::FlowTypes::Flow&)");
    }
}

template<typename Type>
void FlowNetwork<Type>::setFlow(const GraphTypes::node_id & sourceNode,
				const GraphTypes::node_id & targetNode,
				const GraphTypes::FlowTypes::Flow & flow)
  throw(GraphException::InvalidEdge)
{
  try
    {
      this->flowGraph().setCost(sourceNode,targetNode, flow);
    }

  catch(const GraphException::InvalidEdge&)
    {
      throw GraphException::InvalidEdge(sourceNode, targetNode, "Given node_ids do not refer to a valid edge", __LINE__, __FILE__, "FlowNetwork<Type>::setFlow(const GraphTypes::node_id&, const GraphTypes::node_id&, const GraphTypes::FlowTypes::Flow&)");
    }
}

template<typename Type>
void FlowNetwork<Type>::setMaxCapacity(const GraphTypes::node_id & sourceNode,
				       const GraphTypes::node_id & targetNode,
				       const GraphTypes::FlowTypes::Flow & capacity)
  throw(GraphException::InvalidEdge)
{
  if( this->flowGraph().has_edge(sourceNode, targetNode) )
    {
      _maxCapacities[ Edge(sourceNode,targetNode) ] = capacity;
    }

  else
    {
      throw GraphException::InvalidEdge(sourceNode, targetNode, "Given node_ids do not refer to a valid edge", __LINE__, __FILE__, "FlowNetwork<Type>::setMaxCapacity(const GraphTypes::node_id&, const GraphTypes::node_id&, const GraphTypes::FlowTypes::Flow&)");
    }
}

template<typename Type>
const GraphTypes::FlowTypes::Flow & FlowNetwork<Type>::nodeCapacity(const GraphTypes::node_id & node)
  throw(GraphException::InvalidNodeID)
{
  if( this->flowGraph().has_node(node) )
    {
      std::map<GraphTypes::node_id, GraphTypes::FlowTypes::Flow>::iterator it = _nodesCapacities.find(node);

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
GraphTypes::FlowTypes::Flow FlowNetwork<Type>::contribution(const GraphTypes::node_id & node) 
  throw(GraphException::InvalidNodeID)
{
  if( this->flowGraph().has_node(node) )
    {
      GraphTypes::FlowTypes::Flow contribution = 0;

      for(typename Graph<Type>::NodeIterator pred = this->flowGraph().predecessors_begin(node);
	  pred != this->flowGraph().predecessors_begin(node);
	  ++pred)
	{
	  contribution -= flow(*pred, node);
	}

      for(typename Graph<Type>::NodeIterator succ = this->flowGraph().successors_begin(node);
	  succ != this->flowGraph().successors_begin(node);
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
GraphTypes::FlowTypes::Flow FlowNetwork<Type>::minCapacity(const GraphTypes::node_id & sourceNode,
							const GraphTypes::node_id & targetNode) const
  throw(GraphException::InvalidEdge)
{
  if( this->flowGraph().has_edge(sourceNode, targetNode) )
    {
      std::map<Edge, GraphTypes::FlowTypes::Flow>::const_iterator it = _minCapacities.find( Edge(sourceNode, targetNode) );

      if( it != _minCapacities.end() )
	return it->second;

      else
	return 0;
    }

  else
    {
      throw GraphException::InvalidEdge(sourceNode, targetNode, "Given node_ids do not refer to a valid edge", __LINE__, __FILE__, "FlowNetwork<Type>::minCapacity(const GraphTypes::node_id&, const GraphTypes::node_id&)");
    }
}

template<typename Type>
GraphTypes::FlowTypes::Flow FlowNetwork<Type>::flow(const GraphTypes::node_id & sourceNode,
						 const GraphTypes::node_id & targetNode) const
  throw(GraphException::InvalidEdge)
{
  try
    {
      return (GraphTypes::FlowTypes::Flow) this->flowGraph().getCost(sourceNode, targetNode);
    }

  catch(const GraphException::InvalidEdge&)
    {
      throw GraphException::InvalidEdge(sourceNode, targetNode, "Given node_ids do not refer to a valid edge", __LINE__, __FILE__, "FlowNetwork<Type>::flow(const GraphTypes::node_id&, const GraphTypes::node_id&)");
    }
}

template<typename Type>
GraphTypes::FlowTypes::Flow FlowNetwork<Type>::maxCapacity(const GraphTypes::node_id & sourceNode,
							const GraphTypes::node_id & targetNode) const
  throw(GraphException::InvalidEdge)
{
  if( this->flowGraph().has_edge(sourceNode, targetNode) )
    {
      std::map<Edge, GraphTypes::FlowTypes::Flow>::const_iterator it = _maxCapacities.find( Edge(sourceNode, targetNode) );

      if( it != _maxCapacities.end() )
	return it->second;

      else
	return 0;
    }

  else
    {
      throw GraphException::InvalidEdge(sourceNode, targetNode, "Given node_ids do not refer to a valid edge", __LINE__, __FILE__, "FlowNetwork<Type>::maxCapacity(const GraphTypes::node_id&, const GraphTypes::node_id&)");
    }
}

//all min capacities to zero
template<typename Type>
void FlowNetwork<Type>::minCapacitiesToZero()
{
std::map<Edge, GraphTypes::FlowTypes::Flow>::iterator it = _minCapacities.begin();
 while( it != _minCapacities.end() )
    {
      const GraphTypes::node_id & sourceNode = it->first.source();
      const GraphTypes::node_id & targetNode = it->first.target();
      const GraphTypes::FlowTypes::Flow & minCapacity = it->second;

      _maxCapacities[Edge(sourceNode, targetNode)] -= minCapacity;
      setFlow( sourceNode, targetNode, flow(sourceNode, targetNode) - minCapacity );

      _minCapacities.erase(it++);
    }
}

//No capacities on nodes
template<typename Type>
void FlowNetwork<Type>::nodesCapacitiesToFlowCapacities()
{
  for(std::map<GraphTypes::node_id, GraphTypes::FlowTypes::Flow>::iterator it = _nodesCapacities.begin();
      it != _nodesCapacities.end();
      ++it)
    {
      const GraphTypes::node_id & sourceNode = it->first;
      GraphTypes::node_id targetNode = _find_free_node_id();
      const GraphTypes::FlowTypes::Flow & capacity = it->second;

      if( this->flowGraph().is_container() )
	add_node( targetNode, this->flowGraph().get_node_content(sourceNode) );

      else
	add_node(targetNode);

      for(typename Graph<Type>::NodeIterator succ = this->flowGraph().successors_begin(sourceNode);
	  succ != this->flowGraph().successors_end(sourceNode);
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
void FlowNetwork<Type>::uniqueContributors()
{
  for(typename Graph<Type>::NodeIterator node = this->flowGraph().nodes_begin();
      node != this->flowGraph().nodes_begin();
      ++node)
    {
      GraphTypes::FlowTypes::Flow contrib = contribution(*node);
      if( contrib != 0 )
	{
	  if(contrib > 0)
	    add_flow(this->source(), *node, 0, contrib);

	  else
	    add_flow(*node, this->sink(), 0, 0-contrib);
	}
    }
}

template<typename Type>
void FlowNetwork<Type>::normalize()
{
  //all min capacities to zero
  this->minCapacitiesToZero();

  //No capacities on nodes
  this->nodesCapacitiesToFlowCapacities();

  //only one source and only one sink
  this->uniqueContributors();
}
