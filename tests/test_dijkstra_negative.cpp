#include <cstdlib>
#include "PathFinding.hpp"
#include "WeightsTransformer.hpp"
#include "Exporter.hpp"

int main()
{
  Graph<> graph(GraphTypes::DIRECTED, GraphTypes::WEIGHTED, GraphTypes::NOCONTENT);
  Graph<> allPaths(graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT);
  Graph<> allPaths_trans(graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT);
  std::list<GraphTypes::Path> paths_between;
  std::list<GraphTypes::Path> trans_paths_between;
  GraphTypes::ComputingValidity validity, trans_validity;
  GraphTypes::node_id source, target;
  std::string validity_text;
  WeightsTransformer<> transformer;
  PathFinding<> lookup;
  Exporter<> exporte;

  //construction
  graph.add_edge(1,3, 2);
  graph.add_edge(1,2, 3);
  graph.add_edge(2,3, -2);

  //inversion de l'ordre des poids
  Graph<> translated = transformer.translate_weights(graph);

  //Recherche des chemins
  source = 1;
  target = 3;

  allPaths = lookup.dijkstra(graph, source);
  paths_between = lookup.paths_to(allPaths, target);
  validity = lookup.validity();

  allPaths_trans = lookup.dijkstra(translated, source);
  trans_paths_between = lookup.paths_to(allPaths_trans, target);
  trans_validity = lookup.validity();

  //remettre les vrais poids dans l'arbre des chemins
  allPaths_trans = transformer.update_subgraph(graph, allPaths_trans);

  //Exports
  exporte.toGraphviz(translated, "translated.graph");

  exporte.toGraphviz(graph, paths_between, "test_dijkstra_neg.graph");
  exporte.toGraphviz(allPaths, "paths_dijkstra_neg.graph");

  exporte.toGraphviz(graph, trans_paths_between, "test_dijkstra_trans.graph");
  exporte.toGraphviz(allPaths_trans, "paths_dijkstra_trans.graph");

  //compilation dot
  system("dot -Tpng translated.graph -o translated.png");

  system("dot -Tpng test_dijkstra_neg.graph -o test_dijkstra_neg.png");
  system("dot -Tpng paths_dijkstra_neg.graph -o paths_dijkstra_neg.png");

  system("dot -Tpng test_dijkstra_trans.graph -o test_dijkstra_trans.png");
  system("dot -Tpng paths_dijkstra_trans.graph -o paths_dijkstra_trans.png");

  //affichages
  std::cout << std::endl << "AVANT translation: " << std::endl;
  std::cout << "Le graphe a été exporté dans le fichier test_dijkstra_neg.graph" << std::endl;
  std::cout << "L'arbre des chemins a été exporté dans le fichier paths_dijkstra_neg.graph" << std::endl;
  std::cout << "dot -Tpng test_dijkstra_neg.graph -o test_dijkstra_neg.png" << std::endl;
  std::cout << "dot -Tpng paths_dijkstra_neg.graph -o paths_dijkstra_neg.png" << std::endl;
  validity_text = (validity == GraphTypes::VALID) ? "VALIDE" : "INVALIDE";
  std::cout << "La vérification du cacul révèle un calcul " << validity_text << std::endl << std::endl; 

  std::cout << "La translation du graphea été exportée dans le fichier translated.graph" << std::endl;
  std::cout << "dot -Tpng translated.graph -o translated.png" << std::endl << std::endl;

  std::cout << std::endl << "APRÈS translation: " << std::endl;
  std::cout << "Le graphe a été exporté dans le fichier test_dijkstra_trans.graph" << std::endl;
  std::cout << "L'arbre des chemins a été exporté dans le fichier paths_dijkstra_trans.graph" << std::endl;
  std::cout << "dot -Tpng test_dijkstra_trans.graph -o test_dijkstra_trans.png" << std::endl;
  std::cout << "dot -Tpng paths_dijkstra_trans.graph -o paths_dijkstra_trans.png" << std::endl;
  validity_text = (trans_validity == GraphTypes::VALID) ? "VALIDE" : "INVALIDE";
  std::cout << "La vérification du cacul révèle un calcul " << validity_text << std::endl << std::endl; 



  return 0;
}
