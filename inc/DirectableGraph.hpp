#ifndef _DirectableGraph
#define _DirectableGraph

#include "BaseGraph.hpp"
#include "GraphTypes.hpp"

class DirectableGraph : public BaseGraph{
protected:
  GraphTypes::EdgeType _edgeType;

public:
  DirectableGraph(const GraphTypes::EdgeType & edgeType=GraphTypes::UNDIRECTED);
  DirectableGraph(const DirectableGraph & source);

  // Adaptation des prédicats
  bool is_directed()const;
  bool has_edge(const GraphTypes::node_id & origin, const GraphTypes::node_id & target)const;

  // Adaptation des constructeurs
  void add_edge(const GraphTypes::node_id & origin, const GraphTypes::node_id & target);
  void remove_edge(const GraphTypes::node_id & origin, const GraphTypes::node_id & target);

  // Adaptation des observateurs
  GraphTypes::EdgeType edgeType()const;

  unsigned long in_degree(const GraphTypes::node_id & node)const throw(GraphException::InvalidNodeIDException);
  unsigned long out_degree(const GraphTypes::node_id & node)const throw(GraphException::InvalidNodeIDException);
};

#endif
