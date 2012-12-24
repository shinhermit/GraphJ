#include "DiGraph.hpp"

DiGraph::NodeIterator::NodeIterator(){
}

DiGraph::NodeIterator::NodeIterator(std::set<GraphTypes::node_id>::iterator it):_it(it){
}

DiGraph::NodeIterator::NodeIterator(const DiGraph::NodeIterator & source):_it(source._it){
}

DiGraph::NodeIterator & DiGraph::NodeIterator::operator=(const DiGraph::NodeIterator & source){
  _it = source._it;
  return *this;
}

GraphTypes::node_id DiGraph::NodeIterator::operator*()const{
  return *_it;
}

void DiGraph::NodeIterator::operator++(int){
  _it++;
}

void DiGraph::NodeIterator::operator--(int){
  _it--;
}

bool DiGraph::NodeIterator::operator==(const DiGraph::NodeIterator & ref){
  return _it == ref._it;
}

bool DiGraph::NodeIterator::operator!=(const DiGraph::NodeIterator & ref){
  return _it != ref._it;
}

DiGraph::EdgeIterator::EdgeIterator(){
}

DiGraph::EdgeIterator::EdgeIterator(const std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> >::iterator & begin, const std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> >::iterator & end):_current(begin), _end(end){

  if( _current != _end )
    _targetNode = _current->second.begin();
}

DiGraph::EdgeIterator::EdgeIterator(const DiGraph::EdgeIterator & source):_current(source._current), _end(source._end), _targetNode(source._targetNode){
}

DiGraph::EdgeIterator & DiGraph::EdgeIterator::operator=(const DiGraph::EdgeIterator & source){

  _current = source._current;
  _end = source._end;
  _targetNode = source._targetNode;

  return *this;
}

Edge DiGraph::EdgeIterator::operator*()const{
  return Edge(_current->first, *_targetNode);
}

void DiGraph::EdgeIterator::operator++(int){

  if( _targetNode != _current->second.end() ){
    _targetNode++;

    if( _targetNode == _current->second.end() ){
      _current++;

      if(_current != _end)
	_targetNode = _current->second.begin();
    }
  }
  else{
    _current++;

    if(_current != _end)
      _targetNode = _current->second.begin();
  }
}

void DiGraph::EdgeIterator::operator--(int){

  if( _targetNode != _current->second.begin() ){

    _targetNode--;
  }
  else{

    _current--;
    _targetNode = _current->second.end();
    _targetNode--;
  }
}

bool DiGraph::EdgeIterator::operator==(const DiGraph::EdgeIterator & ref){
  bool equal;

  equal = false;

  if(
     (_current == _end && ref._current == _current) ||
     (_current != _end && _current == ref._current && _targetNode == ref._targetNode)
     ){
    equal = true;
  }

  return equal;
}

bool DiGraph::EdgeIterator::operator!=(const DiGraph::EdgeIterator & ref){

  bool neq;

  neq = false;

  if(
     (_current == _end && ref._current != _current) ||
     (_current != _end && (_current != ref._current || _targetNode != ref._targetNode) )
     ){
    neq = true;
  }

  return neq;
}

DiGraph::DiGraph():_nb_of_edges(0){}

DiGraph::DiGraph(const DiGraph & source):_nodes(source._nodes), _nb_of_edges(source._nb_of_edges), _topology(source._topology){
}

DiGraph::~DiGraph(){
}

DiGraph & DiGraph::operator=(const DiGraph & source){
  _nodes = source._nodes;
  _nb_of_edges = source._nb_of_edges;
  _topology = source._topology;
  return *this;
}

bool DiGraph::is_empty(){
  return ( _nodes.size() == 0 );
}

bool DiGraph::has_node(GraphTypes::node_id id){
  
  return ( _nodes.count(id) > 0 );
}

bool DiGraph::has_edge(GraphTypes::node_id id1, GraphTypes::node_id id2){
  bool has;
  std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> >::iterator it;

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

void DiGraph::add_node(GraphTypes::node_id id){
  _nodes.insert(id);
}

void DiGraph::remove_node(GraphTypes::node_id id){
  std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> >::iterator it;
  std::set<GraphTypes::node_id>::iterator pos, pos_as_succ;

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
  }
}

void DiGraph::add_edge(GraphTypes::node_id id1, GraphTypes::node_id id2){
  std::pair<std::set<GraphTypes::node_id>::iterator, bool> status;

  _nodes.insert(id1);
  _nodes.insert(id2);

  if( !_topology.count(id1) ){
    _topology.insert( std::pair<GraphTypes::node_id, std::set<GraphTypes::node_id> >(id1, std::set<GraphTypes::node_id>()) );
  }

  status = _topology[id1].insert(id2);
  if(status.second) _nb_of_edges++;
}

void DiGraph::remove_edge(GraphTypes::node_id id1, GraphTypes::node_id id2){
  std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> >::iterator it;
  std::set<GraphTypes::node_id>::size_type t;

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

std::set<GraphTypes::node_id> DiGraph::successors(GraphTypes::node_id node) throw(std::invalid_argument){
  std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> >::iterator it;

  if( _nodes.count(node) ){

    it = _topology.find(node);
    if( it != _topology.end() ){
      return _topology[node];
    }
    else{
      return std::set<GraphTypes::node_id>();
    }

  }
  else{
    throw std::invalid_argument("DiGraph::successors(GraphTypes::node_id) : given id not in the graph");
  }
}

std::set<GraphTypes::node_id> DiGraph::predecessors(GraphTypes::node_id node) throw(std::invalid_argument){
  std::set<GraphTypes::node_id> preds;
  std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> >::iterator it;

  if( _nodes.count(node) ){

    for(it = _topology.begin(); it != _topology.end(); it++){
      if( it->second.count(node) ){
	preds.insert(it->first);
      }
    }
    return preds;

  }
  else{
    throw std::invalid_argument("DiGraph::predecessors(GraphTypes::node_id) : given id not in the graph");
  }
}

std::set<GraphTypes::node_id> DiGraph::adjacents(GraphTypes::node_id node) throw(std::invalid_argument){

  std::set<GraphTypes::node_id> preds = predecessors(node);
  std::set<GraphTypes::node_id> succs = successors(node);

  preds.insert( succs.begin(), succs.end() );

  return preds;
}

DiGraph::NodeIterator DiGraph::nodes_begin(){
  return NodeIterator( _nodes.begin() );
}

DiGraph::NodeIterator DiGraph::nodes_end(){
  return NodeIterator( _nodes.end() );
}

DiGraph::EdgeIterator DiGraph::edges_begin(){
  return EdgeIterator( _topology.begin(), _topology.end() );
}

DiGraph::EdgeIterator DiGraph::edges_end(){
  return EdgeIterator( _topology.end(), _topology.end() );
}

unsigned long DiGraph::in_degree(GraphTypes::node_id node) throw(std::invalid_argument){
  std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> >::iterator it;
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
    throw std::invalid_argument("DiGraph::in_degree(GraphTypes::node_id) : given id not in the graph");
  }
}

unsigned long DiGraph::out_degree(GraphTypes::node_id node) throw(std::invalid_argument){
  std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> >::iterator it;

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
    throw std::invalid_argument("DiGraph::out_degree(GraphTypes::node_id) : given id not in the graph");
  }
}

unsigned long DiGraph::degree(GraphTypes::node_id node) throw(std::invalid_argument){
  return out_degree(node) + in_degree(node);
}
