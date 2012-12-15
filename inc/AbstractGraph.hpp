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
  virtual bool has_node(GraphTypes::node_id id)=0;
  virtual bool has_edge(GraphTypes::node_id id1, GraphTypes::node_id id2)=0;
  virtual bool is_directed()=0;
  virtual bool is_weighted()=0;
  virtual bool is_container()=0;

  //Constructeurs
  virtual void add_node(GraphTypes::node_id id)=0;
  virtual void remove_node(GraphTypes::node_id id)=0;
  virtual void add_edge(GraphTypes::node_id id1, GraphTypes::node_id id2)=0;
  virtual void remove_edge(GraphTypes::node_id id1, GraphTypes::node_id id2)=0;

  //observateurs
  virtual unsigned long nodes_size()const=0;
  virtual unsigned long edges_size()const=0;
  virtual GraphTypes::NodeType nodeType()const=0;
  virtual GraphTypes::EdgeType edgeType()const=0;
  virtual GraphTypes::EdgeState edgeState()const=0;

  virtual std::set<GraphTypes::node_id> successors(GraphTypes::node_id node)=0;
  virtual std::set<GraphTypes::node_id> predecessors(GraphTypes::node_id node)=0;
  virtual std::set<GraphTypes::node_id> adjacents(GraphTypes::node_id node)=0;

  virtual unsigned long in_degree(GraphTypes::node_id node)=0;
  virtual unsigned long out_degree(GraphTypes::node_id node)=0;
  virtual unsigned long degree(GraphTypes::node_id node)=0;
};

#endif
