template<typename Type>
void WeightsTransformer<Type>::_invert_weights_signs(Graph<Type> & graph)
{
  typename Graph<Type>::EdgeIterator edge;
  GraphTypes::node_id u,v;

  for(edge = graph.edges_begin(); edge != graph.edges_end(); edge++){
    u = edge->source();
    v = edge->target();
    graph.setCost( u, v, 0-graph.getCost(u,v) );
  }
}

template<typename Type>
GraphTypes::Cost WeightsTransformer<Type>::get_zero_offset(const Graph<Type> & graph)
{
  typename Graph<Type>::EdgeIterator edge;
  GraphTypes::node_id u,v;
  GraphTypes::Cost cost, min_cost;

  edge = graph.edges_begin();
  min_cost = graph.getCost(*edge);

  edge++;
  while( edge != graph.edges_end() ){
    cost = graph.getCost(*edge);
    if(cost < min_cost){
      min_cost = cost
    }

    edge++;
  }

  return 0-min_cost;
}

template<typename Type>
Graph<Type> WeightsTransformer<Type>::translate_weights(const Graph<Type> & graph, const GraphTypes::Cost & offset)
{
  typename Graph<Type>::EdgeIterator edge;
  GraphTypes::node_id u,v;

  for(edge = graph.edges_begin(); edge != graph.edges_end(); edge++){
    u = edge->source();
    v = edge->target();
    graph.setCost(u,v, graph.getCost(u,v)+offset);
  }

  return graph;
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
  Graph<Type> transformed = graph;

  initial_offset = get_zero_offset(graph);
  _invert_weights_signs(transformed);
  offset = get_zero_offset(transformed);
  return translate_weights(transformed, offset - initial_offset);
}
