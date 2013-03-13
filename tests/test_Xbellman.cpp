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

  try
    {
      lookup.Xbellman(graph, 1);

      //Exports
      config.setGraphName("test_Xbellman");
      Export::GraphvizPathsHighlight(config, lookup.paths_to(5), nodeStyle);
      Export::ToGraphviz(graph, config, "test_Xbellman.graph");

      Export::ToGraphviz(lookup.resultGraph(), GraphvizAttributesHolder("paths_Xbellman"), "paths_Xbellman.graph");

#ifdef _SYSTEM

      //compilation dot
      system("dot -Tpng test_Xbellman.graph -o test_Xbellman.png");
      system("dot -Tpng paths_Xbellman.graph -o paths_Xbellman.png");

#endif

      //affichages
      std::cout << "Graph a été exporté dans le fichier test_Xbellman.graph" << std::endl;
      std::cout << "Arbre des chemins a été exporté dans le fichier paths_Xbellman.graph" << std::endl;

      std::cout << std::endl << "dot -Tpng test_Xbellman.graph -o test_Xbellman.png" << std::endl;
      std::cout << "Graph a été compilé dans le fichier test_Xbellman.png" << std::endl;
      std::cout << std::endl << "dot -Tpng paths_Xbellman.graph -o paths_Xbellman.png" << std::endl;
      std::cout << "Arbre des chemins a été compilé dans le fichier paths_Xbellman.png" << std::endl;
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
