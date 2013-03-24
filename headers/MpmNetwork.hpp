#ifndef _MpmNetwork
#define _MpmNetwork

#include "CanonicalNetwork.hpp"
#include "MpmTask.hpp"

class MpmNetwork : public CanonicalNetwork<MpmTask>
{
public:
  MpmNetwork(const GraphTypes::node_id & sourceNode,
	     const GraphTypes::node_id & sinkNode,
	     const std::string & sourceNodeLabel="Begin",
	     const std::string & sinkNodeLabel="End");

  MpmNetwork(const std::string & sourceNodeLabel="Begin",
	     const std::string & sinkNodeLabel="End");
};

#endif
