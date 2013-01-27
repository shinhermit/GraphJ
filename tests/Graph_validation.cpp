#include <cassert>
#include <iostream>
#include <string>
#include "Graph.hpp"

int main(){
  Graph<std::string> graph(GraphTypes::UNDIRECTED, GraphTypes::WEIGHTED, GraphTypes::CONTAINER);

  /********** Générateur initial **********/
  
  // Les prédicats
  assert( graph.is_container() );

  // Les observateurs
  assert( graph.nodeType() == GraphTypes::CONTAINER );

  try{
    graph.get_node_content(0);
    assert("graph.get_node_content(0)" == "echec");
  }
  catch(const GraphException::InvalidNodeID & e){
  }


  /********** add_node **********/

  try{
    graph.add_node(1);
    assert("graph.add_node(1)" == "echec");
  }
  catch(const GraphException::InvalidOperation & e){
  }

  graph.add_node(1, "1");
  
  // Les prédicats
  assert( graph.is_container() );

  // Les observateurs
  assert( graph.nodeType() == GraphTypes::CONTAINER );

  try{
    graph.get_node_content(2);
    assert("graph.get_node_content(2)" == "echec");
  }
  catch(const GraphException::InvalidNodeID & e){
  }

  assert( graph.get_node_content(1) == "1" );


  /********** graph.remove_node **********/
   graph.remove_node(1);
  
  // Les prédicats
  assert( graph.is_container() );

  // Les observateurs
  assert( graph.nodeType() == GraphTypes::CONTAINER );

  try{
    graph.get_node_content(1);
    assert("graph.get_node_content(1)" == "echec");
  }
  catch(const GraphException::InvalidNodeID & e){}


  /********** add_edge **********/

  try{
    graph.add_edge(1,2, 1);
    assert("graph.add_edge(1,2, 1)" == "echec");
  }
  catch(const GraphException::InvalidOperation & e){}

  graph.add_edge(1,"1", 2,"2", 1);
  
  // Les prédicats
  assert( graph.is_container() );

  // Les observateurs
  assert( graph.nodeType() == GraphTypes::CONTAINER );

  assert( graph.get_node_content(1) == "1" );
  assert( graph.get_node_content(2) == "2" );


  /********** set_node_content **********/
  graph.set_node_content(1, "-3") ;
  
  // Les prédicats
  assert( graph.is_container() );

  // Les observateurs
  assert( graph.nodeType() == GraphTypes::CONTAINER );

  assert( graph.get_node_content(1) == "-3" );


  std::cout << std::endl << "You can trust your program !!" << std::endl << std::endl;

  return 0;
}
