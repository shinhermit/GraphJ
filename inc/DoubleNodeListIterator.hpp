#ifndef _DoubleNodeListIterator
#define _DoubleNodeListIterator

#include <set>
#include "GraphTypes.hpp"

namespace GraphIterator
{
  class DoubleNodeListIterator : std::iterator<std::bidirectional_iterator_tag, GraphTypes::node_id>
  {
  private:
    std::set<GraphTypes::node_id>::const_iterator _predecessors_begin;
    std::set<GraphTypes::node_id>::const_iterator _predecessors_end;

    std::set<GraphTypes::node_id>::const_iterator _successors_begin;
    std::set<GraphTypes::node_id>::const_iterator _successors_end;

    std::set<GraphTypes::node_id>::const_iterator _current_predecessor;
    std::set<GraphTypes::node_id>::const_iterator _current_successor;

  public:
    DoubleNodeListIterator();
    DoubleNodeListIterator(const std::set<GraphTypes::node_id>::const_iterator & predecessors_begin,
			   const std::set<GraphTypes::node_id>::const_iterator & predecessors_end,
			   const std::set<GraphTypes::node_id>::const_iterator & successors_begin,
			   const std::set<GraphTypes::node_id>::const_iterator & successors_end,
			   const std::set<GraphTypes::node_id>::const_iterator & current_predecessors,
			   const std::set<GraphTypes::node_id>::const_iterator & current_successors
			   );

    DoubleNodeListIterator(const std::set<GraphTypes::node_id>::const_iterator & predecessors_begin,
			   const std::set<GraphTypes::node_id>::const_iterator & predecessors_end,
			   const std::set<GraphTypes::node_id>::const_iterator & successors_begin,
			   const std::set<GraphTypes::node_id>::const_iterator & successors_end
			   );

    DoubleNodeListIterator(const DoubleNodeListIterator & source);

    DoubleNodeListIterator & operator=(const DoubleNodeListIterator & source);

    const GraphTypes::node_id & operator*()const;

    const GraphTypes::node_id * operator->()const;

    DoubleNodeListIterator & operator++();

    DoubleNodeListIterator & operator--();

    DoubleNodeListIterator  operator++(int);

    DoubleNodeListIterator operator--(int);

    bool operator==(const DoubleNodeListIterator & ref)const;

    bool operator!=(const DoubleNodeListIterator & ref)const;
  };
};

#endif
