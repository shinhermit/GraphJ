#include "MpmDatesComputer.hpp"

MpmDatesComputer::MpmDatesComputer(MpmNetwork & network,
		   const GraphTypes::Planning::Duration & ProjectStart)
  :_network(network)
{
  MpmTask & projectBegin = _network.flowGraph().get_node_content( _network.source() );

  projectBegin.setEarlyStart(ProjectStart);
  projectBegin.setLateStart(ProjectStart);
}

void MpmDatesComputer::_early_start_computation()
{
  _lookup.bellman( _network, MpmEdgeWeighter(), _network.source(), GraphTypes::Algorithms::GREEDY, GraphTypes::Algorithms::MAXIMIZE );

  const std::map<GraphTypes::node_id, GraphTypes::Cost> & distances = _lookup.distances();
  Graph<MpmTask> & flowGraph = _network.flowGraph();
  const GraphTypes::Planning::Duration & projectStart = flowGraph.get_node_content(_network.source()).earlyStart();

  for(std::map<GraphTypes::node_id, GraphTypes::Cost>::const_iterator dst_it = distances.begin();
      dst_it != distances.end();
      ++dst_it)
    {
      const GraphTypes::node_id & node = dst_it->first;
      const GraphTypes::Cost & distance = dst_it->second;
      GraphTypes::Planning::Duration earlyStart = projectStart + distance;

      MpmTask & task = flowGraph.get_node_content(node);
      
      task.setEarlyStart(earlyStart);

      if( node == _network.sink() )
	{
	  task.setLateStart(earlyStart);
	}
    }
}

void MpmDatesComputer::_late_start_computation()
{
  _lookup.dual_bellman( _network, MpmEdgeWeighter(GraphTypes::Planning::REVERSED), _network.sink(), GraphTypes::Algorithms::GREEDY, GraphTypes::Algorithms::MAXIMIZE );

  const std::map<GraphTypes::node_id, GraphTypes::Cost> & distances = _lookup.distances();
  Graph<MpmTask> & flowGraph = _network.flowGraph();
  const GraphTypes::Planning::Duration & projectEnd = flowGraph.get_node_content(_network.sink()).lateStart();

  for(std::map<GraphTypes::node_id, GraphTypes::Cost>::const_iterator dst_it = distances.begin();
      dst_it != distances.end();
      ++dst_it)
    {
      const GraphTypes::node_id & node = dst_it->first;
      const GraphTypes::Cost & distance = dst_it->second;
      GraphTypes::Planning::Duration lateStart = projectEnd - distance;

      MpmTask & task = flowGraph.get_node_content(node);
      
      task.setLateStart(lateStart);
    }
}

const GraphTypes::Planning::Duration & MpmDatesComputer::_min_following_early_start(const GraphTypes::node_id & node)
{
  Graph<MpmTask> & flowGraph = _network.flowGraph();

  GraphTypes::Planning::Duration & min = const_cast<GraphTypes::Planning::Duration&>( flowGraph.get_node_content( * flowGraph.successors_begin(node) ).earlyStart() );

  for(Graph<MpmTask>::NodeIterator succ = flowGraph.successors_begin(node);
      succ != flowGraph.successors_end(node);
      ++succ)
    {
      const GraphTypes::Planning::Duration & earlyStart = flowGraph.get_node_content(*succ).earlyStart();

      if(earlyStart < min)
	min = earlyStart;
    }

  return min;
}

void MpmDatesComputer::_slacks_computation()
{
  Graph<MpmTask> & flowGraph = _network.flowGraph();

  for(Graph<MpmTask>::NodeIterator node = flowGraph.nodes_begin();
      node != flowGraph.nodes_end();
      ++node)
    {
      MpmTask & task = flowGraph.get_node_content(*node);
      const GraphTypes::Planning::Duration & minFollowing = _min_following_early_start(*node);

      task.setTotalSlack( task.lateStart()-task.earlyStart() );
      task.setFreeSlack( minFollowing - task.earlyStart() - task.duration() );
      task.setSureSlack( minFollowing - task.lateStart() - task.duration() );
    }
}

void MpmDatesComputer::compute()
{
  _early_start_computation();
  _late_start_computation();
  _slacks_computation();
}
