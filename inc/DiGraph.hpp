#ifndef DIGRAPH
#define DIGRAPH

#include <map>
#include <stdexcept>
#include "AbstractGraph.hpp"

class DiGraph : public AbstractGraph{
protected:
  std::set<Node::node_id> _nodes; /*!< id-sorted vector of all Nodes IDs*/

  std::map<Node::node_id, std::set<Node::node_id> > _topology; /*!< list d'adjacence*/

  std::set<Node::node_id>::iterator _it; /*!< accesses nodes*/

public:
  DiGraph();
  DiGraph(const DiGraph & source);
  ~DiGraph();

  DiGraph & operator=(const DiGraph & source);

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
  std::set<Node::node_id> successors(Node::node_id node) throw(std::invalid_argument);
  std::set<Node::node_id> predecessors(Node::node_id node) throw(std::invalid_argument);
  std::set<Node::node_id> adjacents(Node::node_id node) throw(std::invalid_argument);
  Node::node_id first_node() throw(std::out_of_range);
  Node::node_id next_node() throw(std::out_of_range);
  Node::node_id previous_node() throw(std::out_of_range);
  Node::node_id last_node() throw(std::out_of_range);
  unsigned long internally(Node::node_id node) throw(std::invalid_argument);
  unsigned long externally(Node::node_id node) throw(std::invalid_argument);
  unsigned long degree(Node::node_id node) throw(std::invalid_argument);
};

#endif
