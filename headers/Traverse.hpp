#ifndef _Traverse
#define _Traverse

#include <deque>
#include "Graph.hpp"
#include "Visitor.hpp"

template<typename Content=GraphTypes::Default>
class Traverse
{
public:
  static void Nodes(Graph<Content> & graph,
		    GraphFunctor::Visitor & visit);

  static void Breadth_once(Graph<Content> & graph,
			   const GraphTypes::node_id & node,
			   GraphFunctor::Visitor & visit);

  static void Breadth(Graph<Content> & graph,
		      GraphFunctor::Visitor & visit);

  static void Depth_once(Graph<Content> & graph,
			 const GraphTypes::node_id & node,
			 GraphFunctor::Visitor & visit);

  static void Depth(Graph<Content> & graph,
		    GraphFunctor::Visitor & visit);



  Traverse(Graph<Content> & graph);

  void breadth_once(const GraphTypes::node_id & node,
		    GraphFunctor::Visitor & visit);

  void breadth(GraphFunctor::Visitor & visit);

  void depth_once(const GraphTypes::node_id & node,
		  GraphFunctor::Visitor & visit);

  void depth(GraphFunctor::Visitor & visit);

  const Graph<> & traversingGraph()const;
  
private:
  Graph<Content> & _graph;
  Graph<> _marker;

  static void _Add_edge(Graph<> & marker,
					   Graph<Content> & graph,
					   const GraphTypes::node_id & source,
					   const GraphTypes::node_id & target);

  static void _Breadth_once(Graph<Content> & graph,
			    const GraphTypes::node_id & node,
			    GraphFunctor::Visitor & visit,
			    Graph<> & marker);

  static void _Depth_once(Graph<Content> & graph,
			  const GraphTypes::node_id & node,
			  GraphFunctor::Visitor & visit,
			  Graph<> & marker);

};

#include "Traverse.cpp"

#endif
