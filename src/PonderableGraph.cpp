#include "PonderableGraph.hpp"

PonderableGraph::PonderableGraph(GraphTypes::EdgeType edgeType, GraphTypes::EdgeState edgeState):DirectableGraph(edgeType), _edgeState(edgeState){}

PonderableGraph::PonderableGraph(const PonderableGraph & source):DirectableGraph(source), _edgeState(source._edgeState), _weights(source._weights){}

PonderableGraph & PonderableGraph::operator=(const PonderableGraph & source){
  DirectableGraph::operator=(source);
  _edgeState = source._edgeState;
  _weights = source._weights;
  return *this;
}

bool PonderableGraph::is_weighted(){
  return (_edgeState == GraphTypes::WEIGHTED);
}

void PonderableGraph::remove_node(Node::node_id id){
  std::map<Edge, float>::iterator it;

  for(it = _weights.begin(); it != _weights.end(); it++){
    if(it->first.source() == id || it->first.target() == id){
      _weights.erase(it++);
    }
  }

  DirectableGraph::remove_node(id);
}

void PonderableGraph::add_edge(Node::node_id id1, Node::node_id id2,GraphTypes::Cost cost){
  std::map<Edge,GraphTypes::Cost>::iterator it;

  if(cost < 0) throw std::invalid_argument("PonderableGraph::add_edge(node_id, node_id, int): argument 3 of type GraphTypes::Cost may not be negative");

  DirectableGraph::add_edge(id1, id2);
  if(_edgeState == GraphTypes::WEIGHTED){
    _weights.insert( std::pair<Edge,GraphTypes::Cost>(Edge(id1, id2), cost) );
  }
}

void PonderableGraph::remove_edge(Node::node_id id1, Node::node_id id2){
  std::map<Edge, GraphTypes::Cost>::iterator it;

  DirectableGraph::remove_edge(id1, id2);

  if(_edgeState == GraphTypes::WEIGHTED){
    it = _weights.find(Edge(id1, id2));
    if( it == _weights.end() && _edgeType == GraphTypes::UNDIRECTED){
      it = _weights.find(Edge(id2, id1));
    }

    if( it != _weights.end() ){
      _weights.erase(it);
    }
  }
}

void PonderableGraph::setCost(Node::node_id node1, Node::node_id node2, GraphTypes::Cost cost) throw(std::invalid_argument, std::logic_error){
  std::map<Edge, GraphTypes::Cost>::iterator it;

  if( !has_edge(node1, node2) ){
    throw std::invalid_argument("PonderableGraph::setCost(node_id, node_id,Cost): given node_ids do not refer to a valid edge");
  }
  else if(_edgeState == GraphTypes::UNWEIGHTED){
    throw std::logic_error("PonderableGraph::setCost(node_id, node_id,Cost): the graph is an unweighted Graph");
  }
  else if(cost < 0){
    throw std::invalid_argument("PonderableGraph::setCost(node_id, node_id, int): argument 3 of type Cost may not be negative");
  }
  else{
    it = _weights.find( Edge(node1, node2) );
    if(it == _weights.end() && _edgeType == GraphTypes::UNDIRECTED){
      it = _weights.find( Edge(node2, node1) );
    }

    if( it != _weights.end() ){
      it->second = cost;
    }
    else{
      _weights.insert( std::pair<Edge, GraphTypes::Cost>(Edge(node1, node2), cost) );
    }
  }
}

GraphTypes::Cost PonderableGraph::getCost(Node::node_id node1, Node::node_id node2) throw(std::invalid_argument, std::logic_error){
  std::map<Edge, GraphTypes::Cost>::iterator it;

  if(_edgeState == GraphTypes::WEIGHTED){

    if( !has_edge(node1, node2) ){
      throw std::invalid_argument("PonderableGraph::add_getCost(node_id, node_id): given arguments do not refer to a valid edge");
    }
    else{
      it = _weights.find( Edge(node1, node2) );
      if( it == _weights.end() && _edgeType == GraphTypes::UNDIRECTED ){
	it = _weights.find( Edge(node2, node1) );
      }

      if( it != _weights.end() ){
	return it->second;
      }
      else{
	throw std::logic_error("PonderableGraph::getCost(Node::node_id, Node::node_id)const : edge associated to no cost in a weighted graph");
      }
    }
  }
  else{
    throw std::logic_error("PonderableGraph::getCost(Node::node_id, Node::node_id)const : the graph is an graphTypes::UNWEIGHTED graph");
  }
}
