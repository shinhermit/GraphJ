#include <cstdlib>
#include <vector>
#include <iostream>

#include "Exporter.hpp"
#include "MpmNetworkBuilder.hpp"

int main()
{
  Graph<PlanningActivity> activities(GraphTypes::DIRECTED, GraphTypes::UNWEIGHTED, GraphTypes::CONTAINER);

  typedef Exporter<MpmTask> Export;

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

  MpmNetworkBuilder mpmBuilder(activities);
  MpmNetwork mpm(GraphTypes::UNWEIGHTED, GraphTypes::CONTAINER);

  mpmBuilder.buildInto(mpm);

  Export::ToGraphviz(mpm, "flowGraph.graph");
  Exporter<PlanningActivity>::ToGraphviz(activities, "activityGraph.graph");

  system("dot -Tpng activityGraph.graph -o activityGraph.png");
  system("dot -Tpng flowGraph.graph -o flowGraph.png");

}
