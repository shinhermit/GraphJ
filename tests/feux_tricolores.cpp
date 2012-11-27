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
  Coloring<Edge> color;
  Traverse<Edge> traverse;
  TricolorBuilderVisitor edgeBuilder(6); //intersection à 6 points
  Exporter<> convert;
  Exporter<Edge> exporte;

  std::map<Node::node_id, std::string> labels1, labels2;
  std::map<Node::node_id, NamedColor::ColorName> color_map;

  //graphe de la relations "il existe un franchissement"
  // Nous faisons coïncider l'ordre lexico-graphique et l'ordre numérique
  // Nous verrons pourquoi plus loin

  labels1[1] = "A";
  labels1[2] = "B";
  labels1[3] = "C";
  labels1[4] = "D";
  labels1[5] = "E";

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
  std::cout << convert.toGraphviz(franchissements, labels1);

  convert.toGraphviz(franchissements, labels1, "franchissements.graph");
  std::cout << "Le graphe a été exporté dans le fichier franchissements.graph" << std::endl << std::endl;
  std::cout << "dot -Tpng franchissements.graph -o franchissements.png" << std::endl << std::endl;


  //graphe de la relations "les franchissements sont compatibles"
  labels2[1] = "AC";
  labels2[2] = "AE";
  labels2[3] = "BA";
  labels2[4] = "BD";
  labels2[5] = "BE";
  labels2[6] = "CA";
  labels2[7] = "CD";
  labels2[8] = "DA";
  labels2[9] = "DC";
  labels2[10] = "EC";
  labels2[11] = "ED";

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
  traverse.nodes(incompatibles, edgeBuilder);

  std::cout << "Graphe des incompatibilités de franchissement" << std::endl;
  std::cout << exporte.toGraphviz(incompatibles, labels2);

  exporte.toGraphviz(incompatibles, labels2, "incompatibles.graph");
  std::cout << "Le graphe a été exporté dans le fichier incompatibles.graph" << std::endl << std::endl;
  std::cout << "dot -Tpng incompatibles.graph -o incompatibles.png" << std::endl << std::endl;

  std::cout << "Coloration des franchissements compatibles" << std::endl;
  color_map = color.welsh(incompatibles);
  std::cout << exporte.toGraphviz(incompatibles, labels2, color_map);

  exporte.toGraphviz(incompatibles, labels2, color_map, "coloration.graph");
  std::cout << "Le graphe a été exporté dans le fichier coloration.graph" << std::endl << std::endl;
  std::cout << "dot -Tpng coloration.graph -o coloration.png" << std::endl << std::endl;

  system("dot -Tpng franchissements.graph -o franchissements.png");
  system("dot -Tpng incompatibles.graph -o incompatibles.png");
  system("dot -Tpng coloration.graph -o coloration.png");

  return 0;
}
