#include <cstdlib>
#include "XPathFinding.hpp"
#include "Exporter.hpp"

int main()
{
  Graph<> graph(GraphTypes::DIRECTED, GraphTypes::WEIGHTED, GraphTypes::NOCONTENT);
  XPathFinding<> lookup;
  GraphvizAttributesHolder config;
  const GraphTypes::Graphviz::StyleAttribute nodeStyle=GraphTypes::Graphviz::StyleAttribute::FILLED;

  typedef Exporter<> Export;

  /*
    Construction du graphe
    exemple du cours page 43.
    modifié pour avoir des chemins équivalents

    modifications:
    -graph.add_edge(1,5, 5);//coût modifié: 6 en 5
    pour avoir 2 chemins équivalents arrivant en S5 (marche)

    -graph.add_edge(1,2, 5);//coût modifié: 10 en 5
    pour avoir 2 chemins équivalents arrivant en S2
  */

  graph.add_edge(1,2, 5);//coût modifié: 10 en 5
  graph.add_edge(1,3, 3);
  graph.add_edge(1,5, 5);//coût modifié: 6 en 5

  graph.add_edge(2,1, 0);

  graph.add_edge(3,2, 2);//coût modifié: 4 en 2
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
      lookup.Xdijkstra(graph, 1);

      //Exports
      config.setGraphName("test_Xdijkstra");
      Export::GraphvizPathsHighlight(config, lookup.paths_to(5), nodeStyle);
      Export::ToGraphviz(graph, config, "test_Xdijkstra.graph");

      Export::ToGraphviz(lookup.resultGraph(), GraphvizAttributesHolder("paths_Xdijkstra"), "paths_Xdijkstra.graph");

#ifdef _SYSTEM

      //compilation dot
      system("dot -Tpng test_Xdijkstra.graph -o test_Xdijkstra.png");
      system("dot -Tpng paths_Xdijkstra.graph -o paths_Xdijkstra.png");

#endif

      //affichages
      std::cout << "Graph a été exporté dans le fichier test_Xdijkstra.graph" << std::endl;
      std::cout << "Arbre des chemins a été exporté dans le fichier paths_Xdijkstra.graph" << std::endl;

      std::cout << std::endl << "dot -Tpng test_Xdijkstra.graph -o test_Xdijkstra.png" << std::endl;
      std::cout << "Graph a été compilé dans le fichier test_Xdijkstra.png" << std::endl;

      std::cout << std::endl << "dot -Tpng paths_Xdijkstra.graph -o paths_dijkstra.png" << std::endl;
      std::cout << "Arbre des chemins a été compilé dans le fichier paths_Xdijkstra.png" << std::endl;

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
