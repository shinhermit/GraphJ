#include <cstdlib>
#include "PathFinding.hpp"
#include "XPathFinding.hpp"
#include "Exporter.hpp"

int main()
{
  Graph<> graph(GraphTypes::DIRECTED, GraphTypes::WEIGHTED, GraphTypes::NOCONTENT);
  Graph<> paths(graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT);
  XPathFinding<> lookup;
  Exporter<> exporte;

  /*
    exemple du cours, exemple n°1, page 83 (attention, celui la page 82 est différent)
   */
  graph.add_edge(1,2, 10);
  graph.add_edge(1,3, 3);
  graph.add_edge(1,5, 6);
  graph.add_edge(1,6, 2);

  graph.add_edge(3,2, 4);
  graph.add_edge(3,4, 1);
  graph.add_edge(3,5, 2);

  graph.add_edge(5,4, 3);

  graph.add_edge(6,2, 1);
  graph.add_edge(6,5, 1);

  paths = lookup.Xbellman(graph, 1);

  //Exports
  exporte.toGraphviz(graph, "test_bellman.graph");
  exporte.toGraphviz(paths, "paths_bellman.graph");

  //compilation dot
  system("dot -Tpng test_bellman.graph -o test_bellman.png");
  system("dot -Tpng paths_bellman.graph -o paths_bellman.png");

  //affichages
  std::cout << "Graph a été exporté dans le fichier test_bellman.graph" << std::endl;
  std::cout << "Arbre des chemins a été exporté dans le fichier paths_bellman.graph" << std::endl;

  std::cout << std::endl << "dot -Tpng test_bellman.graph -o test_bellman.png" << std::endl;
  std::cout << "Graph a été compilé dans le fichier test_bellman.png" << std::endl;
  std::cout << std::endl << "dot -Tpng paths_bellman.graph -o paths_bellman.png" << std::endl;
  std::cout << "Arbre des chemins a été compilé dans le fichier paths_bellman.png" << std::endl;

  return 0;
}
