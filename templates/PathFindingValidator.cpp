
using namespace GraphFunctor;

template<typename Type>
bool PathFindingValidator<Type>::operator()(const Graph<Type> & graph,
				      const GraphFunctor::EdgeWeighter<Type> & CostFunctor,
				      const std::map<GraphTypes::node_id, GraphTypes::Cost> & distances)
{
  typename Graph<Type>::EdgeIterator it;
  bool valid;

  valid = true;

  for(it = graph.edges_begin(); it != graph.edges_end(); ++it)
    {

      const GraphTypes::node_id & pred = it->source();
      const GraphTypes::node_id & succ = it->target();

      const GraphTypes::Cost & min_distance = distances.find(succ)->second;
      const GraphTypes::Cost & distance_from_pred = distances.find(pred)->second + CostFunctor(graph, pred, succ);

      if( min_distance > distance_from_pred )
	{
	  valid = false;
	}

    }

  return valid;
}
