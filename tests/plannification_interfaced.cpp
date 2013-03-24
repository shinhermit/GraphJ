#include <cstdlib>
#include <iostream>

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
    std::string label(""), preceeding("");
    GraphTypes::Planning::Duration duration;
    std::map<std::string, GraphTypes::node_id> labelToIdMapper;

    //ajout des tâches
    std::cout << "Saisie des tâches: label durée" << std::endl << " Ex: A 10" << std::endl << "Entrer \"fin.\" pour terminer." << std::endl;

    int i = 1;
    while(label != "fin.")
      {
	std::cin >> label;

	if(label != "fin.")
	  {
	    std::cin >> duration;

	    activities.add_node( i, PlanningActivity(label, duration) );
	    labelToIdMapper[label] = i;

	    ++i;
	  }
      }
  
    //informations de précédence
    std::cout << "Saisie des informations de précédence: tâche précedente1 précédente2 \\\\ ..." << std::endl << "Ex: A B C D E \\\\" << std::endl << "Entrer \"fin.\" pour terminer" << std::endl;

    std::cin >> label;
    while(label != "fin.")
      {

	std::cin >> preceeding;
	while(preceeding != "\\\\")
	  {
	    activities.add_edge(labelToIdMapper[preceeding], labelToIdMapper[label]);

	    std::cin >> preceeding;
	  }

	std::cin >> label;
      }

    //Export initial et Construction du réseau MPM
    Exporter<PlanningActivity>::ToGraphviz(activities, "activityGraph.graph");

    MpmNetworkBuilder mpmBuilder(activities);

    mpmBuilder.buildInto(network);
  }
  
  //Calcul des dates et export
  MpmDatesComputer dates(network);
  dates.compute();

  config.setGraphLabel("MPM chart TP1");
  Export::GraphvizMpmPrepare(network, config);
  Export::GraphvizPathHighlight( config, dates.criticalPath() );
  Export::ToGraphviz(network, config, "bin/MPM_chart.graph");

  system("dot -Tpng bin/activityGraph.graph -o bin/activityGraph.png");
  system("dot -Tpng bin/MPM_chart.graph -o bin/MPM_chart.png");

  return 0;
}
