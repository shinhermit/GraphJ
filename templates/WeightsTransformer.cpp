template<typename Type>
Graph<Type>  WeightsTransformer<Type>::invert_weights_signs(const Graph<Type> & graph)
{
  typename Graph<Type>::EdgeIterator it;
  GraphTypes::node_id pred,succ;
  Graph<Type> inverted = graph;

  for(it = inverted.edges_begin(); it != inverted.edges_end(); ++it){
    pred = it->source();
    succ = it->target();
    inverted.setCost( pred, succ, 0-graph.getCost(pred,succ) );
  }

  return inverted;
}

template<typename Type>
GraphTypes::Cost WeightsTransformer<Type>::get_zero_offset(const Graph<Type> & graph)
{
  typename Graph<Type>::EdgeIterator edge;
  GraphTypes::Cost cost, min_cost;

  edge = graph.edges_begin();
  min_cost = graph.getCost(*edge);

  ++edge;
  while( edge != graph.edges_end() ){
    cost = graph.getCost(*edge);
    if(cost < min_cost){
      min_cost = cost;
    }

    ++edge;
  }

  return 0-min_cost;
}

template<typename Type>
Graph<Type> WeightsTransformer<Type>::translate_weights(const Graph<Type> & graph, const GraphTypes::Cost & offset)
{
  typename Graph<Type>::EdgeIterator it;
  Edge edge;
  GraphTypes::node_id pred,succ;
  Graph<Type> translated = graph;

  for(it = translated.edges_begin(); it != translated.edges_end(); ++it){
    pred = it->source();
    succ = it->target();
    translated.setCost(pred,succ, graph.getCost(pred,succ)+offset);
  }

  return translated;
}

template<typename Type>
Graph<Type> WeightsTransformer<Type>::translate_weights(const Graph<Type> & graph)
{
  GraphTypes::Cost offset;

  offset = get_zero_offset(graph);

  if(offset > 0){
    return translate_weights(graph, offset);
  }
  else{
    return Graph<Type>(graph);
  }
}

template<typename Type>
Graph<Type> WeightsTransformer<Type>::reverse_weights_order(const Graph<Type> & graph)
{
  GraphTypes::Cost initial_offset, offset;
  Graph<Type> transformed;

  initial_offset = get_zero_offset(graph);
  transformed = invert_weights_signs(graph);
  offset = get_zero_offset(transformed);
  return translate_weights(transformed, offset - initial_offset);
}


template<typename Type>
template<typename V>
Graph<Type> WeightsTransformer<Type>::update_subgraph(const Graph<Type> & graph, const Graph<V> & subgraph)
{
  Graph<Type> updated;
  typename Graph<Type>::EdgeIterator it;
  GraphTypes::node_id pred,succ;

  updated = subgraph;

  for(it = subgraph.edges_begin(); it != subgraph.edges_end(); ++it){
    pred = it->source();
    succ = it->target();
    updated.setCost(pred,succ, graph.getCost(pred,succ));
  }

  return updated;
}
