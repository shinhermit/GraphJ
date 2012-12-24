#ifndef _WeightsTransformer
#define _WeightsTransformer

#include "Graph.hpp"

template<typename Type=GraphTypes::Default>
class WeightsTransformer
{
private:
  void _invert_weights_signs(Graph<Type> & graph);

public:
  GraphTypes::Cost get_zero_offset(const Graph<Type> & graph);
  Graph<Type> translate_weights(const Graph<Type> & graph, const GraphTypes::Cost & offset);
  Graph<Type> translate_weights(const Graph<Type> & graph);
  Graph<Type> reverse_weights_order(const Graph<Type> & graph);
  template<typename V>
  Graph<Type> update_subgraph(const Graph<Type> & graph, const Graph<V> & subgraph);
};

#include "WeightsTransformer.cpp"

#endif
