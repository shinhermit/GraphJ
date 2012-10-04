#ifndef ABSTRACTGRAPH
#define ABSTRACTGRAPH

#include <set>
#include "Node.hpp"

class AbstractGraph{
public:
  // Prédicats
  virtual bool is_empty()=0;
  virtual bool has_node(Node::node_id id)=0;
  virtual bool has_edge(Node::node_id id1, Node::node_id id2)=0;

  //Constructeurs
  virtual void add_node(Node::node_id id)=0;
  virtual void remove_node(Node::node_id id)=0;
  virtual void add_edge(Node::node_id id1, Node::node_id id2)=0;
  virtual void remove_edge(Node::node_id id1, Node::node_id id2)=0;

  //observateurs
  virtual unsigned long size()const=0;
  virtual std::set<Node::node_id> successors(Node::node_id node)=0;
  virtual Node::node_id first_node()=0;
  virtual Node::node_id next_node()=0;
  virtual Node::node_id previous_node()=0;
  virtual Node::node_id last_node()=0;
  virtual unsigned long internally(Node::node_id node)=0;
  virtual unsigned long externally(Node::node_id node)=0;
};

#endif
