#include <cassert>
#include <iostream>
#include <string>
#include "PonderableGraph.hpp"
#include "Graph.hpp"

int main()
{
  // PonderableGraph graph(GraphTypes::UNDIRECTED, GraphTypes::WEIGHTED);
  Graph<> graph(GraphTypes::UNDIRECTED, GraphTypes::WEIGHTED, GraphTypes::NOCONTENT);

  /********** Générateur initial **********/

  // Les constructeurs
  graph.remove_node(1);
  graph.remove_edge(2,5);

  try
    {
      graph.setCost(209, 3, -1);
      assert("graph.setCost(209, 3, -1)" == "echec");
    }

  catch(const GraphException::InvalidEdgeException & e){}
  
  // Les prédicats
  assert( graph.is_weighted() );

  // Les observateurs
  assert( graph.edgeState() == GraphTypes::WEIGHTED );

  try
    {
    graph.getCost(2,3);
    assert("graph.getCost(2,3)" == "echec");
  }

  catch(const GraphException::InvalidEdgeException & e){}


  try
    {
    graph.getCost( Edge(2,3) );
    assert("graph.getCost( Edge(2,3) )" == "echec");
  }

  catch(const GraphException::InvalidEdgeException & e){}

  assert( graph.cost() == 0 );


  /********** add_edge **********/
  graph.add_edge(1,2, 1);
  graph.add_edge(2,3, 2);
  graph.add_edge(3,4, 3);
  
  // Les prédicats
  assert( graph.is_weighted() );

  // Les observateurs
  assert( graph.edgeState() == GraphTypes::WEIGHTED );

  assert( graph.getCost(1,2) == 1);
  assert( graph.getCost(2,1) == 1);
  assert( graph.getCost(2,3) == 2);
  assert( graph.getCost(3,2) == 2);
  assert( graph.getCost(3,4) == 3);
  assert( graph.getCost(4,3) == 3);


  assert( graph.getCost( Edge(1,2) ) == graph.getCost(1,2) );
  assert( graph.getCost( Edge(2,3) ) == graph.getCost(2,3) );
  assert( graph.getCost( Edge(3,4) ) == graph.getCost(3,4) );

  assert( graph.cost() == 6 );


  /********** remove_node **********/
  graph.add_edge(4,5, 4);
  graph.add_edge(1,5, 1);
  graph.add_edge(5,2, 5);

  graph.remove_node(5);
  
  // Les prédicats
  assert( graph.is_weighted() );

  // Les observateurs
  assert( graph.edgeState() == GraphTypes::WEIGHTED );

  assert( graph.getCost(1,2) == 1);
  assert( graph.getCost(3,2) == 2);
  assert( graph.getCost(3,4) == 3);

  try
    {
    graph.getCost(1,5);
  }

  catch(const GraphException::InvalidEdgeException & e){}

  try
    {
    graph.getCost(5,2);
  }

  catch(const GraphException::InvalidEdgeException & e){}

  assert( graph.cost() == 6 );

  /********** remove_edge **********/
  graph.remove_edge(2,3);

  // Les observateurs
  assert( graph.getCost(1,2) == 1);
  assert( graph.getCost(3,4) == 3);

  try
    {
    graph.getCost(2,3);
  }

  catch(const GraphException::InvalidEdgeException & e){}

  try
    {
    graph.getCost(5,2);
  }

  catch(const GraphException::InvalidEdgeException & e){}

  assert( graph.cost() == 4 );

  /********** setCost **********/
  graph.setCost(1,2, -1);

  // Les observateurs
  assert( graph.getCost(1,2) == -1);
  assert( graph.getCost(3,4) == 3);

  try
    {
    graph.getCost(2,3);
  }

  catch(const GraphException::InvalidEdgeException & e){}

  assert( graph.cost() == 2 );


  std::cout << std::endl << "You can trust your program !!" << std::endl << std::endl;

  return 0;
}
