#include "BaseGraph.hpp"

BaseGraph::BaseGraph():_nb_of_edges(0){}

BaseGraph::BaseGraph(const BaseGraph & source):_nodes(source._nodes), _topology(source._topology), _reversed_topology(source._reversed_topology), _nb_of_edges(source._nb_of_edges){}

BaseGraph::~BaseGraph(){}

BaseGraph & BaseGraph::operator=(const BaseGraph & source){
  _nodes = source._nodes;
  _topology = source._topology;
  _reversed_topology = source._reversed_topology;
  _nb_of_edges = source._nb_of_edges;
  return *this;
}

bool BaseGraph::is_empty()const
{
  return ( _nodes.size() == 0 );
}

bool BaseGraph::has_node(const GraphTypes::node_id & node)const
{
  
  return ( _nodes.count(node) > 0 );
}

bool BaseGraph::has_edge(const GraphTypes::node_id & origin, const GraphTypes::node_id & target)const
{
  bool has;
  std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> >::const_iterator it;

  has = false;
  if( has_node(origin) && has_node(target) ){
    it = _topology.find(origin);
    if( it != _topology.end() ){
      has = ( it->second.count(target) > 0 );
    }
  }

  return has;
}

bool BaseGraph::is_directed()const
{
  return true;
}

bool BaseGraph::is_weighted()const
{
  return false;
}

bool BaseGraph::is_container()const
{
  return false;
}

void BaseGraph::add_node(const GraphTypes::node_id & node)
{
  _nodes.insert(node);
}

unsigned int BaseGraph::_clean_topology(std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> > & adjacent_list,
			     std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> > & reversed_adjacent_list,
			     const GraphTypes::node_id & node)
{
  std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> >::iterator map_it;
  std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> >::iterator r_map_it;
  std::set<GraphTypes::node_id>::iterator succ;
  unsigned int nb_of_removed;
  
  map_it = adjacent_list.find(node);
  nb_of_removed = 0;

  if( map_it != adjacent_list.end() ){

    //treating the reversed list
    for(succ = map_it->second.begin(); succ != map_it->second.end(); succ++){
      r_map_it = reversed_adjacent_list.find(*succ);

      if( r_map_it != reversed_adjacent_list.end() ){
	r_map_it->second.erase(node);

	//if we emptied the reversed list
	if(r_map_it->second.size() == 0){
	  reversed_adjacent_list.erase(r_map_it);
	}
      }

    }

    nb_of_removed = map_it->second.size();
    adjacent_list.erase(map_it);
  }

  return nb_of_removed;
}

void BaseGraph::remove_node(const GraphTypes::node_id & node)
{

  std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> >::iterator r_map_it;
  std::set<GraphTypes::node_id>::iterator set_it;
  unsigned int nb_of_removed;

  //As a predecessor...
  nb_of_removed = _clean_topology(_topology, _reversed_topology, node);
  _nb_of_edges -= nb_of_removed;

  //As a successor
  _clean_topology(_reversed_topology, _topology, node);

  _nodes.erase(node);
}

void BaseGraph::add_edge(const GraphTypes::node_id & origin, const GraphTypes::node_id & target)
{
  std::pair<std::set<GraphTypes::node_id>::iterator, bool> status;

  _nodes.insert(origin);
  _nodes.insert(target);

  if( !_topology.count(origin) ){
    _topology.insert( std::pair<GraphTypes::node_id, std::set<GraphTypes::node_id> >(origin, std::set<GraphTypes::node_id>()) );
  }

  status = _topology[origin].insert(target);
  if(status.second){
    _nb_of_edges++;

    if( !_reversed_topology.count(target) ){
      _reversed_topology.insert( std::pair<GraphTypes::node_id, std::set<GraphTypes::node_id> >(target, std::set<GraphTypes::node_id>()) );
    }

    _reversed_topology[target].insert(origin);
  }
}

