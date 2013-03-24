#include <cstdlib>
#include <vector>
#include <iostream>

#include "Exporter.hpp"
#include "PlanningActivity.hpp"
#include "Graph.hpp"

int main()
{
  Graph<PlanningActivity> activities(GraphTypes::DIRECTED, GraphTypes::UNWEIGHTED, GraphTypes::CONTAINER);
  Graph<PlanningActivity>::NodeIterator node;
  Graph<PlanningActivity>::NodeIterator pred;

  typedef Exporter<PlanningActivity> Export;

  //exemple du cours (exemple 2, sur mes notes)

  //ajout des tâches
  activities.add_node( 1, PlanningActivity("A", 2) );
  activities.add_node( 2, PlanningActivity("B", 4) );
  activities.add_node( 3, PlanningActivity("C", 4) );
  activities.add_node( 4, PlanningActivity("D", 5) );
  activities.add_node( 5, PlanningActivity("E", 6) );

  //informations de précédence
  activities.add_edge(1,3);
  activities.add_edge(1,4);
  activities.add_edge(2,4);
  activities.add_edge(3,5);
  activities.add_edge(4,5);

  //affichage de la table de précédence
  std::cout << "|\t ID \t|\t Label \t|\t Durée \t|\t Précédences \t|" << std::endl;

  for(Graph<PlanningActivity>::NodeIterator node = activities.nodes_begin();
      node != activities.nodes_end();
      ++node)
    {
      PlanningActivity & activity = activities.get_node_content(*node);

      std::cout << "|\t "<<*node<<" \t|\t "<<activity.label()<<" \t|\t "<<activity.duration()<<" \t|\t ";

      for(Graph<PlanningActivity>::NodeIterator pred = activities.predecessors_begin(*node);
	  pred != activities.predecessors_end(*node);
	  ++pred)
	{
	  PlanningActivity & preceeder = activities.get_node_content(*pred);
	  std::cout << preceeder.label() << ", "bin/;
	}

      std::cout << " \t|" << std::endl;
      
    }

  Export::ToGraphviz(activities, "bin/precedences.graph");

  system("dot -Tpng bin/precedences.graph -o bin/precedences.png");
}
