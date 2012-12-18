#include <cstdlib>
#include "XPathFinding.hpp"
#include "Exporter.hpp"

int main()
{
  Graph<> graph(GraphTypes::DIRECTED, GraphTypes::WEIGHTED, GraphTypes::NOCONTENT);
  Graph<> paths(graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT);
  std::list<GraphTypes::Path> paths_between;
  XPathFinding<> lookup;
  Exporter<> exporte;

  /*
    exemple du cours, exemple n°1, page 83 (attention, celui la page 82 est différent)
    AVEC MODIFICATIONS de coûts, pour avoir des chemins équivalents

   */

  graph.add_edge(1,2, 3);//modifié: 10 en 3
  graph.add_edge(1,3, 3);
  graph.add_edge(1,5, 6);
  graph.add_edge(1,6, 2);

  graph.add_edge(3,2, 4);
  graph.add_edge(3,4, 1);
  graph.add_edge(3,5, 0);//modifié: 4 en 0

  graph.add_edge(5,4, 3);

  graph.add_edge(6,2, 1);
  graph.add_edge(6,5, 1);

  paths = lookup.Xbellman(graph, 1);
  paths_between = lookup.paths_to(paths, 5);

  //Exports
  exporte.toGraphviz(graph, paths_between, "test_Xbellman.graph");
  exporte.toGraphviz(paths, "paths_Xbellman.graph");

  //compilation dot
  system("dot -Tpng test_Xbellman.graph -o test_Xbellman.png");
  system("dot -Tpng paths_Xbellman.graph -o paths_Xbellman.png");

  //affichages
  std::cout << "Graph a été exporté dans le fichier test_Xbellman.graph" << std::endl;
  std::cout << "Arbre des chemins a été exporté dans le fichier paths_Xbellman.graph" << std::endl;

  std::cout << std::endl << "dot -Tpng test_Xbellman.graph -o test_Xbellman.png" << std::endl;
  std::cout << "Graph a été compilé dans le fichier test_Xbellman.png" << std::endl;
  std::cout << std::endl << "dot -Tpng paths_Xbellman.graph -o paths_Xbellman.png" << std::endl;
  std::cout << "Arbre des chemins a été compilé dans le fichier paths_Xbellman.png" << std::endl;

  return 0;
}
