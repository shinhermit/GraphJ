#include <iostream>
#include <cstdlib>

#include "FordFulkerson.hpp"
#include "Importer.hpp"
#include "Exporter.hpp"
#include "CommandLineParser.hpp"

int main(int argc, char ** argv)
{
  CommandLineParser parser(argc, argv);
  std::map<std::string, std::string>  commands;
  std::map<std::string, std::string>::iterator it;

  FlowNetwork<> network(GraphTypes::NOCONTENT);
  FordFulkerson<> maximizer(network);
  GraphvizAttributesHolder config;

  typedef Exporter<> Export;
  
  parser.parseInto(commands);
  it = commands.find("--file");

  if( it != commands.end() )
    {
      std::string & filename = it->second;
      Importer::Raw(network, config, filename);
    }

  else
    {
      Importer::User(network, config);
    }

  Export::ToGraphviz(network, config, "bin/initial_network.graph");

  maximizer.maximizeFlow();

  Export::SetFnCapacities(network, config);
  Export::ToGraphviz(network, config, "bin/maximized_network.graph");

  ::system("dot -Tpng bin/initial_network.graph -o bin/initial_network.png");
  ::system("dot -Tpng bin/maximized_network.graph -o bin/maximized_network.png");
}
