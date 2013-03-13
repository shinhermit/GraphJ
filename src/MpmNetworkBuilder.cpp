#include "MpmNetworkBuilder.hpp"

MpmNetworkBuilder::MpmNetworkBuilder(Graph<PlanningActivity> & planning)
  :_planning(planning)
{}

void MpmNetworkBuilder::buildInto(MpmNetwork & network)
{
  GraphTypes::node_id id;

  //source and sink always at 0 and 1
  network.setSource(0);
  network.setSink(1);

  Graph<MpmTask> & flowGraph = network;
  flowGraph.add_node( network.source(), MpmTask("Début") );
  flowGraph.add_node( network.sink(), MpmTask("Fin") );

  //treat nodes
  for(Graph<PlanningActivity>::NodeIterator planned = _planning.nodes_begin();
      planned != _planning.nodes_end();
      ++planned)
    {
      PlanningActivity & activity = _planning.get_node_content(*planned);
      const std::string & label = activity.label();
      const GraphTypes::Planning::Duration & duration = activity.duration();

      //shift all IDs to make sure to not override source and sink
      id = 2 + *planned;

      flowGraph.add_node(id, MpmTask(label, duration));

      //if no preceeding task, connect to source node
      if( _planning.predecessors_begin(*planned) == _planning.predecessors_end(*planned) )
	{
	  flowGraph.add_edge(0, id);
	}

      //if no following task, connect to sink node
      if( _planning.successors_begin(*planned) == _planning.successors_end(*planned) )
	{
	  flowGraph.add_edge(id, 1);
	}
    }

  //treat edges
  for(Graph<PlanningActivity>::EdgeIterator planned = _planning.edges_begin();
      planned != _planning.edges_end();
      ++planned)
    {
      flowGraph.add_edge( 2+planned->source(), 2+planned->target() );
    }
}

MpmNetwork MpmNetworkBuilder::build()
{
  MpmNetwork network(GraphTypes::UNWEIGHTED, GraphTypes::CONTAINER);

  buildInto(network);

  return network;
}
