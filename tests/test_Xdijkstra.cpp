#include <cstdlib>
#include "XPathFinding.hpp"
#include "Exporter.hpp"

int main()
{
  Graph<> graph(GraphTypes::DIRECTED, GraphTypes::WEIGHTED, GraphTypes::NOCONTENT);
  Graph<> allPaths(graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT);
  XPathFinding<> lookup;
  Exporter<> exporte;

  /*
    Construction du graphe
    exemple du cours page 43.
   */
  graph.add_edge(1,2, 10);
  graph.add_edge(1,3, 3);
  graph.add_edge(1,5, 6);

  graph.add_edge(2,1, 0);

  graph.add_edge(3,2, 4);
  graph.add_edge(3,5, 2);

  graph.add_edge(4,3, 1);
  graph.add_edge(4,5, 3);

  graph.add_edge(5,2, 0);
  graph.add_edge(5,6, 1);

  graph.add_edge(6,1, 2);
  graph.add_edge(6,2, 1);

  //Recherche des chemins
  allPaths = lookup.Xdijkstra(graph, 1);

  //Exports
  exporte.toGraphviz(graph, "test_dijkstra.graph");
  exporte.toGraphviz(allPaths, "paths_dijkstra.graph");

  //compilation dot
  system("dot -Tpng test_dijkstra.graph -o test_dijkstra.png");
  system("dot -Tpng paths_dijkstra.graph -o paths_dijkstra.png");

  //affichages
  std::cout << "Graph a été exporté dans le fichier test_dijkstra.graph" << std::endl;
  std::cout << "Arbre des chemins a été exporté dans le fichier paths_dijkstra.graph" << std::endl;

  std::cout << std::endl << "dot -Tpng test_dijkstra.graph -o test_dijkstra.png" << std::endl;
  std::cout << "Graph a été compilé dans le fichier test_dijkstra.png" << std::endl;

  std::cout << std::endl << "dot -Tpng paths_dijkstra.graph -o paths_dijkstra.png" << std::endl;
  std::cout << "Arbre des chemins a été compilé dans le fichier paths_dijkstra.png" << std::endl;

  return 0;
}
