#ifndef _WeightsTransformer
#define _WeightsTransformer

#include "Graph.hpp"

template<typename Type=GraphTypes::Default>
class WeightsTransformer
{
public:
  Graph<Type> invert_weights_signs(Graph<Type> & graph);
  GraphTypes::Cost get_zero_offset(Graph<Type> & graph);
  Graph<Type> translate_weights(Graph<Type> & graph, const GraphTypes::Cost & offset);
  Graph<Type> translate_weights(Graph<Type> & graph);
  Graph<Type> reverse_weights_order(Graph<Type> & graph);
  template<typename V>
  Graph<Type> update_subgraph(Graph<Type> & graph, Graph<V> & subgraph);
};

#include "WeightsTransformer.cpp"

#endif
