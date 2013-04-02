#ifndef _Traverse
#define _Traverse

#include <deque>
#include "Graph.hpp"
#include "Visitor.hpp"

template<typename Type=GraphTypes::Default>
class Traverse
{
public:
  static void Nodes(Graph<Type> & graph,
		    GraphFunctor::Visitor & visit);

  static void Breadth_once(Graph<Type> & graph,
			   const GraphTypes::node_id & node,
			   GraphFunctor::Visitor & visit);

  static void Breadth(Graph<Type> & graph,
		      GraphFunctor::Visitor & visit);

  static void Depth_once(Graph<Type> & graph,
			 const GraphTypes::node_id & node,
			 GraphFunctor::Visitor & visit);

  static void Depth(Graph<Type> & graph,
		    GraphFunctor::Visitor & visit);



  Traverse(Graph<Type> & graph);

  void breadth_once(Graph<Type> & graph,
		    const GraphTypes::node_id & node,
		    GraphFunctor::Visitor & visit);

  void breadth(Graph<Type> & graph,
	       GraphFunctor::Visitor & visit);

  void depth_once(Graph<Type> & graph,
		  const GraphTypes::node_id & node,
		  GraphFunctor::Visitor & visit);

  void depth(Graph<Type> & graph,
	     GraphFunctor::Visitor & visit);

  const Graph<> & traversingGraph()const;
  
private:
  Graph<Type> & _graph;
  Graph<> _marker;

  static void Traverse<Type>::_Add_edge(Graph<> & marker,
					Graph<Type> & graph,
					const GraphTypes::node_id & source,
					const GraphTypes::node_id & target);

  static void _Breadth_once(Graph<Type> & graph,
			    const GraphTypes::node_id & node,
			    GraphFunctor::Visitor & visit,
			    Graph<> & marker);

  static void _Depth_once(Graph<Type> & graph,
			  const GraphTypes::node_id & node,
			  GraphFunctor::Visitor & visit,
			  Graph<> & marker);

};

#include "Traverse.cpp"

#endif
