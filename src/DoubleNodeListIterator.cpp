#include "DoubleNodeListIterator.hpp"

using namespace GraphIterator;

DoubleNodeListIterator::DoubleNodeListIterator(){}

DoubleNodeListIterator::DoubleNodeListIterator(const std::set<GraphTypes::node_id>::const_iterator & predecessors_begin,
		       const std::set<GraphTypes::node_id>::const_iterator & predecessors_end,
		       const std::set<GraphTypes::node_id>::const_iterator & successors_begin,
		       const std::set<GraphTypes::node_id>::const_iterator & successors_end,
		       const std::set<GraphTypes::node_id>::const_iterator & current_predecessor,
		       const std::set<GraphTypes::node_id>::const_iterator & current_successor
		       ):_predecessors_begin(predecessors_begin), _predecessors_end(predecessors_end), _successors_begin(successors_begin), _successors_end(successors_end), _current_predecessor(current_predecessor), _current_successor(current_successor){}

DoubleNodeListIterator::DoubleNodeListIterator(const std::set<GraphTypes::node_id>::const_iterator & predecessors_begin,
		       const std::set<GraphTypes::node_id>::const_iterator & predecessors_end,
		       const std::set<GraphTypes::node_id>::const_iterator & successors_begin,
		       const std::set<GraphTypes::node_id>::const_iterator & successors_end
		       ):_predecessors_begin(predecessors_begin), _predecessors_end(predecessors_end), _successors_begin(successors_begin), _successors_end(successors_end), _current_predecessor(predecessors_begin), _current_successor(successors_begin){}

DoubleNodeListIterator::DoubleNodeListIterator(const DoubleNodeListIterator & source):_predecessors_begin(source._predecessors_begin), _predecessors_end(source._predecessors_end), _successors_begin(source._successors_begin), _successors_end(source._successors_end), _current_predecessor(source._current_predecessor), _current_successor(source._current_successor){}

DoubleNodeListIterator & DoubleNodeListIterator::operator=(const DoubleNodeListIterator & source)
{
   _predecessors_begin = source._predecessors_begin;
   _predecessors_end = source._predecessors_end;

   _successors_begin = source._successors_begin;
   _successors_end = source._successors_end;

   _current_predecessor = source._current_predecessor;
   _current_successor = source._current_successor;

   return *this;
}

const GraphTypes::node_id & DoubleNodeListIterator::operator*()const
{
  if(_current_predecessor != _predecessors_end){
    return *_current_predecessor;
  }
  else{
    return *_current_successor;
  }
}

const GraphTypes::node_id * DoubleNodeListIterator::operator->()const
{
  return & ( operator*() );
}

DoubleNodeListIterator & DoubleNodeListIterator::operator++()
{
  if(_current_predecessor != _predecessors_end){
    ++_current_predecessor;

    // if(_current_predecessor == _predecessors_end){
    //   if(_current_successor != _successors_end){
    // 	++ _current_successor;
    //   }
    // }

  }
  else if(_current_successor != _successors_end){
    ++ _current_successor;
  }

  return *this;
}

DoubleNodeListIterator & DoubleNodeListIterator::operator--()
{
  if(_current_successor != _successors_begin){
    -- _current_successor;
  }
  else if(_current_predecessor != _predecessors_begin){
    -- _current_predecessor;
  }

  return *this;
}

DoubleNodeListIterator DoubleNodeListIterator::operator++(int)
{
  DoubleNodeListIterator pre = *this;

  operator++();

  return pre;
}

DoubleNodeListIterator DoubleNodeListIterator::operator--(int)
{
  DoubleNodeListIterator pre = *this;

  operator++();

  return pre;
}

bool DoubleNodeListIterator::operator==(const DoubleNodeListIterator & ref)const
{
  return ((_predecessors_begin == ref._predecessors_begin) &
	  (_predecessors_end == ref._predecessors_end) &
	  (_successors_begin == ref._successors_begin) &
	  (_successors_end == ref._successors_end) &
	  (_current_predecessor == ref._current_predecessor) &
	  (_current_successor == ref._current_successor)
	  );
}

bool DoubleNodeListIterator::operator!=(const DoubleNodeListIterator & ref)const
{
  return !operator==(ref);
}

