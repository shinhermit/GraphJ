#ifndef _BaseGraph
#define _BaseGraph

#include <map>
#include <set>
#include "Node.hpp"
#include "Edge.hpp"
#include "GraphTypes.hpp"
#include "GraphIterator.hpp"
#include "GraphException.hpp"

class BaseGraph{
public:
  typedef std::set<GraphTypes::node_id>::const_iterator NodeIterator;

  typedef GraphIterator::TopologyIterator EdgeIterator;

private:
  unsigned int _clean_topology(std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> > & topology,
			     std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> > & relative_reversed,
			     const GraphTypes::node_id & id);

  NodeIterator _adjacent_begin(const std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> > & topology_map, const GraphTypes::node_id & node)const;
  NodeIterator _adjacent_end(const std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> > & topology_map, const GraphTypes::node_id & node)const;

protected:
  std::set<GraphTypes::node_id> _nodes; /*!< id-sorted vector of all Nodes IDs*/

  std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> > _topology; /*!< Relations (edges): successors lists*/

  std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> > _reversed_topology; /*!< Reversed relations: predecessors lists*/

  unsigned int _nb_of_edges; /*!< Makes it easier to get graph metrics*/

public:
  BaseGraph();
  BaseGraph(const BaseGraph & source);
  virtual ~BaseGraph();

  BaseGraph & operator=(const BaseGraph & source);

  // Prédicats
  bool is_empty()const;
  bool has_node(const GraphTypes::node_id & node)const;
  bool has_edge(const GraphTypes::node_id & origin, const GraphTypes::node_id & target)const;
  bool is_directed()const;
  bool is_weighted()const;
  bool is_container()const;

  //Constructeurs
  void add_node(const GraphTypes::node_id & node);
  void remove_node(const GraphTypes::node_id & node);
  void add_edge(const GraphTypes::node_id & origin, const GraphTypes::node_id & target);
  void remove_edge(const GraphTypes::node_id & origin, const GraphTypes::node_id & target);

  //observateurs
  unsigned long nodes_size()const;
  unsigned long edges_size()const;
  GraphTypes::NodeType nodeType()const;
  GraphTypes::EdgeType edgeType()const;
  GraphTypes::EdgeState edgeState()const;

  NodeIterator successors_begin(const GraphTypes::node_id & node)const throw(GraphException::InvalidNodeIDException);
  NodeIterator successors_end(const GraphTypes::node_id & node)const throw(GraphException::InvalidNodeIDException);
  NodeIterator predecessors_begin(const GraphTypes::node_id & node)const throw(GraphException::InvalidNodeIDException);
  NodeIterator predecessors_end(const GraphTypes::node_id & node)const throw(GraphException::InvalidNodeIDException);

  NodeIterator nodes_begin()const;
  NodeIterator nodes_end()const;
  EdgeIterator edges_begin()const;
  EdgeIterator edges_end()const;

  unsigned long in_degree(const GraphTypes::node_id & node)const throw(GraphException::InvalidNodeIDException);
  unsigned long out_degree(const GraphTypes::node_id & node)const throw(GraphException::InvalidNodeIDException);
  unsigned long degree(const GraphTypes::node_id & node)const throw(GraphException::InvalidNodeIDException);
};

#endif
