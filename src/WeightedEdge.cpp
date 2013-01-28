#include "WeightedEdge.hpp"

WeightedEdge::WeightedEdge(const GraphTypes::node_id & node1,
			   const GraphTypes::node_id & node2,
			   const GraphTypes::Cost & cost):
  Edge(node1, node2),
  _cost(cost)
{}

WeightedEdge::WeightedEdge(const WeightedEdge & source):
  Edge(source),
  _cost(source._cost)
{}

bool WeightedEdge::operator==(const WeightedEdge & ref)const
{
  return Edge::operator==(ref) && _cost == ref._cost;
}

bool WeightedEdge::operator<(const WeightedEdge & ref)const
{
  return (_cost < ref._cost) || ( _cost == ref._cost && Edge::operator<(ref) );
}

bool WeightedEdge::operator<=(const WeightedEdge & ref)const
{
  return operator<(ref) || operator==(ref);
}

bool WeightedEdge::operator>(const WeightedEdge & ref)const
{
  return !operator<=(ref);
}

bool WeightedEdge::operator>=(const WeightedEdge & ref)const
{
  return !operator<(ref);
}

bool WeightedEdge::operator!=(const WeightedEdge & ref)const
{
  return !operator==(ref);
}

const GraphTypes::Cost & WeightedEdge::cost()const
{
  return _cost;
}