void BaseGraph::remove_edge(const GraphTypes::node_id & origin, const GraphTypes::node_id & target)
{
  std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> >::iterator it;
  std::set<GraphTypes::node_id>::size_type nb_of_erased;

  it = _topology.find(origin);
  if( it != _topology.end() ){
    nb_of_erased = it->second.erase(target);

    if(nb_of_erased > 0){
      _nb_of_edges--;

      //if we emptied the list
      if( it->second.size() == 0 ){
	_topology.erase(it);
      }

      //treating the reversed topology
      it = _reversed_topology.find(target);
      it->second.erase(origin);

      if( it->second.size() == 0 ){
	_reversed_topology.erase(it);
      }
    }
  }
}

unsigned long BaseGraph::nodes_size()const
{
  return _nodes.size();
}

unsigned long BaseGraph::edges_size()const
{
  return _nb_of_edges;
}

GraphTypes::NodeType BaseGraph::nodeType()const
{
  return GraphTypes::NOCONTENT;
}

GraphTypes::EdgeType BaseGraph::edgeType()const
{
  return GraphTypes::DIRECTED;
}

GraphTypes::EdgeState BaseGraph::edgeState()const
{
  return GraphTypes::UNWEIGHTED;
}

std::set<GraphTypes::node_id>::const_iterator BaseGraph::_adjacent_begin(const std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> > & topology_map, const GraphTypes::node_id & node)const
{
  std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> >::const_iterator it;

  it = topology_map.find(node);

  if( it != topology_map.end() ){
    return it->second.begin();
  }
  else{
    return _nodes.end();
  }
}

std::set<GraphTypes::node_id>::const_iterator BaseGraph::_adjacent_end(const std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> > & topology_map, const GraphTypes::node_id & node)const
{
  std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> >::const_iterator it;

  it = topology_map.find(node);

  if( it != topology_map.end() ){
    return it->second.end();
  }
  else{
    return _nodes.end();
  }
}

BaseGraph::NodeIterator BaseGraph::predecessors_begin(const GraphTypes::node_id & node)const throw(GraphException::InvalidNodeID, GraphException::InvalidOperation)
{
  if( _nodes.count(node) ){
    return NodeIterator( _adjacent_begin(_reversed_topology, node) );

  }
  else{
    throw GraphException::InvalidNodeID(node, "Invalid node ID", __LINE__, __FILE__, "BaseGraph::predecessors_begin(const GraphTypes::node_id&)");
  }

}

BaseGraph::NodeIterator BaseGraph::predecessors_end(const GraphTypes::node_id & node)const throw(GraphException::InvalidNodeID, GraphException::InvalidOperation)
{
  if( _nodes.count(node) ){
    return NodeIterator( _adjacent_end(_reversed_topology, node) );

  }
  else{
    throw GraphException::InvalidNodeID(node, "Invalid node ID", __LINE__, __FILE__, "BaseGraph::predecessors_end(const GraphTypes::node_id&)");
  }

}

BaseGraph::NodeIterator BaseGraph::successors_begin(const GraphTypes::node_id & node)const throw(GraphException::InvalidNodeID, GraphException::InvalidOperation)
{
  if( _nodes.count(node) ){

    return NodeIterator( _adjacent_begin(_topology, node) );
  }
  else{
    throw GraphException::InvalidNodeID(node, "Invalid node ID", __LINE__, __FILE__, "BaseGraph::successors_begin(const GraphTypes::node_id&)");
  }

}

BaseGraph::NodeIterator BaseGraph::successors_end(const GraphTypes::node_id & node)const throw(GraphException::InvalidNodeID, GraphException::InvalidOperation)
{

  if( _nodes.count(node) ){
    return NodeIterator( _adjacent_end(_topology, node) );

  }
  else{
    throw GraphException::InvalidNodeID(node, "Invalid node ID", __LINE__, __FILE__, "BaseGraph::successors_end(const GraphTypes::node_id&)");
  }

}

