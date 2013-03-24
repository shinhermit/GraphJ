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
  GraphTypes::Cost offset;

  typedef WeightsTransformer<> Transformer;
  typedef Exporter<> Export;

  //construction
  graph.add_edge(1,2, 1);
  graph.add_edge(1,3, 3);
  graph.add_edge(2,3, 4);

  try
    {
      //traitements
      offset = Transformer::Get_zero_offset(graph);
      negatived = Transformer::Invert_weights_signs(graph);
      translated = Transformer::Translate_weights(graph, offset);
      translated_positive = Transformer::Translate_weights(negatived);
      reversed_order = Transformer::Reverse_weights_order(graph);
      involution =  Transformer::Reverse_weights_order(reversed_order);

      //exports
      Export::ToGraphviz(graph, "bin/initial.graph");
      Export::ToGraphviz(negatived, "bin/negative_weights.graph");
      Export::ToGraphviz(translated, "bin/offset_translation.graph");
      Export::ToGraphviz(translated_positive, "bin/positive_translation.graph");
      Export::ToGraphviz(reversed_order, "bin/order_reversion.graph");
      Export::ToGraphviz(involution, "bin/reversion_involution.graph");

#ifdef _SYSTEM

      //compilations
      system("dot -Tpng bin/initial.graph -o bin/initial.png");
      system("dot -Tpng bin/negative_weights.graph -o bin/negative_weights.png");
      system("dot -Tpng bin/offset_translation.graph -o bin/offset_translation.png");
      system("dot -Tpng bin/positive_translation.graph -o bin/positive_translation.png");
      system("dot -Tpng bin/order_reversion.graph -o bin/order_reversion.png");
      system("dot -Tpng bin/reversion_involution.graph -o bin/reversion_involution.png");

#endif

      //affichages
      std::cout << "dot -Tpng bin/initial.graph -o bin/initial.png" << std::endl;
      std::cout << "Le graphe de départ a été exporté dans le fichier initial.png" << std::endl << std::endl;

      std::cout << "dot -Tpng bin/negative_weights.graph -o bin/negative_weights.png" << std::endl;
      std::cout << "Le graphe des poids transformé en négatifs a été exporté dans le fichier negative_weights.png" << std::endl << std::endl;

      std::cout << "dot -Tpng bin/offset_translation.graph -o bin/offset_translation.png" << std::endl;
      std::cout << "Le graphe de la translation par offset a été exporté dans le fichier offset_translation.png" << std::endl << std::endl;

      std::cout << "dot -Tpng bin/positive_translation.graph -o bin/positive_translation.png" << std::endl;
      std::cout << "Le graphe de translation dans l'espace des positifs a été exporté dans le fichier positive_translation.png" << std::endl << std::endl;

      std::cout << "dot -Tpng bin/order_reversion.graph -o bin/order_reversion.png" << std::endl;
      std::cout << "Le graphe d'inversion de l'ordre des poids a été exporté dans le fichier order_reversion.png" << std::endl << std::endl;

      std::cout << "dot -Tpng bin/reversion_involution.graph -o bin/reversion_involution.png" << std::endl;
      std::cout << "Le graphe d'inversion involutive des poids a été exporté dans le fichier reversion_involution.png" << std::endl << std::endl;
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
