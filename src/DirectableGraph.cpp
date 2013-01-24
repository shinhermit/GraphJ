#include "DirectableGraph.hpp"

DirectableGraph::DirectableGraph(const GraphTypes::EdgeType & edgeType):_edgeType(edgeType){}

DirectableGraph::DirectableGraph(const DirectableGraph & source):BaseGraph(source), _edgeType(source._edgeType){}

bool DirectableGraph::is_directed()const
{
  return _edgeType == GraphTypes::DIRECTED;
}

bool DirectableGraph::has_edge(const GraphTypes::node_id & origin, const GraphTypes::node_id & target)const
{
  return BaseGraph::has_edge(origin, target) || BaseGraph::has_edge(origin, target);
}

void DirectableGraph::add_edge(const GraphTypes::node_id & origin, const GraphTypes::node_id & target)
{

  if( BaseGraph::has_edge(target, origin) ){
    BaseGraph::add_edge(origin, target);
  }
}

void DirectableGraph::remove_edge(const GraphTypes::node_id & origin, const GraphTypes::node_id & target)
{
  unsigned int oldsize;

  oldsize = _nb_of_edges;

  BaseGraph::remove_edge(origin,target);

  if(_nb_of_edges == oldsize){
    BaseGraph::remove_edge(target,origin);
  }
}

GraphTypes::EdgeType DirectableGraph::edgeType()const
{
  return _edgeType;
}

unsigned long DirectableGraph::in_degree(const GraphTypes::node_id & node)const throw(GraphException::InvalidNodeIDException)
{

  if(_edgeType == GraphTypes::DIRECTED){
    return BaseGraph::in_degree(node);
  }
  else{
    return BaseGraph::degree(node);
  }  
}

unsigned long DirectableGraph::out_degree(const GraphTypes::node_id & node)const throw(GraphException::InvalidNodeIDException)
{

  if(_edgeType == GraphTypes::DIRECTED){
    return BaseGraph::out_degree(node);
  }
  else{
    return BaseGraph::degree(node);
  }  
}