BaseGraph::NodeIterator BaseGraph::adjacents_begin(const GraphTypes::node_id & node)const throw(GraphException::InvalidNodeID)
{
  std::set<GraphTypes::node_id>::iterator predecessors_begin;
  std::set<GraphTypes::node_id>::iterator predecessors_end;
  std::set<GraphTypes::node_id>::iterator successors_begin;
  std::set<GraphTypes::node_id>::iterator successors_end;

  if( _nodes.count(node) ){
    predecessors_begin = _adjacent_begin(_reversed_topology, node);
    predecessors_end = _adjacent_end(_reversed_topology, node);

    successors_begin = _adjacent_begin(_topology, node);
    successors_end = _adjacent_end(_topology, node);

    return NodeIterator(predecessors_begin, predecessors_end, successors_begin, successors_end, predecessors_begin, successors_begin);

  }
  else{
    throw GraphException::InvalidNodeID(node, "Invalid node ID", __LINE__, __FILE__, "BaseGraph::adjacents_begin(const GraphTypes::node_id&)");
  }

}

BaseGraph::NodeIterator BaseGraph::adjacents_end(const GraphTypes::node_id & node)const throw(GraphException::InvalidNodeID)
{
  std::set<GraphTypes::node_id>::iterator predecessors_begin;
  std::set<GraphTypes::node_id>::iterator predecessors_end;
  std::set<GraphTypes::node_id>::iterator successors_begin;
  std::set<GraphTypes::node_id>::iterator successors_end;

  if( _nodes.count(node) ){
    predecessors_begin = _adjacent_begin(_reversed_topology, node);
    predecessors_end = _adjacent_end(_reversed_topology, node);

    successors_begin = _adjacent_begin(_topology, node);
    successors_end = _adjacent_end(_topology, node);

    return NodeIterator(predecessors_begin, predecessors_end, successors_begin, successors_end, predecessors_end, successors_end);

  }
  else{
    throw GraphException::InvalidNodeID(node, "Invalid node ID", __LINE__, __FILE__, "BaseGraph::adjacents_end(const GraphTypes::node_id&)");
  }

}

BaseGraph::NodeIterator BaseGraph::nodes_begin()const
{
  return NodeIterator( _nodes.begin() );
}

BaseGraph::NodeIterator BaseGraph::nodes_end()const
{
  return NodeIterator( _nodes.end() );
}

BaseGraph::EdgeIterator BaseGraph::edges_begin()const
{
  return EdgeIterator( _topology.begin(), _topology.end(), _topology.begin() );
}

BaseGraph::EdgeIterator BaseGraph::edges_end()const
{
  return EdgeIterator( _topology.begin(), _topology.end(), _topology.end() );
}

unsigned long BaseGraph::in_degree(const GraphTypes::node_id & node)const throw(GraphException::InvalidNodeID)
{
  std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> >::const_iterator it;
  unsigned int deg;

  if( _nodes.count(node) ){
    deg = 0;
    it = _reversed_topology.find(node);

    if( it != _reversed_topology.end() ){
      deg = it->second.size();
    }

    return deg;
  }
  else{
    throw GraphException::InvalidNodeID(node, "Invalid node ID", __LINE__, __FILE__, "BaseGraph::in_degree(const GraphTypes::node_id&)");
  }
}

unsigned long BaseGraph::out_degree(const GraphTypes::node_id & node)const throw(GraphException::InvalidNodeID)
{
  std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> >::const_iterator it;
  unsigned int deg;

  if( _nodes.count(node) > 0){
    deg = 0;

    it = _topology.find(node);
    if( it != _topology.end() ){
      deg = it->second.size();
    }

    return deg;
  }
  else{
    throw GraphException::InvalidNodeID(node, "Invalid node ID", __LINE__, __FILE__, "BaseGraph::out_degree(const GraphTypes::node_id&)");
  }
}

unsigned long BaseGraph::degree(const GraphTypes::node_id & node)const throw(GraphException::InvalidNodeID)
{
  return out_degree(node) + in_degree(node);
}
