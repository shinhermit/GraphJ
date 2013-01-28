#include <iostream>
#include <string>
#include <cstdlib>
#include "Graph.hpp"
#include "PathFinding.hpp"
#include "GraphConverter.hpp"
#include "Exporter.hpp"

int main(){
  Graph<> graph(GraphTypes::UNDIRECTED, GraphTypes::WEIGHTED, GraphTypes::NOCONTENT);
  std::map<GraphTypes::node_id, std::string> label_mapper;
  Graph<> allPaths_dijkstra( GraphTypes::DIRECTED, graph.edgeState(), GraphTypes::NOCONTENT);
  Graph<> allPaths_bellman( GraphTypes::DIRECTED, graph.edgeState(), GraphTypes::NOCONTENT);
  Graph<> allPaths_greedy_bellman( GraphTypes::DIRECTED, graph.edgeState(), GraphTypes::NOCONTENT);
  std::list<GraphTypes::Path> dijkstra_between, bellman_between, greedy_bellman_between;
  GraphTypes::node_id sourceNode, targetNode;
  PathFinding<> lookup;

  typedef GraphConverter<> Convert;
  typedef Exporter<> Export;

  //On ajoute les villes (noeuds)
  label_mapper.insert( std::pair<GraphTypes::node_id, std::string>(1,"Artigueloutan") );
  label_mapper.insert( std::pair<GraphTypes::node_id, std::string>(2,"Billère") );
  label_mapper.insert( std::pair<GraphTypes::node_id, std::string>(3,"Bizanos") );
  label_mapper.insert( std::pair<GraphTypes::node_id, std::string>(4,"Gan") );
  label_mapper.insert( std::pair<GraphTypes::node_id, std::string>(5,"Gelos") );
  label_mapper.insert( std::pair<GraphTypes::node_id, std::string>(6,"Idron") );
  label_mapper.insert( std::pair<GraphTypes::node_id, std::string>(7,"Jurançon") );
  label_mapper.insert( std::pair<GraphTypes::node_id, std::string>(8,"Lescar") );
  label_mapper.insert( std::pair<GraphTypes::node_id, std::string>(9,"Lons") );
  label_mapper.insert( std::pair<GraphTypes::node_id, std::string>(10,"Mazères-Lezons") );
  label_mapper.insert( std::pair<GraphTypes::node_id, std::string>(11,"Ousse") );
  label_mapper.insert( std::pair<GraphTypes::node_id, std::string>(12,"Pau") );
  label_mapper.insert( std::pair<GraphTypes::node_id, std::string>(13,"Sendets") );

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
    //traitements
    sourceNode = 2;//Billères
    targetNode = 13;//Sendet

    //tests
    Export::ToGraphviz(graph, label_mapper, "undirected_before.graph");
    system("dot -Tpng undirected_before.graph -o undirected_before.png");

    graph = Convert::ToDirected(graph);

    allPaths_dijkstra = lookup.dijkstra(graph, sourceNode);
    allPaths_bellman = lookup.bellman(graph, sourceNode);
    allPaths_greedy_bellman = lookup.bellman(graph, sourceNode, GraphTypes::Algorithms::GREEDY);

    dijkstra_between = lookup.paths_to(allPaths_dijkstra, targetNode);
    bellman_between = lookup.paths_to(allPaths_bellman, targetNode);
    greedy_bellman_between = lookup.paths_to(allPaths_greedy_bellman, targetNode);

    //tests
    Export::ToGraphviz(Convert::ToUndirected(graph), label_mapper, "undirected_after.graph");
    system("dot -Tpng undirected_after.graph -o undirected_after.png");

    //exports
    // std::cout << Export::ToMathString(graph, label_mapper) << std::endl << std::endl;
    Export::ToGraphviz(graph, label_mapper, "reseau_routier.graph");

    Export::ToGraphviz(allPaths_dijkstra, label_mapper, "chemins_dijkstra.graph");
    Export::ToGraphviz(allPaths_bellman, label_mapper, "chemins_bellman.graph");

    Export::ToGraphviz(allPaths_greedy_bellman, label_mapper, "chemins_bellman_rapide.graph");

    Export::ToGraphviz(graph, label_mapper, dijkstra_between, "highlight_dijkstra.graph");
    Export::ToGraphviz(graph, label_mapper, bellman_between, "highlight_bellman.graph");
    Export::ToGraphviz(graph, label_mapper, greedy_bellman_between, "highlight_greedy_bellman.graph");

    //compilations dot
    system("dot -Tpng reseau_routier.graph -o reseau_routier.png");

    system("dot -Tpng chemins_dijkstra.graph -o chemins_dijkstra.png");
    system("dot -Tpng chemins_bellman.graph -o chemins_bellman.png");
    system("dot -Tpng chemins_bellman_rapide.graph -o chemins_bellman_rapide.png");

    system("dot -Tpng highlight_dijkstra.graph -o highlight_dijkstra.png");
    system("dot -Tpng highlight_bellman.graph -o highlight_bellman.png");
    system("dot -Tpng highlight_greedy_bellman.graph -o highlight_greedy_bellman.png");

    //affichages
    std::cout << "Le graphe du réseau routier a été exporté dans le fichier reseau_routier.graph" << std::endl;
    std::cout << "dot -Tpng reseau_routier.graph -o reseau_routier.png" << std::endl << std::endl;

    std::cout << "dot -Tpng chemins_dijkstra.graph -o chemins_dijkstra.png" << std::endl;
    std::cout << "Le graphe des chemins par Dijkstra a été exporté dans le fichier chemins_dijkstra.png" << std::endl << std::endl;

    std::cout << "dot -Tpng chemins_bellman.graph -o chemins_bellman.png" << std::endl;
    std::cout << "Le graphe des chemins par Bellman a été exporté dans le fichier chemins_bellman.png" << std::endl << std::endl;

    std::cout << "dot -Tpng chemins_bellman_rapide.graph -o chemins_bellman_rapide.png" << std::endl;
    std::cout << "Le graphe des chemins par Bellman a été exporté dans le fichier chemins_bellman_rapide.png" << std::endl << std::endl;

    std::cout << "dot -Tpng highlight_dijkstra.graph -o highlight_dijkstra.png" << std::endl;
    std::cout << "Les chemins optimaux entre les deux villes sont visibles sur l'image highlight_dijkstra.png" << std::endl << std::endl;

    std::cout << "dot -Tpng highlight_bellman.graph -o highlight_bellman.png" << std::endl;
    std::cout << "Les chemins optimaux entre les deux villes sont visibles sur l'image highlight_bellman.png" << std::endl << std::endl;

    std::cout << "dot -Tpng highlight_greedy_bellman.graph -o highlight_greedy_bellman.png" << std::endl;
    std::cout << "Les chemins optimaux entre les deux villes sont visibles sur l'image highlight_greedy_bellman.png" << std::endl;

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
