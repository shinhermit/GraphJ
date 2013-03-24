#include <cstdlib>
#include <vector>
#include <iostream>

#include "Exporter.hpp"
#include "MpmNetworkBuilder.hpp"
#include "MpmDatesComputer.hpp"

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

  Exporter<PlanningActivity>::ToGraphviz(activities, "activityGraph.graph");

  MpmNetworkBuilder mpmBuilder(activities);
  MpmNetwork mpm;
  GraphvizAttributesHolder config;

  mpmBuilder.buildInto(mpm);

  Export::GraphvizMpmPrepare(mpm, config);
  Export::ToGraphviz(mpm, config, "flowGraph.graph");

  MpmDatesComputer dates(mpm);
  dates.compute();

  config.setGraphLabel("MPM chart");
  Export::GraphvizMpmPrepare(mpm, config);
  Export::GraphvizPathHighlight( config, dates.criticalPath() );
  Export::ToGraphviz(mpm, config, "MPM_chart.graph");

  system("dot -Tpng activityGraph.graph -o activityGraph.png");
  system("dot -Tpng flowGraph.graph -o flowGraph.png");
  system("dot -Tpng MPM_chart.graph -o MPM_chart.png");

}
