#include <iostream>
#include "Graph.hpp"
#include "Coloring.hpp"
#include "Exporter.hpp"
#include "TricolorBuilderVisitor.hpp"
#include <cstdlib>

int main()
{
  Graph<> franchissements(GraphTypes::DIRECTED, GraphTypes::UNWEIGHTED, GraphTypes::NOCONTENT);
  Graph<Edge> incompatibles(GraphTypes::UNDIRECTED, GraphTypes::UNWEIGHTED, GraphTypes::CONTAINER);
  TricolorBuilderVisitor edgeBuilder(incompatibles, 6); //intersection à 6 points

  GraphvizAttributesHolder config1, config2;
  std::map<GraphTypes::node_id, GraphTypes::NamedColor::E_NamedColor> color_mapper;

  typedef Coloring<Edge> Coloring;
  typedef Traverse<Edge> Traverse;
  typedef Exporter<> Convert;
  typedef Exporter<Edge> Export;

  //graphe de la relations "il existe un franchissement"
  // Nous faisons coïncider l'ordre lexico-graphique et l'ordre numérique
  // Nous verrons pourquoi plus loin

  config1.attributesOf(1).setLabel("A");
  config1.attributesOf(2).setLabel("B");
  config1.attributesOf(3).setLabel("C");
  config1.attributesOf(4).setLabel("D");
  config1.attributesOf(5).setLabel("E");

  franchissements.add_edge(1,3);
  franchissements.add_edge(1,5);
  franchissements.add_edge(2,1);
  franchissements.add_edge(2,4);
  franchissements.add_edge(2,5);
  franchissements.add_edge(3,1);
  franchissements.add_edge(3,4);
  franchissements.add_edge(4,1);
  franchissements.add_edge(4,3);
  franchissements.add_edge(5,3);
  franchissements.add_edge(5,4);

  std::cout << "Graphe des franchissements" << std::endl;

  Convert::ToGraphviz(franchissements, config1, "franchissements.graph");
  std::cout << "Le graphe a été exporté dans le fichier franchissements.graph" << std::endl << std::endl;
  std::cout << "dot -Tpng franchissements.graph -o franchissements.png" << std::endl << std::endl;


  //graphe de la relations "les franchissements sont compatibles"
  config2.attributesOf(1).setLabel("AC");
  config2.attributesOf(2).setLabel("AE");
  config2.attributesOf(3).setLabel("BA");
  config2.attributesOf(4).setLabel("BD");
  config2.attributesOf(5).setLabel("BE");
  config2.attributesOf(6).setLabel("CA");
  config2.attributesOf(7).setLabel("CD");
  config2.attributesOf(8).setLabel("DA");
  config2.attributesOf(9).setLabel("DC");
  config2.attributesOf(10).setLabel("EC");
  config2.attributesOf(11).setLabel("ED");

  incompatibles.add_node( 1, Edge(1,3) );
  incompatibles.add_node( 2, Edge(1,5) );
  incompatibles.add_node( 3, Edge(2,1) );
  incompatibles.add_node( 4, Edge(2,4) );
  incompatibles.add_node( 5, Edge(2,5) );
  incompatibles.add_node( 6, Edge(3,1) );
  incompatibles.add_node( 7, Edge(3,4) );
  incompatibles.add_node( 8, Edge(4,1) );
  incompatibles.add_node( 9, Edge(4,3) );
  incompatibles.add_node( 10, Edge(5,3) );
  incompatibles.add_node( 11, Edge(5,4) );

  //construction des arêtes du graphe d'incomatibilité
  // voir les commentaires dans TricolorBuilderVisitor.hpp
  Traverse::Nodes(incompatibles, edgeBuilder);

  // afichage des degrés
  // Graph<Edge>::NodeIterator it_n;
  // for(it_n=incompatibles.nodes_begin(); it_n!=incompatibles.nodes_end(); it_n++){
  //   std::cout << "d°(s" << *it_n << ") = " << incompatibles.degree(*it_n);
  // }

  std::cout << "Graphe des incompatibilités de franchissement" << std::endl;

  Export::ToGraphviz(incompatibles, config2, "incompatibles.graph");
  std::cout << "Le graphe a été exporté dans le fichier incompatibles.graph" << std::endl << std::endl;
  std::cout << "dot -Tpng incompatibles.graph -o incompatibles.png" << std::endl << std::endl;

  std::cout << "Coloration des franchissements compatibles" << std::endl;
  Coloring::Welsh(incompatibles, color_mapper);

  for(std::map<GraphTypes::node_id, GraphTypes::NamedColor::E_NamedColor>::iterator it = color_mapper.begin();
      it != color_mapper.end();
      ++it)
    {
      config2.attributesOf(it->first).setColor(it->second);
      config2.attributesOf(it->first).setStyle(GraphTypes::Graphviz::StyleAttribute::FILLED);
    }

  Export::ToGraphviz(incompatibles, config2, "coloration.graph");
  std::cout << "Le graphe a été exporté dans le fichier coloration.graph" << std::endl << std::endl;
  std::cout << "dot -Tpng coloration.graph -o coloration.png" << std::endl << std::endl;

#ifdef _SYSTEM

  system("dot -Tpng franchissements.graph -o franchissements.png");
  system("dot -Tpng incompatibles.graph -o incompatibles.png");
  system("dot -Tpng coloration.graph -o coloration.png");

#endif

  return 0;
}
