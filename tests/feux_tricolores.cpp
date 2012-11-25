#include "Graph.hpp"
#include "Coloring.hpp"

int main(){
  Graph<> franchissements(GraphTypes::DIRECTED, GraphTypes::UNWEIGHTED, GrapheTypes::NOCONTENT);
  Graph<Edge> incompatibles(GraphTypes::UNDIRECTED, GraphTypes::UNWEIGHTED, GrapheTypes::NOCONTENT);
  Coloring<> color;
  std::map<Node::node_id, std::string> labels1, labels2;

  //graphe de la relations "il existe un franchissement"
  // Nous faisons coïncider l'ordre lexico-graphique et l'ordre numérique
  // Nous verrons pourquoi plus loin

  labels1[1] = "A";
  labels1[2] = "B";
  labels1[3] = "C";
  labels1[4] = "D";
  labels1[5] = "E";

  franchissements.add_edge(1,3);
  franchissements.add_edge(1,5);
  franchissements.add_edge(2,1);
  franchissements.add_edge(2,4);
  franchissements.add_edge(2,5);
  franchissements.add_edge(3,1);
  franchissements.add_edge(3,4);
  franchissements.add_edge(4,1);
  franchissements.add_edge(4,3);
  franchissements.add_edge(5,3);
  franchissements.add_edge(5,4);

  //graphe de la relations "les franchissements sont compatibles"
  labels2[1] = "AC";
  labels2[2] = "AE";
  labels2[3] = "BA";
  labels2[4] = "BD";
  labels2[5] = "BE";
  labels2[6] = "CA";
  labels2[7] = "CD";
  labels2[8] = "DA";
  labels2[9] = "DC";
  labels2[10] = "EC";
  labels2[11] = "ED";

  incompatibles.add_node( Edge(1,3) );
  incompatibles.add_node( Edge(1,5) );
  incompatibles.add_node( Edge(2,1) );
  incompatibles.add_node( Edge(2,4) );
  incompatibles.add_node( Edge(2,5) );
  incompatibles.add_node( Edge(3,1) );
  incompatibles.add_node( Edge(3,4) );
  incompatibles.add_node( Edge(4,1) );
  incompatibles.add_node( Edge(4,3) );
  incompatibles.add_node( Edge(5,3) );
  incompatibles.add_node( Edge(5,4) );

  //construction des arêtes du graphe d'incompatibilité de franchissement
  /*
    La stratégie est la suivante:
    -deux arcs (=franchissement) sont incompatibles s'ils ont un sommet en commun
    -pour un arc u->v, id(u) < id(v)
       -Tous les arcs x->y, id(x) < id(y) tels que
            id(u) <= id(x) <= id(v)  ET id(y) >= id(v)
	sont incompatibles avec u->v.
	Dans cette formule, id(u) et id(v) sont interchangeable,
	il en va de même de id(x) et id(y)
   */

  return 0;
}
