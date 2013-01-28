#include <cstdlib>
#include "PathFinding.hpp"
#include "Exporter.hpp"

int main()
{
  Graph<> graph(GraphTypes::DIRECTED, GraphTypes::WEIGHTED, GraphTypes::NOCONTENT);
  Graph<> paths_greedy(graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT);
  Graph<> paths_dynamic(graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT);
  PathFinding<> lookup;

  typedef Exporter<> Export;

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

  paths_greedy = lookup.bellman(graph, 1, GraphTypes::Algorithms::GREEDY);
  paths_dynamic = lookup.bellman(graph, 1, GraphTypes::Algorithms::DYNAMIC);

  //Exports
  Export::ToGraphviz(graph, "test_bellman.graph");
  Export::ToGraphviz(paths_greedy, "greedy_bellman.graph");
  Export::ToGraphviz(paths_dynamic, "dynamic_bellman.graph");

  //compilation dot
  system("dot -Tpng test_bellman.graph -o test_bellman.png");
  system("dot -Tpng greedy_bellman.graph -o greedy_bellman.png");
  system("dot -Tpng dynamic_bellman.graph -o dynamic_bellman.png");

  //affichages
  std::cout << "Graph a été exporté dans le fichier test_bellman.graph" << std::endl;
  std::cout << "Bellman Glouton: Arbre des chemins a été exporté dans le fichier greedy_bellman.graph" << std::endl;
  std::cout << "Bellman Dynamique: Arbre des chemins a été exporté dans le fichier dynamic_bellman.graph" << std::endl;

  std::cout << std::endl << "dot -Tpng test_bellman.graph -o test_bellman.png" << std::endl;
  std::cout << "Graph a été compilé dans le fichier test_bellman.png" << std::endl;
  std::cout << std::endl << "dot -Tpng paths_bellman.graph -o paths_bellman.png" << std::endl;
  std::cout << "Bellman glouton: arbre des chemins a été compilé dans le fichier greedy_bellman.png" << std::endl;
  std::cout << "Bellman dynamique: arbre des chemins a été compilé dans le fichier dynamic_bellman.png" << std::endl;

  return 0;
}
