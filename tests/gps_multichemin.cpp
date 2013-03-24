#include <iostream>
#include <string>
#include <cstdlib>
#include "Graph.hpp"
#include "XPathFinding.hpp"
#include "GraphConverter.hpp"
#include "Exporter.hpp"

int main(){
  Graph<> graph(GraphTypes::UNDIRECTED, GraphTypes::WEIGHTED, GraphTypes::NOCONTENT);
  GraphvizAttributesHolder config, highlight;
  Graph<> allPaths_dijkstra( GraphTypes::DIRECTED, graph.edgeState(), GraphTypes::NOCONTENT);
  Graph<> allPaths_bellman( GraphTypes::DIRECTED, graph.edgeState(), GraphTypes::NOCONTENT);
  std::list<GraphTypes::Path> dijkstra_between, bellman_between;
  GraphTypes::node_id sourceNode, targetNode;
  GraphTypes::Graphviz::StyleAttribute nodeStyle=GraphTypes::Graphviz::StyleAttribute::FILLED;
  XPathFinding<> lookup;

  typedef GraphConverter<> Convert;
  typedef Exporter<> Export;

  //On ajoute les villes (noeuds)
  config.attributesOf(1).setLabel("Artigueloutan");
  config.attributesOf(2).setLabel("Billère");
  config.attributesOf(3).setLabel("Bizanos");
  config.attributesOf(4).setLabel("Gan");
  config.attributesOf(5).setLabel("Gelos");
  config.attributesOf(6).setLabel("Idron");
  config.attributesOf(7).setLabel("Jurançon");
  config.attributesOf(8).setLabel("Lescar");
  config.attributesOf(9).setLabel("Lons");
  config.attributesOf(10).setLabel("Mazères-Lezons");
  config.attributesOf(11).setLabel("Ousse");
  config.attributesOf(12).setLabel("Pau");
  config.attributesOf(13).setLabel("Sendets");

  //On ajoute maintenant les arcs
  //La syntaxe est la suivante:
  //graph.add_edge(noeud1, noeud2, cout en km)
  //Liaisons Artigueloutan
  graph.add_edge(1,4,4.9); //rajoutée (modif2)
  graph.add_edge(1,5,9.1); //rajoutée (modif1)
  graph.add_edge(1,10,12.2);
  graph.add_edge(1,11,3.1);
  graph.add_edge(1,13,4.3);

  //liaisons Billière
  graph.add_edge(2,4,11.1);
  graph.add_edge(2,5,6.9);//rajoutée (modif1)
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
  graph.add_edge(4,10,14.3);
  graph.add_edge(4,12,10.1);

  //liaisons Gelos
  graph.add_edge(5,10,2.2);
  graph.add_edge(5,12,13.2);

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

  try
    {
      //traitements
      sourceNode = 2;//Billères
      targetNode = 1;//Sendet

      //tests
      config.setGraphName("undirected_before");
      Export::ToGraphviz(graph, config, "bin/undirected_before.graph");
      system("dot -Tpng bin/undirected_before.graph -o bin/undirected_before.png");

      graph = Convert::ToDirected(graph);

      lookup.Xdijkstra(graph, sourceNode);
      allPaths_dijkstra = lookup.resultGraph();
      dijkstra_between = lookup.paths_to(targetNode);

      lookup.Xbellman(graph, sourceNode);
      allPaths_bellman = lookup.resultGraph();
      bellman_between = lookup.paths_to(targetNode);

      //tests
      config.setGraphName("undirected_after");
      Export::ToGraphviz(Convert::ToUndirected(graph), config, "bin/undirected_after.graph");
      system("dot -Tpng bin/undirected_after.graph -o bin/undirected_after.png");

      //exports
      config.setGraphName("reseau_routier");
      Export::ToGraphviz(graph, config, "bin/reseau_routier.graph");

      config.setGraphName("chemins_dijkstra");
      Export::ToGraphviz(allPaths_dijkstra, config, "bin/chemins_dijkstra.graph");

      config.setGraphName("chemins_bellman");
      Export::ToGraphviz(allPaths_bellman, config, "bin/chemins_bellman.graph");

      highlight = config;
      highlight.setGraphName("highlight_dijkstra");
      Export::GraphvizPathsHighlight(highlight, dijkstra_between, nodeStyle);
      Export::ToGraphviz(graph, highlight, "bin/highlight_dijkstra.graph");

      highlight = config;
      highlight.setGraphName("highlight_bellman");
      Export::GraphvizPathsHighlight(highlight, bellman_between, nodeStyle);
      Export::ToGraphviz(graph, highlight, "bin/highlight_bellman.graph");

      //compilations dot
      system("dot -Tpng bin/reseau_routier.graph -o bin/reseau_routier.png");

      system("dot -Tpng bin/chemins_dijkstra.graph -o bin/chemins_dijkstra.png");
      system("dot -Tpng bin/chemins_bellman.graph -o bin/chemins_bellman.png");

      system("dot -Tpng bin/highlight_dijkstra.graph -o bin/highlight_dijkstra.png");
      system("dot -Tpng bin/highlight_bellman.graph -o bin/highlight_bellman.png");

      //affichages
      std::cout << "Le graphe du réseau routier a été exporté dans le fichier reseau_routier.graph" << std::endl;
      std::cout << "dot -Tpng bin/reseau_routier.graph -o bin/reseau_routier.png" << std::endl << std::endl;

      std::cout << "dot -Tpng bin/chemins_dijkstra.graph -o bin/chemins_dijkstra.png" << std::endl;
      std::cout << "Le graphe des chemins par Dijkstra a été exporté dans le fichier chemins_dijkstra.graph" << std::endl << std::endl;

      std::cout << "dot -Tpng bin/chemins_bellman.graph -o bin/chemins_bellman.png" << std::endl;
      std::cout << "Le graphe des chemins par Bellman a été exporté dans le fichier chemins_bellman.graph" << std::endl;

      std::cout << "dot -Tpng bin/highlight_dijkstra.graph -o bin/highlight_dijkstra.png" << std::endl;
      std::cout << "Les chemins optimaux entre les deux villes sont visibles sur l'image highlight_dijkstra.png" << std::endl << std::endl;

      std::cout << "dot -Tpng bin/highlight_bellman.graph -o bin/highlight_bellman.png" << std::endl;
      std::cout << "Les chemins optimaux entre les deux villes sont visibles sur l'image highlight_bellman.png" << std::endl;

    }

  catch(const GraphException::InvalidOperation & io)
    {
      std::cout << "Caught GraphException::InvalidOperation:" << std::endl << io.what() << std::endl;
    }

  catch(const GraphException::InvalidNodeID & in)
    {
      std::cout << "Caught GraphException::InvalidNodeID:" << std::endl << in.what() << std::endl;
    }

  catch(const GraphException::InvalidEdge & ie)
    {
      std::cout << "Caught GraphException::InvalidEdge:" << std::endl << ie.what() << std::endl;
    }

  catch(const GraphException::BasicGraphException & bge)
    {
      std::cout << "Caught GraphException::BasicGraphException:" << std::endl << bge.what() << std::endl;
    }

  catch(std::exception & e)
    {
      std::cout << "Caught exception:" << std::endl << e.what() << std::endl;
    }

  catch(...)
    {
      std::cout << "Caught unexpected exception." << std::endl;
    }

  return 0;
}
