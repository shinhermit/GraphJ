#include <iostream>
#include "Graph.hpp"
#include "Coloring.hpp"
#include "NamedColor.hpp"
#include "Exporter.hpp"

int main()
{
  Graph<> graph(GraphTypes::UNDIRECTED, GraphTypes::UNWEIGHTED, GraphTypes::NOCONTENT);
  std::map<GraphTypes::node_id, GraphTypes::NamedColor::E_NamedColor> color_mapper;

  typedef Coloring<> Coloring;
  typedef Exporter<> Export;

  /*
    Graphe de l'exemple du cours (section 6-Algorithme de Welsh-Powell)
  */

  graph.add_edge(1,2);
  graph.add_edge(1,3);
  graph.add_edge(2,3);
  graph.add_edge(2,4);
  graph.add_edge(2,7);
  graph.add_edge(3,4);
  graph.add_edge(3,7);
  graph.add_edge(4,5);
  graph.add_edge(4,7);
  graph.add_edge(5,6);
  graph.add_edge(5,7);
  graph.add_edge(6,7);

  try
    {
      Coloring::Welsh(graph, color_mapper);

      GraphvizAttributesHolder config("Coloring");
      for(std::map<GraphTypes::node_id, GraphTypes::NamedColor::E_NamedColor>::iterator it = color_mapper.begin();
	  it != color_mapper.end();
	  ++it)
	{
	  config.attributesOf(it->first).setColor(it->second);
	  config.attributesOf(it->first).setStyle(GraphTypes::Graphviz::StyleAttribute::FILLED);
	}

      Export::ToGraphviz(graph, config, "test_coloring.graph");
      std::cout << "Le graphe a été exporté dans le fichier test_coloring.graph" << std::endl;

#ifdef _SYSTEM

      system("dot -Tpng test_coloring.graph -o test_coloring.png");

#endif

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
