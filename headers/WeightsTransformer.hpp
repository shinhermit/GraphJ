#ifndef _WeightsTransformer
#define _WeightsTransformer

#include "Graph.hpp"

template<typename Type=GraphTypes::Default>
class WeightsTransformer
{
public:
  static Graph<Type> Invert_weights_signs(const Graph<Type> & graph);

  static GraphTypes::Cost Get_zero_offset(const Graph<Type> & graph);

  static Graph<Type> Translate_weights(const Graph<Type> & graph,
				       const GraphTypes::Cost & offset);

  static Graph<Type> Translate_weights(const Graph<Type> & graph);

  static Graph<Type> Reverse_weights_order(const Graph<Type> & graph);

  template<typename V>
  static Graph<Type> Update_subgraph(const Graph<Type> & graph,
				     const Graph<V> & subgraph);
};

#include "WeightsTransformer.cpp"

#endif
