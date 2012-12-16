template<typename Type>
Graph<Type> GraphConverter<Type>::toDirected(Graph<Type> & graph)
{
  Graph<Type> convertion(GraphTypes::DIRECTED, graph.edgeState(), graph.nodeType());
  typename Graph<Type>::NodeIterator node;
  std::set<GraphTypes::node_id> adjacents;
  std::set<GraphTypes::node_id>::iterator target;

  if( !graph.is_directed() ){
    node = graph.nodes_begin();
    while( node != graph.nodes_end() ){
      adjacents = graph.adjacents(*node);

      for(target = adjacents.begin(); target != adjacents.end(); target++){

	if( graph.is_weighted() && !graph.is_container() ){
	  convertion.add_edge(*node, *target, graph.getCost(*node,*target));
	}
	else if( graph.is_weighted() && graph.is_container() ){

	  convertion.add_edge(*node, graph.get_node_content(*node), *target, graph.get_node_content(*target), graph.getCost(*node,*target));
	}
	else if( !graph.is_weighted() && graph.is_container() ){
	  
	  convertion.add_edge(*node, graph.get_node_content(*node), *target, graph.get_node_content(*target));
	}
	else{
	  
	  convertion.add_edge(*node, *target);
	}
      }

      node++;
    }
  }
  else{
    convertion = graph;
  }

  return convertion;
}

template<typename Type>
Graph<Type> GraphConverter<Type>::toUndirected(Graph<Type> & graph)
{
  Graph<Type> convertion(GraphTypes::UNDIRECTED, graph.edgeState(), graph.nodeType());
  typename Graph<Type>::NodeIterator node;
  typename Graph<Type>::EdgeIterator edge;
  GraphTypes::node_id sourceNode, targetNode;

  //nodes
  for(node = graph.nodes_begin(); node != graph.nodes_end(); node++){

    if( graph.is_container() ){

      convertion.add_node( *node, graph.get_node_content(*node) );
    }
    else{

      convertion.add_node( *node);
    }
  }

  //edges
  for(edge = graph.edges_begin(); edge != graph.edges_end(); edge++){

    sourceNode = edge->source();
    targetNode = edge->target();

    if( graph.is_weighted() ){

      convertion.add_edge( sourceNode, targetNode, graph.getCost(sourceNode, targetNode) );
    }
    else{

      convertion.add_edge(sourceNode, targetNode);
    }
  }

  return convertion;
}
