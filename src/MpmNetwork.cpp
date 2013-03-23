#include "MpmNetwork.hpp"

MpmNetwork::MpmNetwork(const GraphTypes::node_id & sourceNode,
		       const GraphTypes::node_id & sinkNode,
		       const std::string & sourceNodeLabel,
		       const std::string & sinkNodeLabel)
  :CanonicalNetwork<MpmTask>(sourceNode, MpmTask(sourceNodeLabel), sinkNode, MpmTask(sinkNodeLabel), GraphTypes::UNWEIGHTED, GraphTypes::CONTAINER)
{}

MpmNetwork::MpmNetwork(const std::string & sourceNodeLabel,
		       const std::string & sinkNodeLabel)
  :CanonicalNetwork<MpmTask>(0, MpmTask(sourceNodeLabel), 1, MpmTask(sinkNodeLabel), GraphTypes::UNWEIGHTED, GraphTypes::CONTAINER)
{}
