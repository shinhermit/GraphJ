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

  try
    {
      lookup.bellman(graph, 1, GraphTypes::Algorithms::GREEDY);
      paths_greedy = lookup.resultGraph();

      lookup.bellman(graph, 1, GraphTypes::Algorithms::DYNAMIC);
      paths_dynamic = lookup.resultGraph();

      //Exports
      Export::ToGraphviz(graph, "bin/test_bellman.graph");
      Export::ToGraphviz(paths_greedy, "bin/greedy_bellman.graph");
      Export::ToGraphviz(paths_dynamic, "bin/dynamic_bellman.graph");

#ifdef _SYSTEM

      //compilation dot
      system("dot -Tpng bin/test_bellman.graph -o bin/test_bellman.png");
      system("dot -Tpng bin/greedy_bellman.graph -o bin/greedy_bellman.png");
      system("dot -Tpng bin/dynamic_bellman.graph -o bin/dynamic_bellman.png");

#endif

      //affichages
      std::cout << "Graph a été exporté dans le fichier test_bellman.graph" << std::endl;
      std::cout << "Bellman Glouton: Arbre des chemins a été exporté dans le fichier greedy_bellman.graph" << std::endl;
      std::cout << "Bellman Dynamique: Arbre des chemins a été exporté dans le fichier dynamic_bellman.graph" << std::endl;

      std::cout << std::endl << "dot -Tpng bin/test_bellman.graph -o bin/test_bellman.png" << std::endl;
      std::cout << "Graph a été compilé dans le fichier test_bellman.png" << std::endl;
      std::cout << std::endl << "dot -Tpng bin/paths_bellman.graph -o bin/paths_bellman.png" << std::endl;
      std::cout << "Bellman glouton: arbre des chemins a été compilé dans le fichier greedy_bellman.png" << std::endl;
      std::cout << "Bellman dynamique: arbre des chemins a été compilé dans le fichier dynamic_bellman.png" << std::endl;

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
