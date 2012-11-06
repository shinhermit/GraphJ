#ifndef GRAPH
#define GRAPH

#include "PonderableGraph.hpp"

template <typename Type>
class Graph : public PonderableGraph{
protected:
  std::map<Node::node_id, Type> _contents;

public:
  Graph(EdgeType edgeType=UNDIRECTED, EdgeState state=WEIGHTED);
  Graph(const Graph & source);

  Graph & operator=(const Graph & source);

  // Adaptation des constructeurs
  void add_node(Node::node_id id, Type content);
  void remove_node(Node::node_id node_id);
  void add_edge(Node::node_id src_node, Type content1, Node::node_id target_node, Type content2, PonderableGraph::Cost cost=1.F);
  void add_edge(Node::node_id existing_src, Node::node_id existing_target, PonderableGraph::Cost cost=1.F) throw(std::invalid_argument);
  void remove_edge(Node::node_id src_node, Node::node_id target_node);

  // Nouvelles opérations
  void set_node_content(Node::node_id id, Type content) throw(std::invalid_argument);
  Type get_node_content(Node::node_id id) throw(std::logic_error, std::invalid_argument);
};

#include "Graph.cpp"

#endif
