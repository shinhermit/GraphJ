#ifndef _XPathFinding
#define _XPathFinding

#include <list>
#include <deque>
#include "Graph.hpp"


template <typename Type=GraphTypes::Default>
class XPathFinding
{
private:
  GraphTypes::Algorithms::ComputingValidity _validity;

  GraphTypes::Algorithms::ComputingValidity _check_computing_validity(const Graph<Type> & graph,
								      const std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source);

  //Xdijkstra
  void _init(const Graph<Type> & graph,
	     Graph<> & paths,
	     const GraphTypes::node_id & sourceNode,
	     std::list<GraphTypes::node_id> & candidates,
	     std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source,
	     std::map<GraphTypes::node_id, std::list<GraphTypes::node_id> > & best_predecessors);

  std::list<GraphTypes::node_id> _allClosest(const std::list<GraphTypes::node_id> & candidates,
					     const std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source);

  void _add_edges(const Graph<Type> & graph,
		  Graph<> & paths,
		  const std::map<GraphTypes::node_id,std::list<GraphTypes::node_id> > & best_predecessors,
		  const std::list<GraphTypes::node_id> allClosest);

  void _remove_nodes(std::list<GraphTypes::node_id> & candidates,
		     const std::list<GraphTypes::node_id> allClosest);

  void _update_tables(const Graph<Type> & graph,
		      const Graph<> & paths,
		      const std::list<GraphTypes::node_id> allClosest,
		      std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source,
		      std::map<GraphTypes::node_id, std::list<GraphTypes::node_id> > & best_predecessors);

  //Xbellman: greedy
  void _init(const Graph<Type> & graph,
	     Graph<> & paths,
	     const GraphTypes::node_id & sourceNode,
	     std::list<GraphTypes::node_id> & candidates,
	     std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source,
	     const GraphTypes::Algorithms::OptimizationType & optimizationType=GraphTypes::Algorithms::MINIMIZE);

  std::deque<GraphTypes::node_id> _coupe(const Graph<Type> & graph,
					 const Graph<> & paths,
					 const std::list<GraphTypes::node_id> & candidates);

  void _update_tables(const Graph<Type> & graph,
		      const Graph<> & paths,
		      const std::deque<GraphTypes::node_id> & waiting_for_insertion,
		      std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source,
		      std::map<GraphTypes::node_id, std::list<GraphTypes::node_id> > & best_predecessors,
		      const GraphTypes::Algorithms::OptimizationType & optimizationType=GraphTypes::Algorithms::MINIMIZE);

  void _insert_waiting_nodes(const Graph<Type> & graph,
			     Graph<> & paths,
			     std::deque<GraphTypes::node_id> & waiting_for_insertion,
			     const std::map<GraphTypes::node_id, std::list<GraphTypes::node_id> > & best_predecessors);

  void _remove_nodes(std::list<GraphTypes::node_id> & candidates,
		     const std::deque<GraphTypes::node_id> & waiting_for_insertion);

  Graph<> _greedy_bellman(const Graph<Type> & graph,
			  const GraphTypes::node_id & sourceNode,
			  const GraphTypes::Algorithms::OptimizationType & optimizationType=GraphTypes::Algorithms::MINIMIZE);

  //Xbellman: dynamic
  void _init(const Graph<Type> & graph,
	     Graph<> & paths,
	     const GraphTypes::node_id & sourceNode,
	     std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source,
	     const GraphTypes::Algorithms::OptimizationType & optimizationType=GraphTypes::Algorithms::MINIMIZE);

  void _update_tables(const Graph<Type> & graph,
		      std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source,
		      std::map<GraphTypes::node_id, std::list<GraphTypes::node_id> > & best_predecessors,
		      const GraphTypes::Algorithms::OptimizationType & optimizationType=GraphTypes::Algorithms::MINIMIZE);

  void _build_paths_graph(const Graph<Type> & graph,
			  Graph<> & paths,
			  const GraphTypes::node_id & sourceNode,
			  const std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source,
			  const std::map<GraphTypes::node_id, std::list<GraphTypes::node_id> > & best_predecessors);

  Graph<> _dynamic_bellman(const Graph<Type> & graph,
			   const GraphTypes::node_id & sourceNode,
			   const GraphTypes::Algorithms::OptimizationType & optimizationType=GraphTypes::Algorithms::MINIMIZE);

public:
  XPathFinding();

  Graph<> Xdijkstra(const Graph<Type> & graph,
		    const GraphTypes::node_id & sourceNode
		    ) throw(GraphException::InvalidOperation);

  Graph<> Xbellman(const Graph<Type> & graph,
		   const GraphTypes::node_id & sourceNode,
		   const GraphTypes::Algorithms::AlgorithmicClass & algoClass=GraphTypes::Algorithms::DYNAMIC,
		   const GraphTypes::Algorithms::OptimizationType & optimizationType=GraphTypes::Algorithms::MINIMIZE
		   ) throw(GraphException::InvalidOperation);

  std::list<GraphTypes::Path> paths_to(const Graph<> & allPaths,
				       const GraphTypes::node_id & target
				       ) throw(GraphException::InvalidOperation);

  std::list<GraphTypes::Path> Xbetween(const Graph<Type> & graph,
				       const GraphTypes::node_id & source,
				       const GraphTypes::node_id & target,
				       const GraphTypes::Algorithms::SearchAlgorithm & algo=GraphTypes::Algorithms::DIJKSTRA
				       ) throw(GraphException::InvalidOperation);
};

#include "XPathFinding.cpp"

#endif
