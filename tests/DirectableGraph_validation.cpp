#include <cassert>
#include <iostream>
#include <string>
#include "DirectableGraph.hpp"
#include "PonderableGraph.hpp"
#include "Graph.hpp"

int main()
{
  // DirectableGraph graph(GraphTypes::UNDIRECTED);
  // PonderableGraph graph(GraphTypes::UNDIRECTED, GraphTypes::UNWEIGHTED);
  Graph<> graph(GraphTypes::UNDIRECTED, GraphTypes::UNWEIGHTED, GraphTypes::NOCONTENT);

  /*********** Constructeur initial *****************/
  //Les prédicats
  assert( graph.is_empty() );
  assert( !graph.has_node(1) );
  assert( !graph.has_edge(1,2) );
  assert( !graph.is_directed() );
  assert( !graph.is_weighted() );
  assert( !graph.is_container() );

  //Les tailles
  assert( graph.nodes_size() == 0 );
  assert( graph.edges_size() == 0 );

  //les caractéristiques du graphe
  assert( graph.nodeType() == GraphTypes::NOCONTENT );
  assert( graph.edgeType() == GraphTypes::UNDIRECTED );
  assert( graph.edgeState() == GraphTypes::UNWEIGHTED );

  //les métriques
  try
    {
      graph.in_degree(100);
      assert( "graph.in_degree(100)" == "echec" );
    }
  catch(const GraphException::InvalidNodeID & e){}

  try
    {
      graph.out_degree(1);
      assert("graph.out_degree(1)" == "echec");
    }

  catch(const GraphException::InvalidNodeID & e){}

  try
    {
      graph.degree(2);
      assert("graph.degree(2)" == "echec");
    }

  catch(const GraphException::InvalidNodeID & e){}

  //les itérateurs
  assert( graph.nodes_begin() == graph.nodes_end() );
  assert( graph.edges_begin() == graph.edges_end() );

  try
    {
      graph.successors_begin(100);
      assert("graph.successors_begin(100)" == "echec");
    }

  catch(const GraphException::InvalidOperation & e){}

  try
    {
      graph.successors_end(1);
      assert("graph.successors_end(1)" == "echec");
    }

  catch(const GraphException::InvalidOperation & e){}

  try
    {
      graph.predecessors_begin(100);
      assert("graph.predecessors_begin(100)" == "echec");
    }

  catch(const GraphException::InvalidOperation & e){}

  try
    {
      graph.predecessors_end(1);
      assert("graph.predecessors_end(1)" == "echec");
    }

  catch(const GraphException::InvalidOperation & e){}

  try
    {
      graph.adjacents_begin(100);
      assert("graph.adjacents_begin(100)" == "echec");
    }

  catch(const GraphException::InvalidNodeID & e){}

  try
    {
      graph.adjacents_end(1);
      assert("graph.adjacents_end(1)" == "echec");
    }

  catch(const GraphException::InvalidNodeID & e){}

  //Composition avec les constructeurs
  graph.remove_node(1);
  graph.remove_edge(2,3);


  /******** add_node ******/
  graph.add_node(1);

  //Les prédicats
  assert( !graph.is_empty() );
  assert( !graph.has_node(2) );
  assert( graph.has_node(1) );
  assert( !graph.has_edge(1,1) );
  assert( !graph.has_edge(1,2) );
  assert( !graph.is_directed() );
  assert( !graph.is_weighted() );
  assert( !graph.is_container() );

  //Les tailles
  assert( graph.nodes_size() == 1 );
  assert( graph.edges_size() == 0 );

  //les caractéristiques du graphe
  assert( graph.nodeType() == GraphTypes::NOCONTENT );
  assert( graph.edgeType() == GraphTypes::UNDIRECTED );
  assert( graph.edgeState() == GraphTypes::UNWEIGHTED );

  //les métriques
  assert( graph.in_degree(1) == 0 );
  assert( graph.out_degree(1) == 0 );
  assert( graph.degree(1) == 0 );

  //les itérateurs
  assert( *graph.nodes_begin() == 1 );
  assert( ++graph.nodes_begin() == graph.nodes_end() );
  assert( graph.edges_begin() == graph.edges_end() );

  try
    {
      graph.successors_begin(1);
      assert("graph.successors_begin(1)" == "echec");
    }

  catch(const GraphException::InvalidOperation & e){}


  try
    {
      graph.predecessors_begin(1);
      assert("graph.predecessors_begin(1)" == "echec");
    }

  catch(const GraphException::InvalidOperation & e){}

  assert( graph.adjacents_begin(1) == graph.adjacents_end(1) );


  /******** remove_node ******/
  graph.remove_node(2);
  graph.remove_node(1);

  //Les prédicats
  assert( graph.is_empty() );
  assert( !graph.has_node(2) );
  assert( !graph.has_node(1) );
  assert( !graph.has_edge(1,1) );
  assert( !graph.has_edge(1,2) );

  //Les tailles
  assert( graph.nodes_size() == 0 );
  assert( graph.edges_size() == 0 );

  //les caractéristiques du graphe
  assert( graph.nodeType() == GraphTypes::NOCONTENT );
  assert( graph.edgeType() == GraphTypes::UNDIRECTED );
  assert( graph.edgeState() == GraphTypes::UNWEIGHTED );

  //les métriques
  try
    {
      graph.in_degree(1);
      assert("graph.in_degree(1)" == "echec");
    }

  catch(const GraphException::InvalidNodeID & e){}

  try
    {
      graph.out_degree(1);
      assert("graph.out_degree(1)" == "echec");
    }

  catch(const GraphException::InvalidNodeID & e){}

  try
    {
      graph.degree(2);
      assert("graph.degree(2)" == "echec");
    }

  catch(const GraphException::InvalidNodeID & e){}

  //les itérateurs
  assert( graph.nodes_begin() == graph.nodes_end() );
  assert( graph.edges_begin() == graph.edges_end() );

  try
    {
      graph.successors_begin(100);
      assert("graph.successors_begin(100)" == "echec");
    }

  catch(const GraphException::InvalidOperation & e){}

  try
    {
      graph.successors_end(1);
      assert("graph.successors_end(1)" == "echec");
    }

  catch(const GraphException::InvalidOperation & e){}

  try
    {
      graph.predecessors_begin(100);
      assert("graph.predecessors_begin(100)" == "echec");
    }

  catch(const GraphException::InvalidOperation & e){}

  try
    {
      graph.predecessors_end(1);
      assert("graph.predecessors_end(1)" == "echec");
    }

  catch(const GraphException::InvalidOperation & e){}

  try
    {
      graph.adjacents_begin(100);
      assert("graph.adjacents_begin(100)" == "echec");
    }

  catch(const GraphException::InvalidNodeID & e){}

  try
    {
      graph.adjacents_end(1);
      assert("graph.adjacents_end(1)" == "echec");
    }

  catch(const GraphException::InvalidNodeID & e){}


  /******** add_edge ******/
  graph.add_edge(1,2);
  graph.add_edge(3,4);

  //Les prédicats
  assert( !graph.is_empty() );

  assert( graph.has_node(1) );
  assert( graph.has_node(2) );
  assert( graph.has_node(3) );
  assert( graph.has_node(4) );
  assert( !graph.has_node(0) );

  assert( !graph.has_edge(1,1) );
  assert( !graph.has_edge(1,3) );
  assert( graph.has_edge(1,2) );
  assert( graph.has_edge(2,1) );
  assert( graph.has_edge(3,4) );
  assert( graph.has_edge(4,3) );

  assert( !graph.is_directed() );
  assert( !graph.is_weighted() );
  assert( !graph.is_container() );

  //Les tailles
  assert( graph.nodes_size() == 4 );
  assert( graph.edges_size() == 2 );

  //les caractéristiques du graphe
  assert( graph.nodeType() == GraphTypes::NOCONTENT );
  assert( graph.edgeType() == GraphTypes::UNDIRECTED );
  assert( graph.edgeState() == GraphTypes::UNWEIGHTED );

  //les métriques
  assert( graph.in_degree(1) == 1 );
  assert( graph.in_degree(2) == 1 );
  assert( graph.in_degree(3) == 1 );
  assert( graph.in_degree(4) == 1 );

  assert( graph.out_degree(1) == 1 );
  assert( graph.out_degree(2) == 1 );
  assert( graph.out_degree(3) == 1 );
  assert( graph.out_degree(4) == 1 );

  assert( graph.degree(1) == 1 );
  assert( graph.degree(4) == 1 );

  //les itérateurs
  assert( *graph.nodes_begin() == 1 );
  assert( *(++graph.nodes_begin()) == 2 );
  assert( ++ ++ ++ ++graph.nodes_begin() == graph.nodes_end() );

  assert( *graph.edges_begin() == Edge(1,2) );
  assert( *(++graph.edges_begin()) == Edge(3,4) );
  assert( ++ ++graph.edges_begin() == graph.edges_end() );

  assert( *(--graph.edges_end()) == Edge(3,4) );
  assert( *(-- --graph.edges_end()) == Edge(1,2) );
  assert( -- --graph.edges_end() == graph.edges_begin() );

  assert( *graph.adjacents_begin(1) == 2 );
  assert( *graph.adjacents_begin(3) == 4 );
  assert( *graph.adjacents_begin(2) == 1 );
  assert( *graph.adjacents_begin(4) == 3 );

  assert(++graph.adjacents_begin(1) == graph.adjacents_end(1) );
  assert(++graph.adjacents_begin(2) == graph.adjacents_end(2) );
  assert(++graph.adjacents_begin(3) == graph.adjacents_end(3) );
  assert(++graph.adjacents_begin(4) == graph.adjacents_end(4) );

  assert(--graph.adjacents_end(1) == graph.adjacents_begin(1) );
  assert(--graph.adjacents_end(2) == graph.adjacents_begin(2) );
  assert(--graph.adjacents_end(3) == graph.adjacents_begin(3) );
  assert(--graph.adjacents_end(4) == graph.adjacents_begin(4) );

  graph.add_edge(2,3);
  GraphTypes::node_id adj1 = *graph.adjacents_begin(2);
  GraphTypes::node_id adj2 = *(++graph.adjacents_begin(2));
  assert( graph.degree(2) == graph.degree(3) && graph.degree(3) == 2 );
  assert( adj1 == 1 || adj1 == 3);
  assert( adj2 == 1 || adj2 == 3);
  assert( ( !(adj1 == 1) ) || (adj2 == 3 ) );
  assert( ( !(adj1 == 3) ) || (adj2 == 1 ) );
  assert( ++ ++graph.adjacents_begin(2) == graph.adjacents_end(2) );

  adj1 = *(--graph.adjacents_end(2));
  adj2 = *(-- --graph.adjacents_end(2));
  assert( adj1 == 1 || adj1 == 3);
  assert( adj2 == 1 || adj2 == 3);
  assert( ( !(adj1 == 1) ) || (adj2 == 3 ) );
  assert( ( !(adj1 == 3) ) || (adj2 == 1 ) );
  assert( -- --graph.adjacents_end(2) == graph.adjacents_begin(2) );
  graph.remove_edge(2,3);


  /******** remove_edge ******/
  graph.remove_edge(1,2);

  //Les prédicats
  assert( !graph.is_empty() );

  assert( graph.has_node(1) );
  assert( graph.has_node(2) );
  assert( graph.has_node(3) );
  assert( graph.has_node(4) );

  assert( !graph.has_edge(1,1) );
  assert( !graph.has_edge(1,2) );
  assert( !graph.has_edge(2,1) );
  assert( graph.has_edge(3,4) );
  assert( graph.has_edge(4,3) );

  assert( !graph.is_directed() );
  assert( !graph.is_weighted() );
  assert( !graph.is_container() );

  //Les tailles
  assert( graph.nodes_size() == 4 );
  assert( graph.edges_size() == 1 );

  //les caractéristiques du graphe
  assert( graph.nodeType() == GraphTypes::NOCONTENT );
  assert( graph.edgeType() == GraphTypes::UNDIRECTED );
  assert( graph.edgeState() == GraphTypes::UNWEIGHTED );

  //les métriques
  assert( graph.in_degree(1) == 0 );
  assert( graph.in_degree(2) == 0 );
  assert( graph.in_degree(3) == 1 );
  assert( graph.in_degree(4) == 1 );

  assert( graph.out_degree(1) == 0 );
  assert( graph.out_degree(2) == 0 );
  assert( graph.out_degree(3) == 1 );
  assert( graph.out_degree(4) == 1 );

  assert( graph.degree(1) == 0 );
  assert( graph.degree(2) == 0 );
  assert( graph.degree(3) == 1 );
  assert( graph.degree(4) == 1 );

  //les itérateurs
  assert( *graph.nodes_begin() == 1 );
  assert( *(++graph.nodes_begin()) == 2 );
  assert( ++ ++ ++ ++graph.nodes_begin() == graph.nodes_end() );

  assert( *graph.edges_begin() == Edge(3,4) );
  assert( ++graph.edges_begin() == graph.edges_end() );

  assert( *(--graph.edges_end()) == Edge(3,4) );
  assert( --graph.edges_end() == graph.edges_begin() );

  assert( graph.adjacents_begin(1) == graph.adjacents_end(1) );
  assert( graph.adjacents_begin(2) == graph.adjacents_end(2) );
  assert( *graph.adjacents_begin(3) == 4 );
  assert( *graph.adjacents_begin(4) == 3 );

  assert(++graph.adjacents_begin(3) == graph.adjacents_end(3) );
  assert(++graph.adjacents_begin(4) == graph.adjacents_end(4) );

  assert(--graph.adjacents_end(3) == graph.adjacents_begin(3) );
  assert(--graph.adjacents_end(4) == graph.adjacents_begin(4) );


  std::cout << std::endl << "You can trust your program !!" << std::endl << std::endl;

  return 0;
}
