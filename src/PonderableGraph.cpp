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

void PonderableGraph::remove_node(GraphTypes::node_id id){
  std::map<Edge, float>::iterator it;

  it = _weights.begin();
  while( it != _weights.end() ){
    if(it->first.source() == id || it->first.target() == id){
      _weights.erase(it++);
    }
    else{
      it++;
    }
  }

  DiGraph::remove_node(id);
}

void PonderableGraph::add_edge(GraphTypes::node_id id1, GraphTypes::node_id id2,GraphTypes::Cost cost){
  std::map<Edge,GraphTypes::Cost>::iterator it;

  DirectableGraph::add_edge(id1, id2);
  if(_edgeState == GraphTypes::WEIGHTED){
    _weights.insert( std::pair<Edge,GraphTypes::Cost>(Edge(id1, id2), cost) );
  }
}

void PonderableGraph::remove_edge(GraphTypes::node_id id1, GraphTypes::node_id id2){
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

GraphTypes::EdgeState PonderableGraph::edgeState()const{
  return _edgeState;
}

void PonderableGraph::setCost(GraphTypes::node_id node1, GraphTypes::node_id node2, GraphTypes::Cost cost) throw(std::invalid_argument, std::logic_error){
  std::map<Edge, GraphTypes::Cost>::iterator it;

  if( !has_edge(node1, node2) ){
    throw std::invalid_argument("PonderableGraph::setCost(node_id, node_id,Cost): given node_ids do not refer to a valid edge");
  }
  else if(_edgeState == GraphTypes::UNWEIGHTED){
    throw std::logic_error("PonderableGraph::setCost(node_id, node_id,Cost): the graph is an unweighted Graph");
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

GraphTypes::Cost PonderableGraph::getCost(GraphTypes::node_id node1, GraphTypes::node_id node2) throw(std::invalid_argument, std::logic_error){
  std::map<Edge, GraphTypes::Cost>::iterator it;

  if(_edgeState == GraphTypes::WEIGHTED){

    if( !has_edge(node1, node2) ){
      throw std::invalid_argument("PonderableGraph::getCost(node_id, node_id): given arguments do not refer to a valid edge");
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
	throw std::logic_error("PonderableGraph::getCost(GraphTypes::node_id, GraphTypes::node_id)const : edge associated to no cost in a weighted graph");
      }
    }
  }
  else{
    throw std::logic_error("PonderableGraph::getCost(GraphTypes::node_id, GraphTypes::node_id)const : the graph is an graphTypes::UNWEIGHTED graph");
  }
}

GraphTypes::Cost PonderableGraph::getCost(const Edge & edge) throw(std::invalid_argument, std::logic_error)
{
  return getCost( edge.source(), edge.target() );
}

GraphTypes::Cost PonderableGraph::cost() throw(std::logic_error){
  std::map<Edge,GraphTypes::Cost>::iterator it;
  GraphTypes::Cost cost;

  if(_edgeState == GraphTypes::UNWEIGHTED){
    throw std::logic_error("PonderableGraph::cost()const : the type of the graph is graphTypes::UNWEIGHTED");
  }
  else{
    cost = 0;
    for(it = _weights.begin(); it != _weights.end(); it++){
      cost += it->second;
    }

    return cost;
  }
}
