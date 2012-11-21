#include "DiGraph.hpp"

DiGraph::DiGraph():_nb_of_edges(0), _it(_nodes.begin()){}

DiGraph::DiGraph(const DiGraph & source):_nodes(source._nodes), _nb_of_edges(source._nb_of_edges), _topology(source._topology), _it(_nodes.begin()){
}

DiGraph::~DiGraph(){
}

DiGraph & DiGraph::operator=(const DiGraph & source){
  _nodes = source._nodes;
  _nb_of_edges = source._nb_of_edges;
  _topology = source._topology;
  _it = _nodes.begin();
  return *this;
}

bool DiGraph::is_empty(){
  return ( _nodes.size() == 0 );
}

bool DiGraph::has_node(Node::node_id id){
  
  return ( _nodes.count(id) > 0 );
}

bool DiGraph::has_edge(Node::node_id id1, Node::node_id id2){
  bool has;
  std::map<Node::node_id, std::set<Node::node_id> >::iterator it;

  has = false;
  if( has_node(id1) && has_node(id2) ){
    it = _topology.find(id1);
    if( it != _topology.end() ){
      has = ( it->second.count(id2) > 0 );
    }
  }

  return has;
}

bool DiGraph::is_directed(){
  return true;
}

bool DiGraph::is_weighted(){
  return false;
}

bool DiGraph::is_container(){
  return false;
}

bool DiGraph::at_nodes_end(){
  return _it == _nodes.end();
}

void DiGraph::add_node(Node::node_id id){
  _nodes.insert(id);
  _it = _nodes.begin();
}

void DiGraph::remove_node(Node::node_id id){
  std::map<Node::node_id, std::set<Node::node_id> >::iterator it;
  std::set<Node::node_id>::iterator pos, pos_as_succ;

  pos = _nodes.find(id);
  if( pos != _nodes.end() ){
    //erasing the node in all successors lists
    it=_topology.begin();
    while( it!=_topology.end() ){
      pos_as_succ = it->second.find(id);
      if( pos_as_succ != it->second.end() ){
	it->second.erase(pos_as_succ);
	_nb_of_edges --;
      }

      //if we emptied the list of successors
      if(it->second.size() == 0){
	_topology.erase(it++); //possible issue: will this change it? (side effect). Solving side effect by post-incrementation
      }
      else{
	it++;
      }
    }

    //erasing the list of successors of the node
    it = _topology.find(id);
    if( it != _topology.end() ){
      _nb_of_edges -= it->second.size();
      _topology.erase(it);
    }
    

    //erasing the node
    _nodes.erase(pos);
    _it = _nodes.begin();
  }
}

void DiGraph::add_edge(Node::node_id id1, Node::node_id id2){
  std::pair<std::set<Node::node_id>::iterator, bool> status;

  _nodes.insert(id1);
  _nodes.insert(id2);

  if( !_topology.count(id1) ){
    _topology.insert( std::pair<Node::node_id, std::set<Node::node_id> >(id1, std::set<Node::node_id>()) );
  }

  status = _topology[id1].insert(id2);
  if(status.second) _nb_of_edges++;
}

void DiGraph::remove_edge(Node::node_id id1, Node::node_id id2){
  std::map<Node::node_id, std::set<Node::node_id> >::iterator it;
  std::set<Node::node_id>::size_type t;

  it = _topology.find(id1);
  if( it != _topology.end() ){
    t = it->second.erase(id2);
    if(t > 0) _nb_of_edges--;
  }
}

unsigned long DiGraph::nodes_size()const{
  return _nodes.size();
}

unsigned long DiGraph::edges_size()const{
  return _nb_of_edges;
}

GraphTypes::NodeType DiGraph::nodeType()const{
  return GraphTypes::NOCONTENT;
}

GraphTypes::EdgeType DiGraph::edgeType()const{
  return GraphTypes::DIRECTED;
}

GraphTypes::EdgeState DiGraph::edgeState()const{
  return GraphTypes::UNWEIGHTED;
}

std::set<Node::node_id> DiGraph::successors(Node::node_id node) throw(std::invalid_argument){
  std::map<Node::node_id, std::set<Node::node_id> >::iterator it;

  if( _nodes.count(node) ){

    it = _topology.find(node);
    if( it != _topology.end() ){
      return _topology[node];
    }
    else{
      return std::set<Node::node_id>();
    }

  }
  else{
    throw std::invalid_argument("DiGraph::successors(Node::node_id) : given id not in the graph");
  }
}

std::set<Node::node_id> DiGraph::predecessors(Node::node_id node) throw(std::invalid_argument){
  std::set<Node::node_id> preds;
  std::map<Node::node_id, std::set<Node::node_id> >::iterator it;

  if( _nodes.count(node) ){

    for(it = _topology.begin(); it != _topology.end(); it++){
      if( it->second.count(node) ){
	preds.insert(it->first);
      }
    }
    return preds;

  }
  else{
    throw std::invalid_argument("DiGraph::predecessors(Node::node_id) : given id not in the graph");
  }
}

std::set<Node::node_id> DiGraph::adjacents(Node::node_id node) throw(std::invalid_argument){

  std::set<Node::node_id> preds = predecessors(node);
  std::set<Node::node_id> succs = successors(node);

  preds.insert( succs.begin(), succs.end() );

  return preds;
}

Node::node_id DiGraph::first_node() throw(std::out_of_range){
  if( _nodes.size() > 0 ){
    _it = _nodes.begin();
    return *_it;
  }
  else{
    throw std::out_of_range("DiGraph::first_node() : attemp to access empty graph");
  }
}

Node::node_id DiGraph::next_node() throw(std::out_of_range){
  if( _nodes.size() > 0 ){

    if( _it != _nodes.end() )
      _it++;

    return *_it;
  }
  else{
    throw std::out_of_range("DiGraph::next_node() : Attempt to access empty graph");
  }
}

Node::node_id DiGraph::previous_node() throw(std::out_of_range){
  if( _nodes.size() > 0 ){
    if(_it != _nodes.begin() )
      _it--;

    return *_it;
  }
  else{
    throw std::out_of_range("DiGraph::next_node() : Attempt to access empty graph");
  }
}

Node::node_id DiGraph::last_node() throw(std::out_of_range){
  if( _nodes.size() > 0 ){
    _it = _nodes.end();
    _it --;
    return *_it;
  }
  else{
    throw std::out_of_range("DiGraph::last_node() : Attempt to access empty graph");
  }
}

unsigned long DiGraph::in_degree(Node::node_id node) throw(std::invalid_argument){
  std::map<Node::node_id, std::set<Node::node_id> >::iterator it;
  unsigned long count;

  if( _nodes.count(node) ){

    count = 0;
    for(it = _topology.begin(); it != _topology.end(); it++){
      if( it->second.count(node) ){
	count ++;
      }
    }
    return count;

  }
  else{
    throw std::invalid_argument("DiGraph::in_degree(Node::node_id) : given id not in the graph");
  }
}

unsigned long DiGraph::out_degree(Node::node_id node) throw(std::invalid_argument){
  std::map<Node::node_id, std::set<Node::node_id> >::iterator it;

  if( _nodes.count(node) > 0){

    it = _topology.find(node);
    if( it != _topology.end() ){
      return it->second.size();
    }
    else{
      return 0;
    }

  }
  else{
    throw std::invalid_argument("DiGraph::out_degree(Node::node_id) : given id not in the graph");
  }
}

unsigned long DiGraph::degree(Node::node_id node) throw(std::invalid_argument){
  return out_degree(node) + in_degree(node);
}
