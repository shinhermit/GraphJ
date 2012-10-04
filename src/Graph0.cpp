#include "Graph0.hpp"

Graph0::Graph0():_it(_nodes.begin()){}

Graph0::Graph0(const Graph0 & source):_nodes(source._nodes),_topology(source._topology), _it(_nodes.begin()){
}

Graph0::~Graph0(){
}

Graph0 & Graph0::operator=(const Graph0 & source){
  _nodes = source._nodes;
  _topology = source._topology;
  _it = _nodes.begin();
  return *this;
}

bool Graph0::is_empty(){
  return ( _nodes.size() == 0 );
}

bool Graph0::has_node(Node::node_id id){
  
  return ( _nodes.count(id) > 0 );
}

bool Graph0::has_edge(Node::node_id id1, Node::node_id id2){
  bool has;

  has = false;
  if( has_node(id1) && has_node(id2) ){
    if( _topology.count(id1) ){
      has = ( _topology[id1].count(id2) > 0 );
    }
  }

  return has;
}

void Graph0::add_node(Node::node_id id){
  _nodes.insert(id);
  _it = _nodes.begin();
}

void Graph0::remove_node(Node::node_id id){
  std::map<Node::node_id, std::set<Node::node_id> >::iterator it;
  std::set<Node::node_id>::iterator pos, pos_as_succ;

  pos = _nodes.find(id);
  if( pos != _nodes.end() ){
    //erasing the node in all successors lists
    for(it=_topology.begin(); it!=_topology.end(); it++){
      pos_as_succ = it->second.find(id);
      if( pos_as_succ != it->second.end() ){
	it->second.erase(pos_as_succ);
      }

      //if we emptied the list of successors
      if(it->second.size() == 0){
	_topology.erase(it++); //possible issue: will this change it? (side effect). Solving side effect by post-incrementation
      }
    }

    //erasing the list of successors of the node
    _topology.erase(id);

    //erasing the node
    _nodes.erase(pos);
    _it = _nodes.begin();
  }
}

void Graph0::add_edge(Node::node_id id1, Node::node_id id2){
  _nodes.insert(id1);
  _nodes.insert(id2);

  if( !_topology.count(id1) ){
    _topology.insert( std::pair<Node::node_id, std::set<Node::node_id> >(id1, std::set<Node::node_id>()) );
  }
  _topology[id1].insert(id2);
}

void Graph0::remove_edge(Node::node_id id1, Node::node_id id2){
  //the order of these instructions is important
  remove_node(id2);
  remove_node(id1);
}

unsigned long Graph0::size()const{
  return _nodes.size();
}

std::set<Node::node_id> Graph0::successors(Node::node_id node){
  std::map<Node::node_id, std::set<Node::node_id> >::iterator it;

  it = _topology.find(node);
  if( it != _topology.end() ){
    return _topology[node];
  }
  else{
    return std::set<Node::node_id>();
  }
}

Node::node_id Graph0::first_node(){
  if( _nodes.size() > 0 ){
    _it = _nodes.begin();
    return *_it;
  }
  else{
    throw std::string("Graph0::first_node() : attemp to access empty graph");
  }
}

Node::node_id Graph0::next_node(){
  if( _nodes.size() > 0 ){

    if( _it != _nodes.end() )
      _it++;

    if(_it != _nodes.end() ){
      return *_it;
    }
    else{
      _it = _nodes.begin();
      return *_it;
    }
  }
  else{
    throw std::string("Graph0::next_node() : Attempt to access empty graph");
  }
}

Node::node_id Graph0::previous_node(){
  if( _nodes.size() > 0 ){
    if(_it != _nodes.begin() ){
      _it--;
      return *_it;
    }
    else{
      _it = _nodes.end();
      _it--;
      return *_it;
    }
  }
  else{
    throw std::string("Graph0::next_node() : Attempt to access empty graph");
  }
}

Node::node_id Graph0::last_node(){
  if( _nodes.size() > 0 ){
    _it = _nodes.end();
    _it --;
    return *_it;
  }
  else{
    throw std::string("Graph0::last_node() : Attempt to access empty graph");
  }
}
