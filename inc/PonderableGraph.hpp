#ifndef _PonderableGraph
#define _PonderableGraph

#include "DirectableGraph.hpp"

class PonderableGraph : public DirectableGraph{
protected:
  GraphTypes::EdgeState _edgeState;

  std::map<Edge,GraphTypes::Cost> _weights;

public:
  PonderableGraph(const GraphTypes::EdgeType & edgeType=GraphTypes::UNDIRECTED,
		  const GraphTypes::EdgeState & state=GraphTypes::WEIGHTED);

  PonderableGraph(const PonderableGraph & source);

  PonderableGraph & operator=(const PonderableGraph & source);

  // Adaptation des prédicats
  bool is_weighted()const;

  // Adaptation des constructeurs
  void remove_node(const GraphTypes::node_id & node);

  void add_edge(const GraphTypes::node_id & origin,
		const GraphTypes::node_id & target,
		const GraphTypes::Cost & cost=0.F);

  void remove_edge(const GraphTypes::node_id & origin,
		   const GraphTypes::node_id & target);

  // Adaptation des observateurs
  GraphTypes::EdgeState edgeState()const;

  // Nouvelles opérations
  void setCost(const GraphTypes::node_id & origin,
	       const GraphTypes::node_id & target,
	       const GraphTypes::Cost & cost
	       )throw(GraphException::InvalidEdge, GraphException::InvalidOperation);

  GraphTypes::Cost getCost(const GraphTypes::node_id & origin,
			   const GraphTypes::node_id & target
			   )const throw(GraphException::InvalidEdge, GraphException::InvalidOperation);

  GraphTypes::Cost getCost(const Edge & edge)const
    throw(GraphException::InvalidEdge, GraphException::InvalidOperation);

  GraphTypes::Cost cost()const
    throw(GraphException::InvalidOperation);

};

#endif
