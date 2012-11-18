#include "DirectableGraph.hpp"

DirectableGraph::DirectableGraph(GraphTypes::EdgeType edgeType):_edgeType(edgeType){}

DirectableGraph::DirectableGraph(const DirectableGraph & source):DiGraph(source), _edgeType(source._edgeType){}

bool DirectableGraph::has_edge(Node::node_id id1, Node::node_id id2){
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

bool DirectableGraph::is_weighted(){
  return false;
}

void DirectableGraph::add_edge(Node::node_id id1, Node::node_id id2){
  DiGraph::add_edge(id1, id2);

  if(_edgeType == GraphTypes::UNDIRECTED){
    DiGraph::add_edge(id2, id1);
  }
}

std::set<Node::node_id> DirectableGraph::predecessors(Node::node_id node) throw(std::invalid_argument){

  if(_edgeType == GraphTypes::DIRECTED){
    return DiGraph::predecessors(node);
  }
  else{
    return DiGraph::successors(node);
  }
}

std::set<Node::node_id> DirectableGraph::adjacents(Node::node_id node) throw(std::invalid_argument){

  if(_edgeType == GraphTypes::DIRECTED){
    return DiGraph::adjacents(node);
  }
  else{
    return DiGraph::successors(node);
  }
}

unsigned long DirectableGraph::in_degree(Node::node_id node) throw(std::invalid_argument){

  if(_edgeType == GraphTypes::DIRECTED){
    return DiGraph::in_degree(node);
  }
  else{
    return DiGraph::out_degree(node);
  }
}

unsigned long DirectableGraph::degree(Node::node_id node) throw(std::invalid_argument){

  if(_edgeType == GraphTypes::DIRECTED){
    return DiGraph::degree(node);
  }
  else{
    return DiGraph::out_degree(node);
  }  
}
