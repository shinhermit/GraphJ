#include "TopologyIterator.hpp"

using namespace GraphIterator;

TopologyIterator::TopologyIterator(){}

TopologyIterator::TopologyIterator(const TopologyIterator & source):_topology_begin(source._topology_begin), _topology_end(source._topology_end), _current_pair(source._current_pair), _second(source._second), _edge(source._edge){}

TopologyIterator::TopologyIterator(const std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> >::const_iterator & topology_begin,
				   const std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> >::const_iterator & topology_end,
				   const std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> >::const_iterator & current_pair,
				   const std::set<GraphTypes::node_id>::const_iterator & second):
  _topology_begin(topology_begin),
  _topology_end(topology_end),
  _current_pair(current_pair),
  _second(second)
{

  if(_current_pair != _topology_end)
    {
      _edge = Edge(_current_pair->first, *_second);
    }

}

TopologyIterator::TopologyIterator(const std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> >::const_iterator & topology_begin,
				   const std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> >::const_iterator & topology_end,
				   const std::map<GraphTypes::node_id, std::set<GraphTypes::node_id> >::const_iterator & current_pair):
  _topology_begin(topology_begin),
  _topology_end(topology_end),
  _current_pair(current_pair)
{

  if(_current_pair != _topology_end)
    {
      _second = _current_pair->second.begin();
      _edge = Edge(_current_pair->first, *_second);
    }

}

TopologyIterator & TopologyIterator::operator=(const TopologyIterator & source)
{
  _topology_begin = source._topology_begin;
  _topology_end = source._topology_end;
  _current_pair = source._current_pair;
  _second = source._second;
  _edge = source._edge;

  return *this;
}

const Edge & TopologyIterator::operator*()const
{
  return _edge;
}

const Edge * TopologyIterator::operator->()const
{

  return & ( operator*() ) ;
}

TopologyIterator & TopologyIterator::operator++()
{
  if(_topology_begin != _topology_end){

    if(_current_pair != _topology_end){
      if( _second != _current_pair->second.end() ){
	++ _second;

	if( _second == _current_pair->second.end() ){
	  ++ _current_pair;

	  if(_current_pair != _topology_end){
	    _second = _current_pair->second.begin();
	  }

	}
      }
      else{
	++ _current_pair;

	if(_current_pair != _topology_end){
	  _second = _current_pair->second.begin();
	}

      }
    }

    //mise à jour du _edge
    if(_current_pair != _topology_end){
      _edge = Edge(_current_pair->first, *_second);
    }

  }

  return *this;
}

TopologyIterator & TopologyIterator::operator--()
{
  if(_topology_begin != _topology_end){

    if(_current_pair == _topology_begin){

      if( _second != _current_pair->second.begin() ){
	-- _second;
      }
    }
    else if(_current_pair == _topology_end){
      -- _current_pair;

      _second = _current_pair->second.end();
      -- _second;
    }
    else{

      if( _second != _current_pair->second.begin() ){
	-- _second;
      }
      else{
	--_current_pair;

	_second = _current_pair->second.end();
	--_second;
      }

    }

    //mise à jour du _edge
    _edge = Edge(_current_pair->first, *_second);

  }

  return *this;
}

TopologyIterator TopologyIterator::operator++(int)
{
  TopologyIterator pre= *this;
  ++(*this);
  return pre;
}

TopologyIterator TopologyIterator::operator--(int)
{
  TopologyIterator pre= *this;
  --(*this);
  return pre;
}

bool TopologyIterator::operator==(const TopologyIterator & ref)const
{
  if(_current_pair != _topology_end){
    return (_current_pair == ref._current_pair && _second == ref._second);
  }
  else{
    return (_current_pair == ref._current_pair);
  }
}

bool TopologyIterator::operator!=(const TopologyIterator & ref)const
{
  return !operator==(ref);
}

