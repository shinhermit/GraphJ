#include <cstdlib>

#include "PlanningActivity.hpp"
#include "MpmNetwork.hpp"
#include "MpmNetworkBuilder.hpp"
#include "MpmDatesComputer.hpp"
#include "Exporter.hpp"

int main()
{
  MpmNetwork network("Début", "Fin");
  GraphvizAttributesHolder config;

  typedef Exporter<MpmTask> Export;

  {
    Graph<PlanningActivity> activities(GraphTypes::DIRECTED, GraphTypes::UNWEIGHTED, GraphTypes::CONTAINER);

    //ajout des tâches
    activities.add_node( 1, PlanningActivity("A", 50) );
    activities.add_node( 2, PlanningActivity("B", 45) );
    activities.add_node( 3, PlanningActivity("C", 15) );
    activities.add_node( 4, PlanningActivity("D", 10) );
    activities.add_node( 5, PlanningActivity("E", 30) );
    activities.add_node( 6, PlanningActivity("F", 20) );
    activities.add_node( 7, PlanningActivity("G", 8) );
    activities.add_node( 8, PlanningActivity("H", 8) );
    activities.add_node( 9, PlanningActivity("I", 5) );
    activities.add_node( 10, PlanningActivity("J", 6) );
    activities.add_node( 11, PlanningActivity("K", 6) );
    activities.add_node( 12, PlanningActivity("L", 2) );
    activities.add_node( 13, PlanningActivity("M", 6) );
    activities.add_node( 14, PlanningActivity("N", 1) );
  
    //informations de précédence
    activities.add_edge(1,3);
    activities.add_edge(1,4);
    activities.add_edge(1,6);
    activities.add_edge(1,7);
    activities.add_edge(1,8);
    activities.add_edge(1,9);
    activities.add_edge(1,10);
    activities.add_edge(1,11);
    activities.add_edge(1,12);
    activities.add_edge(1,13);
    activities.add_edge(1,14);

    activities.add_edge(2,3);
    activities.add_edge(2,4);
    activities.add_edge(2,5);
    activities.add_edge(2,10);
    activities.add_edge(2,11);
    activities.add_edge(2,12);
    activities.add_edge(2,13);
    activities.add_edge(2,14);

    activities.add_edge(4,13);
    activities.add_edge(4,12);
    activities.add_edge(4,11);
    activities.add_edge(4,14);

    activities.add_edge(5,10);
    activities.add_edge(5,14);

    activities.add_edge(6,8);
    activities.add_edge(6,9);
    activities.add_edge(6,10);
    activities.add_edge(6,14);

    activities.add_edge(7,10);
    activities.add_edge(7,14);

    activities.add_edge(8,10);
    activities.add_edge(8,14);

    activities.add_edge(9,10);
    activities.add_edge(9,14);

    activities.add_edge(11,12);
    activities.add_edge(11,14);

    Exporter<PlanningActivity>::ToGraphviz(activities, "bin/activityGraph.graph");

    MpmNetworkBuilder mpmBuilder(activities);

    mpmBuilder.buildInto(network);
  }
  
  MpmDatesComputer dates(network);
  dates.compute();

  config.setGraphLabel("MPM chart TP1");
  Export::GraphvizMpmPrepare(network, config);
  Export::GraphvizPathHighlight( config, dates.criticalPath() );
  Export::ToGraphviz(network, config, "bin/MPM_chart.graph");

  system("dot -Tpng bin/MPM_chart.graph -o bin/MPM_chart.png");

  return 0;
}
