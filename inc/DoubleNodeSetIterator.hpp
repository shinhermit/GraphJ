#ifndef _DoubleNodeSetIterator
#define _DoubleNodeSetIterator

#include <iterator>
#include <set>
#include "GraphTypes.hpp"

namespace GraphIterator
{
  typedef std::iterator<std::bidirectional_iterator_tag, GraphTypes::node_id> NodeIterator;

  class DoubleNodeSetIterator : public NodeIterator
  {
  private:
    GraphTypes::Iterator::Type _type;

    std::set<GraphTypes::node_id>::const_iterator _predecessors_begin;
    std::set<GraphTypes::node_id>::const_iterator _predecessors_end;

    std::set<GraphTypes::node_id>::const_iterator _successors_begin;
    std::set<GraphTypes::node_id>::const_iterator _successors_end;

    std::set<GraphTypes::node_id>::const_iterator _current_predecessor;
    std::set<GraphTypes::node_id>::const_iterator _current_successor;

  public:
    DoubleNodeSetIterator();

    DoubleNodeSetIterator(const std::set<GraphTypes::node_id>::const_iterator & underlying);

    DoubleNodeSetIterator(const std::set<GraphTypes::node_id>::const_iterator & predecessors_begin,
			  const std::set<GraphTypes::node_id>::const_iterator & predecessors_end,
			  const std::set<GraphTypes::node_id>::const_iterator & successors_begin,
			  const std::set<GraphTypes::node_id>::const_iterator & successors_end,
			  const std::set<GraphTypes::node_id>::const_iterator & current_predecessors,
			  const std::set<GraphTypes::node_id>::const_iterator & current_successors
			  );

    DoubleNodeSetIterator(const std::set<GraphTypes::node_id>::const_iterator & predecessors_begin,
			  const std::set<GraphTypes::node_id>::const_iterator & predecessors_end,
			  const std::set<GraphTypes::node_id>::const_iterator & successors_begin,
			  const std::set<GraphTypes::node_id>::const_iterator & successors_end
			  );

    DoubleNodeSetIterator(const DoubleNodeSetIterator & source);

    DoubleNodeSetIterator & operator=(const DoubleNodeSetIterator & source);

    GraphTypes::Iterator::Type type()const;

    const GraphTypes::node_id & operator*()const;

    const GraphTypes::node_id * operator->()const;

    DoubleNodeSetIterator & operator++();

    DoubleNodeSetIterator & operator--();

    DoubleNodeSetIterator  operator++(int);

    DoubleNodeSetIterator operator--(int);

    bool operator==(const DoubleNodeSetIterator & ref)const;

    bool operator!=(const DoubleNodeSetIterator & ref)const;
  };
};

#endif
