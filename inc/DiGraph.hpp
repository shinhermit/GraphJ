#ifndef DIGRAPH
#define DIGRAPH

#include <map>
#include <stdexcept>
#include "AbstractGraph.hpp"
#include "Edge.hpp"

class DiGraph : public AbstractGraph{
public:
  class NodeIterator
  {
  private:
    std::set<GraphTypes::node_id>::iterator _it;
  public:
    NodeIterator();
    NodeIterator(std::set<GraphTypes::node_id>::iterator it);
    NodeIterator(const NodeIterator & source);
    NodeIterator & operator=(const NodeIterator & source);
    GraphTypes::node_id operator*()const;
    void operator++(int);
    void operator--(int);
    bool operator==(const NodeIterator & ref);
    bool operator!=(const NodeIterator & ref);
  };

  class EdgeIterator
  {
  private:
    std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> >::iterator _current, _end;
    std::set<GraphTypes::node_id>::iterator _targetNode;
  public:
    EdgeIterator();
    EdgeIterator(const std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> >::iterator & begin, const std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> >::iterator & end);
    EdgeIterator(const EdgeIterator & source);
    EdgeIterator & operator=(const EdgeIterator & source);
    Edge operator*()const;
    void operator++(int);
    void operator--(int);
    bool operator==(const EdgeIterator & ref);
    bool operator!=(const EdgeIterator & ref);
  };

protected:
  std::set<GraphTypes::node_id> _nodes; /*!< id-sorted vector of all Nodes IDs*/

  unsigned long _nb_of_edges; /*!< makes it easier to get graph metrics*/

  std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> > _topology; /*!< adjacence list, reduces algorithms complexity*/

public:
  DiGraph();
  DiGraph(const DiGraph & source);
  ~DiGraph();

  DiGraph & operator=(const DiGraph & source);

  // Prédicats
  bool is_empty();
  bool has_node(GraphTypes::node_id id);
  bool has_edge(GraphTypes::node_id id1, GraphTypes::node_id id2);
  bool is_directed();
  bool is_weighted();
  bool is_container();

  //Constructeurs
  void add_node(GraphTypes::node_id id);
  void remove_node(GraphTypes::node_id id);
  void add_edge(GraphTypes::node_id id1, GraphTypes::node_id id2);
  void remove_edge(GraphTypes::node_id id1, GraphTypes::node_id id2);

  //observateurs
  unsigned long nodes_size()const;
  unsigned long edges_size()const;
  GraphTypes::NodeType nodeType()const;
  GraphTypes::EdgeType edgeType()const;
  GraphTypes::EdgeState edgeState()const;

  std::set<GraphTypes::node_id> successors(GraphTypes::node_id node) throw(std::invalid_argument);
  std::set<GraphTypes::node_id> predecessors(GraphTypes::node_id node) throw(std::invalid_argument);
  std::set<GraphTypes::node_id> adjacents(GraphTypes::node_id node) throw(std::invalid_argument);

  NodeIterator nodes_begin();
  NodeIterator nodes_end();
  EdgeIterator edges_begin();
  EdgeIterator edges_end();

  unsigned long in_degree(GraphTypes::node_id node) throw(std::invalid_argument);
  unsigned long out_degree(GraphTypes::node_id node) throw(std::invalid_argument);
  unsigned long degree(GraphTypes::node_id node) throw(std::invalid_argument);
};

#endif
