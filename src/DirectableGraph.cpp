#include "DirectableGraph.hpp"

DirectableGraph::DirectableGraph(GraphTypes::EdgeType edgeType):_edgeType(edgeType){}

DirectableGraph::DirectableGraph(const DirectableGraph & source):DiGraph(source), _edgeType(source._edgeType){}

bool DirectableGraph::has_edge(GraphTypes::node_id id1, GraphTypes::node_id id2){
  bool has;

  has = DiGraph::has_edge(id1, id2);

  if(!has && _edgeType == GraphTypes::UNDIRECTED){
    has = DiGraph::has_edge(id2, id1);
  }

  return has;
}

bool DirectableGraph::is_directed(){
  return _edgeType == GraphTypes::DIRECTED;
}

void DirectableGraph::add_edge(GraphTypes::node_id id1, GraphTypes::node_id id2){
  DiGraph::add_edge(id1, id2);

  if(_edgeType == GraphTypes::UNDIRECTED){
    DiGraph::add_edge(id2, id1);
  }
}

unsigned long DirectableGraph::edges_size()const{
  unsigned long size;

  size = (_edgeType == GraphTypes::UNDIRECTED) ? DiGraph::edges_size() / 2 : DiGraph::edges_size();

  return size;
}

GraphTypes::EdgeType DirectableGraph::edgeType()const{
  return _edgeType;
}

std::set<GraphTypes::node_id> DirectableGraph::predecessors(GraphTypes::node_id node) throw(std::invalid_argument){

  if(_edgeType == GraphTypes::DIRECTED){
    return DiGraph::predecessors(node);
  }
  else{
    return DiGraph::successors(node);
  }
}

std::set<GraphTypes::node_id> DirectableGraph::adjacents(GraphTypes::node_id node) throw(std::invalid_argument){

  if(_edgeType == GraphTypes::DIRECTED){
    return DiGraph::adjacents(node);
  }
  else{
    return DiGraph::successors(node);
  }
}

unsigned long DirectableGraph::in_degree(GraphTypes::node_id node) throw(std::invalid_argument){

  if(_edgeType == GraphTypes::DIRECTED){
    return DiGraph::in_degree(node);
  }
  else{
    return DiGraph::out_degree(node);
  }
}

unsigned long DirectableGraph::degree(GraphTypes::node_id node) throw(std::invalid_argument){

  if(_edgeType == GraphTypes::DIRECTED){
    return DiGraph::degree(node);
  }
  else{
    return DiGraph::out_degree(node);
  }  
}
