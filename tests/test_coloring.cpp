#include <iostream>
#include "Graph.hpp"
#include "Coloring.hpp"
#include "NamedColor.hpp"
#include "Exporter.hpp"

int main(){
  Graph<> graph(GraphTypes::UNDIRECTED, GraphTypes::UNWEIGHTED, GraphTypes::NOCONTENT);
  Coloring<> coloring;
  Exporter<> exporte;
  std::map<GraphTypes::node_id, NamedColor::ColorName> color_mapper;

  /*
    Graphe de l'exemple du cours (section 6-Algorithme de Welsh-Powell)
  */

  graph.add_edge(1,2);
  graph.add_edge(1,3);
  graph.add_edge(2,3);
  graph.add_edge(2,4);
  graph.add_edge(2,7);
  graph.add_edge(3,4);
  graph.add_edge(3,7);
  graph.add_edge(4,5);
  graph.add_edge(4,7);
  graph.add_edge(5,6);
  graph.add_edge(5,7);
  graph.add_edge(6,7);

  std::cout << exporte.toGraphviz(graph) << std::endl;

  color_mapper = coloring.welsh(graph);

  std::cout << "Résultat de la coloration:" << std::endl;
  std::cout << exporte.toGraphviz(graph, color_mapper) << std::endl;

  exporte.toGraphviz(graph, color_mapper, "test_coloring.graph");
  std::cout << "Le graphe a été exporté dans le fichier test_coloring.graph" << std::endl;

  return 0;
}
