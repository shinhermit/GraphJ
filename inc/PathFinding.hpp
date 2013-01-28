#ifndef _PathFinding
#define _PathFinding

#include <list>
#include <deque>
#include "Graph.hpp"
#include "Traverse.hpp"

template <typename Type=GraphTypes::Default>
class PathFinding
{
private:
  GraphTypes::Algorithms::ComputingValidity _validity;

  GraphTypes::Algorithms::ComputingValidity _check_computing_validity(const Graph<Type> & graph,
								      const std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source);

  //DIJKSTRA
  void _init(const Graph<Type> & graph,
	     Graph<> & paths,
	     const GraphTypes::node_id & sourceNode,
	     std::list<GraphTypes::node_id> & candidates,
	     std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source,
	     std::map<GraphTypes::node_id, GraphTypes::node_id> & best_predecessor);

  const GraphTypes::node_id & _closest(const std::list<GraphTypes::node_id> & candidates,
				       const std::map<GraphTypes::node_id,GraphTypes::Cost> & distance_from_source);

  void _update_tables(const Graph<Type> & graph,
		      const Graph<> & paths,
		      const GraphTypes::node_id & closest,
		      std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source,
		      std::map<GraphTypes::node_id, GraphTypes::node_id> & best_predecessor);

  //BELLMAN GREEDY
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
		      std::map<GraphTypes::node_id, GraphTypes::node_id> & best_predecessor,
		      const GraphTypes::Algorithms::OptimizationType & optimizationType=GraphTypes::Algorithms::MINIMIZE);

  void _insert_waiting_nodes(const Graph<Type> & graph,
			     Graph<> & paths,
			     std::deque<GraphTypes::node_id> & waiting_for_insertion,
			     const std::map<GraphTypes::node_id, GraphTypes::node_id> & best_predecessor);

  void _remove_nodes(std::list<GraphTypes::node_id> & candidates,
		     const std::deque<GraphTypes::node_id> & waiting_for_insertion);

  Graph<> _greedy_bellman(const Graph<Type> & graph,
			  const GraphTypes::node_id & sourceNode,
			  const GraphTypes::Algorithms::OptimizationType & optimizationType=GraphTypes::Algorithms::MINIMIZE);

  //BELLMAN DYNAMIC
  void _init(const Graph<Type> & graph,
	     Graph<> & paths,
	     const GraphTypes::node_id & sourceNode,
	     std::map<GraphTypes::node_id,GraphTypes::Cost> & distance_from_source,
	     const GraphTypes::Algorithms::OptimizationType & optimizationType=GraphTypes::Algorithms::MINIMIZE);

  void _update_tables(const Graph<Type> & graph,
		      std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source,
		      std::map<GraphTypes::node_id, GraphTypes::node_id> & best_predecessor,
		      const GraphTypes::Algorithms::OptimizationType & optimizationType=GraphTypes::Algorithms::MINIMIZE);

  void _build_paths_graph(const Graph<Type> & graph,
			  Graph<> & paths,
			  const GraphTypes::node_id & sourceNode,
			  const std::map<GraphTypes::node_id, GraphTypes::Cost> & distance_from_source,
			  const std::map<GraphTypes::node_id, GraphTypes::node_id> & best_predecessor);

  Graph<> _dynamic_bellman(const Graph<Type> & graph,
			   const GraphTypes::node_id & sourceNode,
			   const GraphTypes::Algorithms::OptimizationType & optimizationType=GraphTypes::Algorithms::MINIMIZE);

public:
  PathFinding();

  Graph<> dijkstra(const Graph<Type> & graph,
		   const GraphTypes::node_id & sourceNode
		   ) throw(GraphException::InvalidOperation);

  Graph<> bellman(const Graph<Type> & graph,
		  const GraphTypes::node_id & sourceNode,
		  const GraphTypes::Algorithms::AlgorithmicClass & algoClass=GraphTypes::Algorithms::DYNAMIC,
		  const GraphTypes::Algorithms::OptimizationType & optimizationType=GraphTypes::Algorithms::MINIMIZE
		  ) throw(GraphException::InvalidOperation);

  std::list<GraphTypes::Path> paths_to(const Graph<> & allPaths,
				       const GraphTypes::node_id & target
				       ) throw(GraphException::InvalidOperation);

  std::list<GraphTypes::Path> between(const Graph<Type> & graph,
				      const GraphTypes::node_id & source,
				      const GraphTypes::node_id & target,
				      const GraphTypes::Algorithms::SearchAlgorithm & algo=GraphTypes::Algorithms::DIJKSTRA
				      )throw(GraphException::InvalidOperation);

  const GraphTypes::Algorithms::ComputingValidity & validity()const;
};

#include "PathFinding.cpp"

#endif
