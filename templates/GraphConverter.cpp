template<typename Type>
void _copyNodes(const Graph<Type> & graph, Graph<Type> & convertion)
{
  typename Graph<Type>::NodeIterator node;

  for(node = graph.nodes_begin(); node != graph.nodes_end(); ++node){

    if( graph.is_container() ){
      convertion.add_node( *node, graph.get_node_content(*node) );
    }

    else{
      convertion.add_node(*node);
    }

  }
}

template<typename Type>
Graph<Type> GraphConverter<Type>::toDirected(const Graph<Type> & graph)
{
  Graph<Type> convertion(GraphTypes::DIRECTED, graph.edgeState(), graph.nodeType());
  typename Graph<Type>::NodeIterator node;
  typename Graph<Type>::EdgeIterator edge;
  GraphTypes::node_id origin, target;

  if( !graph.is_directed() ){

    //nodes
    _copyNodes(graph, convertion);

    //edges
    for(edge = graph.edges_begin(); edge != graph.edges_end(); ++edge){
      origin = edge->source();
      target = edge->target();

      if( graph.is_weighted() ){
	convertion.add_edge(origin,target, graph.getCost(origin,target) );
	convertion.add_edge(target,origin, graph.getCost(target,origin) );
      }

      else{
	convertion.add_edge(origin,target);
	convertion.add_edge(target,origin);
      }
    }
  }

  else{
    convertion = graph;
  }

  return convertion;
}

template<typename Type>
Graph<Type> GraphConverter<Type>::toUndirected(const Graph<Type> & graph)
{
  Graph<Type> convertion(GraphTypes::UNDIRECTED, graph.edgeState(), graph.nodeType());
  typename Graph<Type>::NodeIterator node;
  typename Graph<Type>::EdgeIterator edge;
  GraphTypes::node_id origin, target;

  if( graph.is_directed() ){

    //nodes
    _copyNodes(graph, convertion);

    //edges
    for(edge = graph.edges_begin(); edge != graph.edges_end(); ++edge){

      origin = edge->source();
      target = edge->target();

      if( graph.is_weighted() ){
	convertion.add_edge( origin, target, graph.getCost(origin, target) );
      }

      else{
	convertion.add_edge(origin, target);
      }

    }

  }

  else{
    convertion = graph;
  }

  return convertion;
}
