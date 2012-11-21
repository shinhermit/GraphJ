 #ifndef ABSTRACTGRAPH
#define ABSTRACTGRAPH

#include <set>
#include <fstream>
#include "Node.hpp"
#include "Edge.hpp"
#include "GraphTypes.hpp"

class AbstractGraph{
public:
  // Prédicats
  virtual bool is_empty()=0;
  virtual bool has_node(Node::node_id id)=0;
  virtual bool has_edge(Node::node_id id1, Node::node_id id2)=0;
  virtual bool is_directed()=0;
  virtual bool is_weighted()=0;
  virtual bool is_container()=0;
  virtual bool at_nodes_end()=0;

  //Constructeurs
  virtual void add_node(Node::node_id id)=0;
  virtual void remove_node(Node::node_id id)=0;
  virtual void add_edge(Node::node_id id1, Node::node_id id2)=0;
  virtual void remove_edge(Node::node_id id1, Node::node_id id2)=0;

  //observateurs
  virtual unsigned long nodes_size()const=0;
  virtual unsigned long edges_size()const=0;
  virtual GraphTypes::NodeType nodeType()const=0;
  virtual GraphTypes::EdgeType edgeType()const=0;
  virtual GraphTypes::EdgeState edgeState()const=0;

  virtual std::set<Node::node_id> successors(Node::node_id node)=0;
  virtual std::set<Node::node_id> predecessors(Node::node_id node)=0;
  virtual std::set<Node::node_id> adjacents(Node::node_id node)=0;

  virtual Node::node_id first_node()=0;
  virtual Node::node_id next_node()=0;
  virtual Node::node_id previous_node()=0;
  virtual Node::node_id last_node()=0;

  virtual unsigned long in_degree(Node::node_id node)=0;
  virtual unsigned long out_degree(Node::node_id node)=0;
  virtual unsigned long degree(Node::node_id node)=0;
};

#endif
