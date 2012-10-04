#include "AbstractGraph.hpp"

bool AbstractGraph::is_empty(){
 std::cout << "calling abstract AbstractGraph::is_empty()" << std::endl;
  return false;
}

bool AbstractGraph::has_node(Node::node_id id){
  std::cout << "calling abstract AbstractGraph::has_node()" << std::endl;
  
  return false;
}

bool AbstractGraph::has_edge(Node::node_id id1, Node::node_id id2){
  std::cout << "calling abstract AbstractGraph::has_edge()" << std::endl;
  return false;
}

void AbstractGraph::add_node(Node::node_id id){ 
  std::cout << "calling abstract AbstractGraph::add_node()" << std::endl;
}

void AbstractGraph::remove_node(Node::node_id id){
  std::cout << "calling abstract AbstractGraph::remove_node()" << std::endl;
}

void AbstractGraph::add_edge(Node::node_id id1, Node::node_id id2){
  std::cout << "calling abstract AbstractGraph::add_edge()" << std::endl;
}

void AbstractGraph::remove_edge(Node::node_id id1, Node::node_id id2){ 
  std::cout << "calling abstract AbstractGraph::remove_edge()" << std::endl;
}

unsigned long AbstractGraph::size()const{
  std::cout << "calling abstract AbstractGraph::size()" << std::endl;
  return 0;
}

std::set<Node::node_id> AbstractGraph::successors(Node::node_id node){
  std::cout << "calling abstract AbstractGraph::successors()" << std::endl;
  return std::set<Node::node_id>() ;
}

Node::node_id AbstractGraph::first_node(){
  std::cout << "calling abstract AbstractGraph::first_node()" << std::endl;
  return 0;
}

Node::node_id AbstractGraph::next_node(){
  std::cout << "calling abstract AbstractGraph::next_node()" << std::endl;
  return 0;
}

Node::node_id AbstractGraph::previous_node(){ 
  std::cout << "calling abstract AbstractGraph::previous_node()" << std::endl;
  return 0;
}

Node::node_id AbstractGraph::last_node(){
  std::cout << "calling abstract AbstractGraph::last_node()" << std::endl;
  return 0;
}

unsigned long internally(Node::node_id node){
  std::cout << "calling abstract AbstractGraph::internally()" << std::endl;
  return 0;
}

unsigned long externally(Node::node_id node){
  std::cout << "calling abstract AbstractGraph::externally()" << std::endl;
  return 0;
}
