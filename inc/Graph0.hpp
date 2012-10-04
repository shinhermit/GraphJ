#ifndef GRAPH0
#define GRAPH0

#include <set>
#include <map>
#include "Node.hpp"

class Graph0{
protected:
  std::set<Node::node_id> _nodes; /* id-sorted vector of all Nodes IDs*/

  std::map<Node::node_id, std::set<Node::node_id> > _topology; /*!< list d'adjacence*/

  std::set<Node::node_id>::iterator _it; /*!< accesses nodes*/

public:
  Graph0();
  Graph0(const Graph0 & source);
  ~Graph0();

  Graph0 & operator=(const Graph0 & source);

  // Prédicats
  bool is_empty();
  bool has_node(Node::node_id id);
  bool has_edge(Node::node_id id1, Node::node_id id2);

  //Constructeurs
  void add_node(Node::node_id id);
  void remove_node(Node::node_id id);
  void add_edge(Node::node_id id1, Node::node_id id2);
  void remove_edge(Node::node_id id1, Node::node_id id2);

  //observateurs
  unsigned long size()const;
  std::set<Node::node_id> successors(Node::node_id node);
  Node::node_id first_node();
  Node::node_id next_node();
  Node::node_id previous_node();
  Node::node_id last_node();
};

#endif
