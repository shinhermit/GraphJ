#ifndef _TopologyIterator
#define _TopologyIterator

#include <iterator>
#include <map>
#include <set>
#include "GraphTypes.hpp"
#include "Edge.hpp"

namespace GraphIterator
{
  typedef std::iterator<std::bidirectional_iterator_tag, Edge> EdgeIterator;

  class TopologyIterator : public EdgeIterator
  {
  private:
    std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> >::const_iterator _topology_begin;
    std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> >::const_iterator _topology_end;
    std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> >::const_iterator _current_pair;
    std::set<GraphTypes::node_id>::const_iterator _second;
    Edge _edge;

  public:
    TopologyIterator();

    TopologyIterator(const TopologyIterator & source);

    TopologyIterator(const std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> >::const_iterator & topology_begin,
		     const std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> >::const_iterator & topology_end,
		     const std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> >::const_iterator & current_pair,
		     const std::set<GraphTypes::node_id>::const_iterator & second
		     );

    TopologyIterator(const std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> >::const_iterator & topology_begin,
		     const std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> >::const_iterator & topology_end,
		     const std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> >::const_iterator & current_pair
		     );

    TopologyIterator & operator=(const TopologyIterator & source);

    const Edge & operator*()const;
    const Edge * operator->()const;
    TopologyIterator & operator++();
    TopologyIterator operator++(int);
    TopologyIterator & operator--();
    TopologyIterator operator--(int);

    bool operator==(const TopologyIterator & ref)const;
    bool operator!=(const TopologyIterator & ref)const;
  };
};

#endif
