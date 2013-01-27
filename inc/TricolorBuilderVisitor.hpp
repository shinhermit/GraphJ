#ifndef _TricolorBuilderVisitor
#define _TricolorBuilderVisitor

#include "Visitor.hpp"
#include "Graph.hpp"
#include <sstream>
#include <string>


  //construction des arêtes du graphe d'incompatibilité de franchissement
  /*
    La stratégie est la suivante:
    -deux arcs (=franchissement) qui ont un sommet commun sont incompatibles
    -Étant donnés deux points, B et D par exemple, tout franchissement X->Y tel que
      X et Y sont de part et d'autre du segment joignant B et D
    est incompatible avec le franchissement BD
      . pour déterminer une telle situation:
        # on numérote les points de 1 à 5, à partir de B (en tournant de la sens horaire)
	   :: Compte tenu de l'attribution de nos id, cela revient à calculer un delta; D = id(B) - 1
	   :: Suite à cette renumérotation:
	       -pour un arc u->v, id(u) < id(v)
	       -Tous les arcs x->y, id(x) < id(y) tels que
	       id(u) < id(x) < id(v)  ET id(y) > id(v)
	       sont incompatibles avec u->v.
	       Dans cette formule, id(u) et id(v) sont interchangeable,
	       il en va de même de id(x) et id(y)
   */

namespace GraphFunctor
{

  class TricolorBuilderVisitor : public Visitor
  {
  private:
    Graph<Edge> & _graph;

    long _nb_roads;

    long _renumber(const long & asFirst, const long & oldNumber)const;
    bool _adjacent(const Edge & edge1, const Edge & edge2)const;
    bool _intersect(const Edge & edge1, const Edge & edge2)const;

  public:
    TricolorBuilderVisitor(Graph<Edge> & graph, const long & nb_roads);

    ~TricolorBuilderVisitor();

    void operator()(const GraphTypes::node_id & node);
  };

};

#endif
