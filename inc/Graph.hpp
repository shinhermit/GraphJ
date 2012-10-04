#ifndef GRAPH
#define GRAPH

#include "Graph0.hpp"
#include "Node.hpp"

template <typename Type>
class Graph : private Graph0{

protected:
  std::map<Node::node_id, Type> _contents;

public:
  Graph();
  Graph(const Graph & source);
  ~Graph();

  Graph & operator=(const Graph & source);

  // Prédicats
  bool is_empty();
  bool has_node(Node::node_id id);
  bool has_edge(Node::node_id src_node, Node::node_id target_node);

  //Constructeurs
  void add_node(Node::node_id id, Type content);
  void remove_node(Node::node_id node_id);
  void add_edge(Node::node_id src_node, Type content1, Node::node_id target_node, Type content2);
  void add_edge(Node::node_id existing_src, Node::node_id existing_target);
  void remove_edge(Node::node_id src_node, Node::node_id target_node);

  //Observateurs
  unsigned long size()const;
  std::set<Node::node_id> successors(Node::node_id node);
  Node::node_id first_node();
  Node::node_id next_node();
  Node::node_id previous_node();
  Node::node_id last_node();
  Type get_node_content(Node::node_id id);
};

#include "Graph.cpp"

#endif
