#include <cstdlib>
#include "PathFinding.hpp"
#include "WeightsTransformer.hpp"
#include "Exporter.hpp"

int main()
{
  Graph<> graph(GraphTypes::DIRECTED, GraphTypes::WEIGHTED, GraphTypes::NOCONTENT);
  Graph<> allPaths_dijkstra(graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT);
  Graph<> allPaths_bellman(graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT);
  std::list<GraphTypes::Path> paths_dijkstra_between, paths_bellman_between;
  GraphTypes::node_id source, target;
  PathFinding<> lookup;
  GraphvizAttributesHolder config;

  typedef WeightsTransformer<> Transformer;
  typedef Exporter<> Export;

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

  //inversion de l'ordre des poids
  Graph<> reversed = Transformer::Reverse_weights_order(graph);

  //Recherche des chemins
  source = 1;
  target = 6;

try
  {
  lookup.dijkstra(reversed, source);

  allPaths_dijkstra = lookup.resultGraph();
  paths_dijkstra_between = lookup.paths_to(target);

  lookup.bellman(graph, source, GraphTypes::Algorithms::DYNAMIC, GraphTypes::Algorithms::MAXIMIZE);

  allPaths_bellman = lookup.resultGraph();
  paths_bellman_between = lookup.paths_to(target);

  //remettre les vrais poids dans l'arbre des chemins
  allPaths_dijkstra = Transformer::Update_subgraph(graph, allPaths_dijkstra);

  //Exports
  config.setGraphName("dijkstra_maximize");
  Export::GraphvizPathsHighlight(config, paths_dijkstra_between);
  Export::ToGraphviz(graph, config, "dijkstra_maximize.graph");

  Export::ToGraphviz(allPaths_dijkstra, GraphvizAttributesHolder("paths_dijkstra_maximize"), "paths_dijkstra_maximize.graph");

  config.clear();
  config.setGraphName("bellman_maximize");
  Export::GraphvizPathsHighlight(config, paths_bellman_between);
  Export::ToGraphviz(graph, config, "bellman_maximize.graph");

  Export::ToGraphviz(allPaths_bellman, GraphvizAttributesHolder("paths_bellman_maximize"), "paths_bellman_maximize.graph");

#ifdef _SYSTEM

  //compilation dot
  system("dot -Tpng dijkstra_maximize.graph -o dijkstra_maximize.png");
  system("dot -Tpng paths_dijkstra_maximize.graph -o paths_dijkstra_maximize.png");

  system("dot -Tpng bellman_maximize.graph -o bellman_maximize.png");
  system("dot -Tpng paths_bellman_maximize.graph -o paths_bellman_maximize.png");

#endif

  //affichages
  std::cout << "DIJKSTRA: " << std::endl;
  std::cout << "Le graphe a été exporté dans le fichier dijkstra_maximize.graph" << std::endl;
  std::cout << "L'arbre des chemins a été exporté dans le fichier paths_dijkstra_maximize.graph" << std::endl << std::endl;

  std::cout << std::endl << "dot -Tpng dijkstra_maximize.graph -o dijkstra_maximize.png" << std::endl;
  std::cout << std::endl << "dot -Tpng paths_dijkstra_maximize.graph -o paths_dijkstra_maximize.png" << std::endl << std::endl;

  std::cout << "Le graphe a été exporté dans le fichier dijkstra_maximize.png" << std::endl;
  std::cout << "L'arbre des chemins a été exporté dans le fichier dijkstra_maximize.png" << std::endl << std::endl;

  std::cout << std::endl << "BELLMAN: " << std::endl;
  std::cout << "Le graphe a été exporté dans le fichier bellman_maximize.graph" << std::endl;
  std::cout << "L'arbre des chemins a été exporté dans le fichier paths_bellman_maximize.graph" << std::endl << std::endl;

  std::cout << std::endl << "dot -Tpng bellman_maximize.graph -o bellman_maximize.png" << std::endl;
  std::cout << std::endl << "dot -Tpng paths_bellman_maximize.graph -o paths_bellman_maximize.png" << std::endl << std::endl;

  std::cout << "Le graphe a été exporté dans le fichier bellman_maximize.png" << std::endl;
  std::cout << "L'arbre des chemins a été exporté dans le fichier bellman_maximize.png" << std::endl << std::endl;

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

  catch(const std::exception & e)
    {
      std::cout << "Caught exception:" << std::endl << e.what() << std::endl;
    }

  catch(...)
    {
      std::cout << "Caught unexpected exception." << std::endl;
    }

  return 0;
}
