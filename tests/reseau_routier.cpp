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
  label_mapper.insert( std::pair<Node::node_id, std::string>(8,"Lescar") );
  label_mapper.insert( std::pair<Node::node_id, std::string>(9,"Lons") );
  label_mapper.insert( std::pair<Node::node_id, std::string>(10,"Mazères-Lezons") );
  label_mapper.insert( std::pair<Node::node_id, std::string>(11,"Ousse") );
  label_mapper.insert( std::pair<Node::node_id, std::string>(12,"Pau") );
  label_mapper.insert( std::pair<Node::node_id, std::string>(13,"Sendets") );

  //On ajoute maintenant les arcs
  //La syntaxe est la suivante:
  //graph.add_edge(noeud1, noeud2, cout en km)
  //Liaisons Artigueloutan
  graph.add_edge(1,10,12.2);
  graph.add_edge(1,11,3.1);
  graph.add_edge(1,13,4.3);

  //liaisons Billière
  graph.add_edge(2,4,11.1);
  graph.add_edge(2,7,4.5);
  graph.add_edge(2,8,5.2);
  graph.add_edge(2,12,2.9);

  //liaisons Bizanos
  graph.add_edge(3,6,5.7);
  graph.add_edge(3,10,2.9);
  graph.add_edge(3,12,2.2);
  
  //liaisons Gan
  graph.add_edge(4,5,8.4);
  graph.add_edge(4,6,13.3);
  graph.add_edge(4,7,8.1);
  graph.add_edge(4,10,9.1);
  graph.add_edge(4,12,10.1);

  //liaisons Gelos
  graph.add_edge(5,10,2.2);
  graph.add_edge(5,12,3.2);

  //liaisons Idron
  graph.add_edge(6,8,13.3);
  graph.add_edge(6,9,10.9);
  graph.add_edge(6,10,5.4);
  graph.add_edge(6,11,4.2);
  graph.add_edge(6,13,5.3);

  //Liaisons Jurançon
  graph.add_edge(7,12,3.6);

  //Liaisons Lescar
  graph.add_edge(8,9,4.2);
  graph.add_edge(8,12,7.9);
  graph.add_edge(8,13,17.4);

  //Liaisons Lons
  graph.add_edge(9,12,5.1);
  graph.add_edge(9,13,14.1);

  //Liaisons Mazères
  graph.add_edge(10,12,4.4);

  //Liaisons Ousse
  graph.add_edge(11,12,10);
  graph.add_edge(11,13,1.9);

  //Liaison Pau
  graph.add_edge(12,13,10.3);

  try{
    std::cout << exporte.toGraphviz(graph, label_mapper) << std::endl << std::endl;
    // std::cout << exporte.toMathString(graph, label_mapper) << std::endl << std::endl;

    exporte.toGraphviz(graph, label_mapper, "reseau_routier.graph");
    std::cout << "Le graphe a été exporté dans le fichier reseau_routier.graph" << std::endl << std::endl;

    std::cout << "Le graphe a été exporté dans le fichier reseau_routier.graph. Compiler:" << std::endl;
    std::cout << "dot -Tpng reseau_routier.graph -o reseau_routier.png" << std::endl << std::endl;

    min_tree = acm.prim(graph);
    std::cout << "Prim:" << std::endl;
    std::cout << exporte.toGraphviz(min_tree, label_mapper) << std::endl;
    std::cout << "Coût: " << min_tree.cost() << std::endl << std::endl;

    exporte.toGraphviz(min_tree, label_mapper, "acm_prim.graph");
    std::cout << "L'arbre a été exporté dans le fichier acm_prim.graph. Compiler:" << std::endl;
    std::cout << "dot -Tpng acm_prim.graph -o acm_prim.png" << std::endl << std::endl;

    min_tree = acm.kruskal(graph);
    std::cout << "Kruskal:" << std::endl;
    std::cout << exporte.toGraphviz(min_tree, label_mapper) << std::endl;
    std::cout << "Coût: " << min_tree.cost() << std::endl << std::endl;

    exporte.toGraphviz(min_tree, label_mapper, "acm_kruskal.graph");
    std::cout << "L'arbre a été exporté dans le fichier acm_kruskal.graph. Compiler:" << std::endl;
    std::cout << "dot -Tpng acm_kruskal.graph -o acm_kruskal.png" << std::endl << std::endl;

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
