#include "Edge.hpp"

Edge::Edge(){}

Edge::Edge(const GraphTypes::node_id & origin,
	   const GraphTypes::node_id & target):
  _origin(origin),
  _target(target)
{}

Edge::Edge(const Edge & source):
  _origin(source._origin),
  _target(source._target)
{}

bool Edge::operator==(const Edge & ref)const
{
  return _origin == ref._origin && _target == ref._target;
}

bool Edge::operator<(const Edge & ref)const
{
  return (_origin < ref._origin) || (_origin == ref._origin && _target < ref._target);
}

bool Edge::operator<=(const Edge & ref)const
{
  return operator<(ref) || operator==(ref);
}

bool Edge::operator>(const Edge & ref)const
{
  return !operator<=(ref);
}

bool Edge::operator>=(const Edge & ref)const
{
  return !operator<(ref);  
}

bool Edge::operator!=(const Edge & ref)const
{
  return _origin != ref._origin || _target != ref._target;
}

const GraphTypes::node_id & Edge::source()const
{
  return _origin;
}

const GraphTypes::node_id & Edge::target()const
{
  return _target;
}
