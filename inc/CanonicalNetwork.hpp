#ifndef _CanonicalNetwork
#define _CanonicalNetwork

#include "Graph.hpp"

/**
   A network (ie digraph) with only one source and one sink
*/
template<typename Type=GraphTypes::Default>
class CanonicalNetwork
{
private:
  Graph<Type> _flowGraph;
  GraphTypes::node_id _sourceNode;
  GraphTypes::node_id _sinkNode;

public:
  CanonicalNetwork(const GraphTypes::node_id & sourceNode,
		   const GraphTypes::node_id & sinkNode,
		   const GraphTypes::EdgeState & state=GraphTypes::WEIGHTED,
		   const GraphTypes::NodeType & nodeType=GraphTypes::NOCONTENT);

  CanonicalNetwork(const GraphTypes::EdgeState & state=GraphTypes::WEIGHTED,
		   const GraphTypes::NodeType & nodeType=GraphTypes::NOCONTENT);

  CanonicalNetwork(const CanonicalNetwork & source);

  CanonicalNetwork & operator=(const CanonicalNetwork & source);

  void setSource(const GraphTypes::node_id & source);
  void setSink(const GraphTypes::node_id & sink);

  const GraphTypes::node_id & source()const;
  const GraphTypes::node_id & sink()const;

  Graph<Type> & flowGraph();
  operator Graph<Type>&();
};

#include "CanonicalNetwork.cpp"

#endif
