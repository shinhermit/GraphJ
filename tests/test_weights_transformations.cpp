#include "Graph.hpp"
#include "WeightsTransformer.hpp"
#include "Exporter.hpp"
#include <cstdlib>
#include <iostream>

int main()
{
  Graph<> graph(GraphTypes::DIRECTED, GraphTypes::WEIGHTED, GraphTypes::NOCONTENT);
  Graph<> negatived( graph.edgeType(), graph.edgeState(), graph.nodeType() );
  Graph<> translated( graph.edgeType(), graph.edgeState(), graph.nodeType() );
  Graph<> translated_positive( graph.edgeType(), graph.edgeState(), graph.nodeType() );
  Graph<> reversed_order( graph.edgeType(), graph.edgeState(), graph.nodeType() );
  Graph<> involution( graph.edgeType(), graph.edgeState(), graph.nodeType() );
  WeightsTransformer<> transformer;
  Exporter<> exporte;
  GraphTypes::Cost offset;

  //construction
  graph.add_edge(1,2, 1);
  graph.add_edge(1,3, 3);
  graph.add_edge(2,3, 4);

  //traitements
  offset = transformer.get_zero_offset(graph);
  negatived = transformer.invert_weights_signs(graph);
  translated = transformer.translate_weights(graph, offset);
  translated_positive = transformer.translate_weights(negatived);
  reversed_order = transformer.reverse_weights_order(graph);
  involution =  transformer.reverse_weights_order(reversed_order);

  //exports
  exporte.toGraphviz(graph, "initial.graph");
  exporte.toGraphviz(negatived, "negative_weights.graph");
  exporte.toGraphviz(translated, "offset_translation.graph");
  exporte.toGraphviz(translated_positive, "positive_translation.graph");
  exporte.toGraphviz(reversed_order, "order_reversion.graph");
  exporte.toGraphviz(involution, "reversion_involution.graph");

  //compilations
  system("dot -Tpng initial.graph -o initial.png");
  system("dot -Tpng negative_weights.graph -o negative_weights.png");
  system("dot -Tpng offset_translation.graph -o offset_translation.png");
  system("dot -Tpng positive_translation.graph -o positive_translation.png");
  system("dot -Tpng order_reversion.graph -o order_reversion.png");
  system("dot -Tpng reversion_involution.graph -o reversion_involution.png");

  //affichages
  std::cout << "dot -Tpng initial.graph -o initial.png" << std::endl;
  std::cout << "Le graphe de départ a été exporté dans le fichier initial.png" << std::endl << std::endl;

  std::cout << "dot -Tpng negative_weights.graph -o negative_weights.png" << std::endl;
  std::cout << "Le graphe des poids transformé en négatifs a été exporté dans le fichier negative_weights.png" << std::endl << std::endl;

  std::cout << "dot -Tpng offset_translation.graph -o offset_translation.png" << std::endl;
  std::cout << "Le graphe de la translation par offset a été exporté dans le fichier offset_translation.png" << std::endl << std::endl;

  std::cout << "dot -Tpng positive_translation.graph -o positive_translation.png" << std::endl;
  std::cout << "Le graphe de translation dans l'espace des positifs a été exporté dans le fichier positive_translation.png" << std::endl << std::endl;

  std::cout << "dot -Tpng order_reversion.graph -o order_reversion.png" << std::endl;
  std::cout << "Le graphe d'inversion de l'ordre des poids a été exporté dans le fichier order_reversion.png" << std::endl << std::endl;

  std::cout << "dot -Tpng reversion_involution.graph -o reversion_involution.png" << std::endl;
  std::cout << "Le graphe d'inversion involutive des poids a été exporté dans le fichier reversion_involution.png" << std::endl << std::endl;

  return 0;
}