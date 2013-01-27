#include "PonderableGraph.hpp"

PonderableGraph::PonderableGraph(const GraphTypes::EdgeType & edgeType, const GraphTypes::EdgeState & edgeState):DirectableGraph(edgeType), _edgeState(edgeState){}

PonderableGraph::PonderableGraph(const PonderableGraph & source):DirectableGraph(source), _edgeState(source._edgeState), _weights(source._weights){}

PonderableGraph & PonderableGraph::operator=(const PonderableGraph & source){
  DirectableGraph::operator=(source);
  _edgeState = source._edgeState;
  _weights = source._weights;
  return *this;
}

bool PonderableGraph::is_weighted()const{
  return (_edgeState == GraphTypes::WEIGHTED);
}

void PonderableGraph::remove_node(const GraphTypes::node_id & node){
  std::map<Edge, float>::iterator it;

  it = _weights.begin();
  while( it != _weights.end() ){
    if(it->first.source() == node || it->first.target() == node){
      _weights.erase(it++);
    }
    else{
      it++;
    }
  }

  DirectableGraph::remove_node(node);
}

void PonderableGraph::add_edge(const GraphTypes::node_id & origin, const GraphTypes::node_id & target, const GraphTypes::Cost & cost){
  std::map<Edge,GraphTypes::Cost>::iterator it;

  DirectableGraph::add_edge(origin, target);

  if(_edgeState == GraphTypes::WEIGHTED){

    if( (_edgeType == GraphTypes::DIRECTED) || ( origin < target ) ){
      _weights.insert( std::pair<Edge,GraphTypes::Cost>(Edge(origin, target), cost) );
    }
    else{
      _weights.insert( std::pair<Edge,GraphTypes::Cost>(Edge(target, origin), cost) );
    }

  }
}

void PonderableGraph::remove_edge(const GraphTypes::node_id & origin, const GraphTypes::node_id & target){
  std::map<Edge, GraphTypes::Cost>::iterator it;

  DirectableGraph::remove_edge(origin, target);

  if(_edgeState == GraphTypes::WEIGHTED){

    if( (_edgeType == GraphTypes::DIRECTED) || ( origin < target ) ){
      it = _weights.find( Edge(origin, target) );
    }
    else{
      it = _weights.find(Edge(target, origin));
    }

    if( it != _weights.end() ){
      _weights.erase(it);
    }

  }
}

GraphTypes::EdgeState PonderableGraph::edgeState()const{
  return _edgeState;
}

void PonderableGraph::setCost(const GraphTypes::node_id & origin, const GraphTypes::node_id & target, const GraphTypes::Cost & cost) throw(GraphException::InvalidEdge, GraphException::InvalidOperation){
  std::map<Edge, GraphTypes::Cost>::iterator it;

  if( !has_edge(origin, target) ){
    throw GraphException::InvalidEdge(origin, target, "Given node_ids do not refer to a valid edge", __LINE__, __FILE__, "PonderableGraph::setCost(const GraphTypes::node_id&, const GraphTypes::node_id&, const GraphTypes::Cost&)");
  }
  else if(_edgeState == GraphTypes::UNWEIGHTED){
    throw GraphException::InvalidOperation("The graph is unweighted", __LINE__, __FILE__, "PonderableGraph::setCost(const GraphTypes::node_id&, const GraphTypes::node_id&, const GraphTypes::Cost&)");
  }
  else{

    if( (_edgeType == GraphTypes::DIRECTED) || ( origin < target ) ){
      it = _weights.find( Edge(origin, target) );
    }
    else{
      it = _weights.find( Edge(target, origin) );
    }

    //Normally, every edge is inserted with a default weight
    assert( it != _weights.end() );

    it->second = cost;
  }
}

GraphTypes::Cost PonderableGraph::getCost(const GraphTypes::node_id & origin, const GraphTypes::node_id & target)const throw(GraphException::InvalidEdge, GraphException::InvalidOperation){
  std::map<Edge, GraphTypes::Cost>::const_iterator it;

  if(_edgeState == GraphTypes::WEIGHTED){

    if( !has_edge(origin, target) ){
    throw GraphException::InvalidEdge(origin, target, "Given node_ids do not refer to a valid edge", __LINE__, __FILE__, "PonderableGraph::getCost(const GraphTypes::node_id&, const GraphTypes::node_id&)");
    }
    else{

      if( (_edgeType == GraphTypes::DIRECTED) || ( origin < target ) ){
	it = _weights.find( Edge(origin, target) );
      }
      else{
	it = _weights.find( Edge(target, origin) );
      }

      //Normally, any edge is associated to a weight
      assert( it != _weights.end() );

      return it->second;
    }

  }
  else{
    throw GraphException::InvalidOperation("The graph is unweighted", __LINE__, __FILE__, "PonderableGraph::getCost(const GraphTypes::node_id&, const GraphTypes::node_id&)");
  }
}

GraphTypes::Cost PonderableGraph::getCost(const Edge & edge)const throw(GraphException::InvalidEdge, GraphException::InvalidOperation)
{
  return getCost( edge.source(), edge.target() );
}

GraphTypes::Cost PonderableGraph::cost()const throw(GraphException::InvalidOperation){
  std::map<Edge,GraphTypes::Cost>::const_iterator it;
  GraphTypes::Cost cost;

  if(_edgeState == GraphTypes::UNWEIGHTED){
    throw GraphException::InvalidOperation("The graph is unweighted", __LINE__, __FILE__, "PonderableGraph::cost()");
  }
  else{
    cost = 0;
    for(it = _weights.begin(); it != _weights.end(); it++){
      cost += it->second;
    }

    return cost;
  }
}
