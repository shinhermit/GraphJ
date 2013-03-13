#include <cstdlib>
#include "PathFinding.hpp"
#include "Exporter.hpp"

int main()
{
  Graph<> graph(GraphTypes::DIRECTED, GraphTypes::WEIGHTED, GraphTypes::NOCONTENT);
  PathFinding<> lookup;
  GraphvizAttributesHolder config;
  const GraphTypes::Graphviz::StyleAttribute nodeStyle=GraphTypes::Graphviz::StyleAttribute::FILLED;

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

  try
    {

      //Recherche des chemins
      lookup.dijkstra(graph, 1);

      //Exports
      config.setGraphName("test_dijkstra");
      Export::GraphvizPathsHighlight(config, lookup.paths_to(6), nodeStyle);
      Export::ToGraphviz(graph, config, "test_dijkstra.graph");

      Export::ToGraphviz(lookup.resultGraph(), GraphvizAttributesHolder("paths_dijkstra"), "paths_dijkstra.graph");

#ifdef _SYSTEM

      //compilation dot
      system("dot -Tpng test_dijkstra.graph -o test_dijkstra.png");
      system("dot -Tpng paths_dijkstra.graph -o paths_dijkstra.png");

#endif

      //affichages
      std::cout << "Le graphe a été exporté dans le fichier test_dijkstra.graph" << std::endl;
      std::cout << "L'arbre des chemins a été exporté dans le fichier paths_dijkstra.graph" << std::endl << std::endl;

      std::cout << std::endl << "dot -Tpng test_dijkstra.graph -o test_dijkstra.png" << std::endl;
      std::cout << std::endl << "dot -Tpng paths_dijkstra.graph -o paths_dijkstra.png" << std::endl << std::endl;

      std::cout << "Le graphe a été exporté dans le fichier test_dijkstra.png" << std::endl;
      std::cout << "L'arbre des chemins a été exporté dans le fichier paths_dijkstra.png" << std::endl << std::endl;

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
