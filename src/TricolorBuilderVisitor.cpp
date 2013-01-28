#include "TricolorBuilderVisitor.hpp"

using namespace GraphFunctor;

TricolorBuilderVisitor::TricolorBuilderVisitor(Graph<Edge> & graph,
					       const long & nb_roads):
  _graph(graph),
  _nb_roads(nb_roads)
{}

TricolorBuilderVisitor::~TricolorBuilderVisitor(){}

long TricolorBuilderVisitor::_renumber(const long & asFirst,
				       const long & oldNumber)const
{
  long renum, delta;

  delta = asFirst - 1;

  renum = oldNumber - delta;
  if(renum <= 0)
    renum += _nb_roads;

  return renum;
}

bool TricolorBuilderVisitor::_adjacent(const Edge & edge1,
				       const Edge & edge2)const
{
  bool adjacent;

  adjacent = false;

  if(
     //     edge1.source() == edge2.source() ||
     edge1.source() == edge2.target() ||
     edge1.target() == edge2.source() ||
     edge1.target() == edge2.target()
     )
    {
      adjacent = true;
    }

  return adjacent;
}

bool TricolorBuilderVisitor::_intersect(const Edge & edge1, const Edge & edge2)const
{
  long asFirst, reSource1, reTarget1, reSource2, reTarget2, oldNumber;
  bool intersect;

  //renumérotation des sommets (du graphe des franchissements)
  asFirst = (long)edge1.source();
  reSource1 = _renumber(asFirst, asFirst);

  oldNumber = (long)edge1.target();
  reTarget1 = _renumber(asFirst, oldNumber);

  oldNumber = (long)edge2.source();
  reSource2 = _renumber(asFirst, oldNumber);

  oldNumber = (long)edge2.target();
  reTarget2 = _renumber(asFirst, oldNumber);

  intersect = false;

  if(
     ( (reSource1 < reSource2 && reSource2 < reTarget1) && reTarget1 < reTarget2) ||
     ( (reSource1 < reTarget2 && reTarget2 < reTarget1) && reTarget1 < reSource2)
     )
    {
      intersect = true;
    }

  return intersect;
}

void TricolorBuilderVisitor::operator()(const GraphTypes::node_id & node)
{
  Graph<Edge>::NodeIterator node2;
  Edge current, candidate;

  current = _graph.get_node_content(node);

  node2 = _graph.nodes_begin();
  while( node2 != _graph.nodes_end() )
    {

      if(*node2 != node)
	{
	  candidate = _graph.get_node_content(*node2);

	  //arcs incompatibles si un sommet en commun ou se croisent
	  if( _adjacent(current, candidate) ||
	      _intersect(current, candidate)
	      )
	    {
	      _graph.add_edge(node, *node2);
	    }
	}

      ++node2;
    }
}
