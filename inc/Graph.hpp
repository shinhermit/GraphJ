#ifndef _Graph
#define _Graph

#include "PonderableGraph.hpp"

template <typename Type=GraphTypes::Default>
class Graph : public PonderableGraph{
protected:
  GraphTypes::NodeType _nodeType;
  std::map<GraphTypes::node_id, Type> _contents;

public:
  Graph(const GraphTypes::EdgeType & edgeType=GraphTypes::UNDIRECTED, const GraphTypes::EdgeState & state=GraphTypes::WEIGHTED, const GraphTypes::NodeType & nodeType=GraphTypes::NOCONTENT);
  Graph(const Graph & source);

  Graph & operator=(const Graph & source);

  // Adaptation des prédicats
  bool is_container()const;

  // Adaptation des constructeurs
  void add_node(const GraphTypes::node_id & node, const Type & content);
  void add_node(const GraphTypes::node_id & node) throw(GraphException::InvalidOperation);
  void remove_node(const GraphTypes::node_id & node_id);
  void add_edge(const GraphTypes::node_id & src_node, const Type & content1, const GraphTypes::node_id & target_node, const Type & content2, const GraphTypes::Cost & cost=0.F);
  void add_edge(const GraphTypes::node_id & existing_src, const GraphTypes::node_id & existing_target, const GraphTypes::Cost & cost=0.F) throw(GraphException::InvalidOperation);

  // Adaptation des observateurs
  GraphTypes::NodeType nodeType()const;

  // Nouvelles opérations
  void set_node_content(const GraphTypes::node_id & node, const Type & content) throw(GraphException::InvalidOperation, GraphException::InvalidNodeID);
  Type get_node_content(const GraphTypes::node_id & node)const throw(GraphException::InvalidOperation, GraphException::InvalidNodeID);
};

#include "Graph.cpp"

#endif
