#include "DirectableGraph.hpp"

DirectableGraph::DirectableGraph(const GraphTypes::EdgeType & edgeType):_edgeType(edgeType){}

DirectableGraph::DirectableGraph(const DirectableGraph & source):BaseGraph(source), _edgeType(source._edgeType){}

bool DirectableGraph::is_directed()const
{
  return _edgeType == GraphTypes::DIRECTED;
}

bool DirectableGraph::has_edge(const GraphTypes::node_id & origin, const GraphTypes::node_id & target)const
{
  bool has = BaseGraph::has_edge(origin, target);

  if(!has && _edgeType == GraphTypes::UNDIRECTED){
    has = BaseGraph::has_edge(target, origin);
  }

  return has;
}

void DirectableGraph::add_edge(const GraphTypes::node_id & origin, const GraphTypes::node_id & target)
{

  if( (_edgeType == GraphTypes::DIRECTED) || (origin < target) ){

    BaseGraph::add_edge(origin, target);
  }
  else{
    BaseGraph::add_edge(target, origin);
  }

}

void DirectableGraph::remove_edge(const GraphTypes::node_id & origin, const GraphTypes::node_id & target)
{

  if( (_edgeType == GraphTypes::DIRECTED) || (origin < target) ){

    BaseGraph::remove_edge(origin, target);
  }
  else{
    BaseGraph::remove_edge(target, origin);
  }
}

GraphTypes::EdgeType DirectableGraph::edgeType()const
{
  return _edgeType;
}

DirectableGraph::NodeIterator DirectableGraph::predecessors_begin(const GraphTypes::node_id & node)const throw(GraphException::InvalidNodeID, GraphException::InvalidOperation)
{

  if(_edgeType == GraphTypes::DIRECTED){
    return BaseGraph::predecessors_begin(node);
  }
  else{
    throw GraphException::InvalidOperation("undirected graph: use adjacents_begin(const GraphTypes::node_id&)", __LINE__, __FILE__, "DirectableGraph::predecessors_begin(const GraphTypes::node_id&)");
  }

}

DirectableGraph::NodeIterator DirectableGraph::predecessors_end(const GraphTypes::node_id & node)const throw(GraphException::InvalidNodeID, GraphException::InvalidOperation)
{

  if(_edgeType == GraphTypes::DIRECTED){
    return BaseGraph::predecessors_end(node);
  }
  else{
    throw GraphException::InvalidOperation("undirected graph: use adjacents_end(const GraphTypes::node_id&)", __LINE__, __FILE__, "DirectableGraph::predecessors_end(const GraphTypes::node_id&)");
  }

}

DirectableGraph::NodeIterator DirectableGraph::successors_begin(const GraphTypes::node_id & node)const throw(GraphException::InvalidNodeID, GraphException::InvalidOperation)
{

  if(_edgeType == GraphTypes::DIRECTED){
    return BaseGraph::successors_begin(node);
  }
  else{
    throw GraphException::InvalidOperation("undirected graph: use adjacents_begin(const GraphTypes::node_id&)", __LINE__, __FILE__, "DirectableGraph::successors_begin(const GraphTypes::node_id&)");
  }

}

DirectableGraph::NodeIterator DirectableGraph::successors_end(const GraphTypes::node_id & node)const throw(GraphException::InvalidNodeID, GraphException::InvalidOperation)
{

  if(_edgeType == GraphTypes::DIRECTED){
    return BaseGraph::successors_end(node);
  }
  else{
    throw GraphException::InvalidOperation("undirected graph: use adjacents_end(const GraphTypes::node_id&)", __LINE__, __FILE__, "DirectableGraph::successors_end(const GraphTypes::node_id&)");
  }

}

unsigned long DirectableGraph::in_degree(const GraphTypes::node_id & node)const throw(GraphException::InvalidNodeID)
{

  if(_edgeType == GraphTypes::DIRECTED){
    return BaseGraph::in_degree(node);
  }
  else{
    return BaseGraph::degree(node);
  }  
}

unsigned long DirectableGraph::out_degree(const GraphTypes::node_id & node)const throw(GraphException::InvalidNodeID)
{

  if(_edgeType == GraphTypes::DIRECTED){
    return BaseGraph::out_degree(node);
  }
  else{
    return BaseGraph::degree(node);
  }  
}
