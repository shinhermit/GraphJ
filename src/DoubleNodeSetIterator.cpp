#include "DoubleNodeSetIterator.hpp"

using namespace GraphIterator;

DoubleNodeSetIterator::DoubleNodeSetIterator(){}

DoubleNodeSetIterator::DoubleNodeSetIterator(const std::set<GraphTypes::node_id>::const_iterator & underlying):
  _type(GraphTypes::Iterator::SIMPLE),
  _current_predecessor(underlying)
{}

DoubleNodeSetIterator::DoubleNodeSetIterator(const std::set<GraphTypes::node_id>::const_iterator & predecessors_begin,
					     const std::set<GraphTypes::node_id>::const_iterator & predecessors_end,
					     const std::set<GraphTypes::node_id>::const_iterator & successors_begin,
					     const std::set<GraphTypes::node_id>::const_iterator & successors_end,
					     const std::set<GraphTypes::node_id>::const_iterator & current_predecessor,
					     const std::set<GraphTypes::node_id>::const_iterator & current_successor
					     ):
  _type(GraphTypes::Iterator::DOUBLE),
  _predecessors_begin(predecessors_begin),
  _predecessors_end(predecessors_end),
  _successors_begin(successors_begin),
  _successors_end(successors_end),
  _current_predecessor(current_predecessor),
  _current_successor(current_successor)
{}

DoubleNodeSetIterator::DoubleNodeSetIterator(const std::set<GraphTypes::node_id>::const_iterator & predecessors_begin,
					     const std::set<GraphTypes::node_id>::const_iterator & predecessors_end,
					     const std::set<GraphTypes::node_id>::const_iterator & successors_begin,
					     const std::set<GraphTypes::node_id>::const_iterator & successors_end
					     ):
  _type(GraphTypes::Iterator::DOUBLE),
  _predecessors_begin(predecessors_begin),
  _predecessors_end(predecessors_end),
  _successors_begin(successors_begin),
  _successors_end(successors_end),
  _current_predecessor(predecessors_begin),
  _current_successor(successors_begin)
{}

DoubleNodeSetIterator::DoubleNodeSetIterator(const DoubleNodeSetIterator & source):_type(source._type), _current_predecessor(source._current_predecessor)
{
  if(source._type == GraphTypes::Iterator::DOUBLE)
    {
      _predecessors_begin = source._predecessors_begin;
      _predecessors_end = source._predecessors_end;

      _successors_begin = source._successors_begin;
      _successors_end = source._successors_end;

      _current_successor = source._current_successor;
    }
}

DoubleNodeSetIterator & DoubleNodeSetIterator::operator=(const DoubleNodeSetIterator & source)
{
  _type = source._type;
  _current_predecessor = source._current_predecessor;

  if(source._type == GraphTypes::Iterator::DOUBLE)
    {
      _predecessors_begin = source._predecessors_begin;
      _predecessors_end = source._predecessors_end;

      _successors_begin = source._successors_begin;
      _successors_end = source._successors_end;

      _current_successor = source._current_successor;
    }

  return *this;
}

GraphTypes::Iterator::Type DoubleNodeSetIterator::type()const
{
  return _type;
}

const GraphTypes::node_id & DoubleNodeSetIterator::operator*()const
{

  if(_type == GraphTypes::Iterator::SIMPLE)
    {
      return *_current_predecessor;
    }

  else
    {

      if(_current_predecessor != _predecessors_end){
	return *_current_predecessor;
      }

      else
	{
	  return *_current_successor;
	}

    }
}

const GraphTypes::node_id * DoubleNodeSetIterator::operator->()const
{
  return & ( operator*() );
}

DoubleNodeSetIterator & DoubleNodeSetIterator::operator++()
{

  if(_type == GraphTypes::Iterator::SIMPLE)
    {
      ++_current_predecessor;
    }

  else
    {

      if(_current_predecessor != _predecessors_end)
	{
	  ++_current_predecessor;

	}

      else if(_current_successor != _successors_end)
	{
	  ++ _current_successor;
	}

    }

  return *this;
}

DoubleNodeSetIterator & DoubleNodeSetIterator::operator--()
{

  if(_type == GraphTypes::Iterator::SIMPLE)
    {
      --_current_predecessor;
    }

  else
    {

      if(_current_successor != _successors_begin)
	{
	  -- _current_successor;
	}

      else if(_current_predecessor != _predecessors_begin)
	{
	  -- _current_predecessor;
	}

    }

  return *this;
}

DoubleNodeSetIterator DoubleNodeSetIterator::operator++(int)
{
  DoubleNodeSetIterator pre = *this;

  operator++();

  return pre;
}

DoubleNodeSetIterator DoubleNodeSetIterator::operator--(int)
{
  DoubleNodeSetIterator pre = *this;

  operator--();

  return pre;
}

bool DoubleNodeSetIterator::operator==(const DoubleNodeSetIterator & ref)const
{
  bool eq;

  if(_type == GraphTypes::Iterator::SIMPLE){
    eq = (_current_predecessor == ref._current_predecessor);
  }

  else
    {
      eq = ((_predecessors_begin == ref._predecessors_begin) &
	    (_predecessors_end == ref._predecessors_end) &
	    (_successors_begin == ref._successors_begin) &
	    (_successors_end == ref._successors_end) &
	    (_current_predecessor == ref._current_predecessor) &
	    (_current_successor == ref._current_successor)
	    );
    }

  return eq;
}

bool DoubleNodeSetIterator::operator!=(const DoubleNodeSetIterator & ref)const
{
  return !operator==(ref);
}
