#include <iostream>
#include <string>
#include "Graph.hpp"
#include "Acm.hpp"
#include "Exporter.hpp"

int main(){
  Graph<> graph(GraphTypes::UNDIRECTED, GraphTypes::WEIGHTED, GraphTypes::NOCONTENT);
  std::map<Node::node_id, std::string> label_mapper;
  Graph<> min_tree( graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT);
  Acm<> acm;
  Exporter<> exporte;

  //On ajoute les villes (noeuds)
  label_mapper.insert( std::pair<Node::node_id, std::string>(1,"Artigueloutan") );
  label_mapper.insert( std::pair<Node::node_id, std::string>(2,"Billère") );
  label_mapper.insert( std::pair<Node::node_id, std::string>(3,"Bizanos") );
  label_mapper.insert( std::pair<Node::node_id, std::string>(4,"Gan") );
  label_mapper.insert( std::pair<Node::node_id, std::string>(5,"Gelos") );
  label_mapper.insert( std::pair<Node::node_id, std::string>(6,"Idron") );
  label_mapper.insert( std::pair<Node::node_id, std::string>(7,"Jurançon") );
  label_mapper.insert( std::pair<Node::node_id, std::string>(8,"Lons") );
  label_mapper.insert( std::pair<Node::node_id, std::string>(9,"Mazères-Lezons") );
  label_mapper.insert( std::pair<Node::node_id, std::string>(10,"Ousse") );
  label_mapper.insert( std::pair<Node::node_id, std::string>(11,"Pau") );
  label_mapper.insert( std::pair<Node::node_id, std::string>(12,"Sendets") );

  //On ajoute maintenant les arcs
  //La syntaxe est la suivante:
  //graph.add_edge(noeud1, noeud2, cout en km)
  //Liaisons Artigueloutan
  graph.add_edge(1,2,14);
  graph.add_edge(1,3,10);
  graph.add_edge(1,4,18);
  graph.add_edge(1,5,12);
  graph.add_edge(1,6,7);
  graph.add_edge(1,7,14);
  graph.add_edge(1,8,16);
  graph.add_edge(1,9,12);
  graph.add_edge(1,10,3);
  graph.add_edge(1,11,12);
  graph.add_edge(1,12,4);

  //liaisons Billière
  graph.add_edge(2,3,4);
  graph.add_edge(2,4,9);
  graph.add_edge(2,5,3);
  graph.add_edge(2,6,8);
  graph.add_edge(2,7,3);
  graph.add_edge(2,8,2);
  graph.add_edge(2,9,5);
  graph.add_edge(2,10,12);
  graph.add_edge(2,11,3);
  graph.add_edge(2,12,12);

  //liaisons Bizanos
  graph.add_edge(3,4,10);
  graph.add_edge(3,5,3);
  graph.add_edge(3,6,4);
  graph.add_edge(3,7,4);
  graph.add_edge(3,8,6);
  graph.add_edge(3,9,3);
  graph.add_edge(3,10,8);
  graph.add_edge(3,11,2);
  graph.add_edge(3,12,9);
  
  //liaisons Gan
  graph.add_edge(4,5,8);
  graph.add_edge(4,6,14);
  graph.add_edge(4,7,7);
  graph.add_edge(4,8,12);
  graph.add_edge(4,9,9);
  graph.add_edge(4,10,17);
  graph.add_edge(4,11,9);
  graph.add_edge(4,12,18);

  //liaisons Gelos
  graph.add_edge(5,6,6);
  graph.add_edge(5,7,2);
  graph.add_edge(5,8,5);
  graph.add_edge(5,9,2);
  graph.add_edge(5,10,10);
  graph.add_edge(5,11,2);
  graph.add_edge(5,12,11);

  //liaisons Idron
  graph.add_edge(6,7,8);
  graph.add_edge(6,8,10);
  graph.add_edge(6,9,5);
  graph.add_edge(6,10,4);
  graph.add_edge(6,11,6);
  graph.add_edge(6,12,5);

  //Liaisons Jurançon
  graph.add_edge(7,8,6);
  graph.add_edge(7,9,4);
  graph.add_edge(7,10,11);
  graph.add_edge(7,11,2);
  graph.add_edge(7,12,12);

  //Liaisons Lons
  graph.add_edge(8,9,7);
  graph.add_edge(8,10,13);
  graph.add_edge(8,11,5);
  graph.add_edge(8,12,14);

  //Liaisons Mazères
  graph.add_edge(9,10,9);
  graph.add_edge(9,11,4);
  graph.add_edge(9,12,11);

  //Liaisons Ousse
  graph.add_edge(10,11,9);
  graph.add_edge(10,12,2);

  //Liaison Pau
  graph.add_edge(11,12,10);

  try{
    std::cout << exporte.toGraphviz(graph, label_mapper) << std::endl << std::endl;

    exporte.toGraphviz(graph, label_mapper, "cas_pratique.graph");
    std::cout << "Le graphe a été exporté dans le fichier cas_pratique.graph" << std::endl << std::endl;

    min_tree = acm.prim(graph);
    std::cout << "Prim:" << std::endl;
    std::cout << exporte.toGraphviz(min_tree, label_mapper) << std::endl;
    std::cout << "Coût: " << min_tree.cost() << std::endl << std::endl;

    exporte.toGraphviz(min_tree, label_mapper, "cas_pratique_prim.graph");
    std::cout << "Le graphe a été exporté dans le fichier cas_pratique_prim.graph" << std::endl << std::endl;

    min_tree = acm.kruskal(graph);
    std::cout << "Kruskal:" << std::endl;
    std::cout << exporte.toGraphviz(min_tree, label_mapper) << std::endl;
    std::cout << "Coût: " << min_tree.cost() << std::endl << std::endl;

    exporte.toGraphviz(min_tree, label_mapper, "cas_pratique_kruskal.graph");
    std::cout << "Le graphe a été exporté dans le fichier cas_pratique_kruskal.graph" << std::endl << std::endl;

  }
  catch(std::invalid_argument & iv){
    std::cout << "Caught invalid_argument exception:" << std::endl << iv.what() << std::endl;
  }
  catch(std::logic_error & le){
    std::cout << "Caught logic_error exception:" << std::endl << le.what() << std::endl;
  }
  catch(std::exception & e){
    std::cout << "Caught exception:" << std::endl << e.what() << std::endl;
  }
  catch(...){
    std::cout << "Caught unexpected exception." << std::endl;
  }

  return 0;
}
