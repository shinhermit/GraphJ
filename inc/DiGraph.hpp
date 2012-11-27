#ifndef DIGRAPH
#define DIGRAPH

#include <map>
#include <stdexcept>
#include "AbstractGraph.hpp"

class DiGraph : public AbstractGraph{
public:
  class NodeIterator
  {
  private:
    std::set<Node::node_id>::iterator _it;
  public:
    NodeIterator();
    NodeIterator(std::set<Node::node_id>::iterator it);
    NodeIterator(const NodeIterator & source);
    NodeIterator & operator=(const NodeIterator & source);
    Node::node_id operator*()const;
    void operator++(int);
    void operator--(int);
    bool operator==(const NodeIterator & ref);
    friend bool operator!=(const NodeIterator & it1, const NodeIterator & it2);
  };

protected:
  std::set<Node::node_id> _nodes; /*!< id-sorted vector of all Nodes IDs*/

  unsigned long _nb_of_edges; /*!< makes it easier to get graph metrics*/

  std::map<Node::node_id, std::set<Node::node_id> > _topology; /*!< adjacence list, reduces algorithms complexity*/

public:
  DiGraph();
  DiGraph(const DiGraph & source);
  ~DiGraph();

  DiGraph & operator=(const DiGraph & source);

  // Prédicats
  bool is_empty();
  bool has_node(Node::node_id id);
  bool has_edge(Node::node_id id1, Node::node_id id2);
  bool is_directed();
  bool is_weighted();
  bool is_container();

  //Constructeurs
  void add_node(Node::node_id id);
  void remove_node(Node::node_id id);
  void add_edge(Node::node_id id1, Node::node_id id2);
  void remove_edge(Node::node_id id1, Node::node_id id2);

  //observateurs
  unsigned long nodes_size()const;
  unsigned long edges_size()const;
  GraphTypes::NodeType nodeType()const;
  GraphTypes::EdgeType edgeType()const;
  GraphTypes::EdgeState edgeState()const;

  std::set<Node::node_id> successors(Node::node_id node) throw(std::invalid_argument);
  std::set<Node::node_id> predecessors(Node::node_id node) throw(std::invalid_argument);
  std::set<Node::node_id> adjacents(Node::node_id node) throw(std::invalid_argument);

  NodeIterator nodes_begin();
  NodeIterator nodes_end();

  unsigned long in_degree(Node::node_id node) throw(std::invalid_argument);
  unsigned long out_degree(Node::node_id node) throw(std::invalid_argument);
  unsigned long degree(Node::node_id node) throw(std::invalid_argument);
};

#endif
