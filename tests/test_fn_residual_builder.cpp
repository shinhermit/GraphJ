#include <iostream>
#include <cstdlib>

#include "FnResidualBuilder.hpp"
#include "Importer.hpp"
#include "Exporter.hpp"
#include "CommandLineParser.hpp"

int main(int argc, char ** argv)
{
  CommandLineParser parser(argc, argv);
  std::map<std::string, std::string>  commands;
  std::map<std::string, std::string>::iterator it;

  FlowNetwork<> network(GraphTypes::NOCONTENT);
  FnResidualBuilder<> builder(network);
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

  builder.build();


  Export::ToGraphviz(network, config, "bin/flow_network.graph");
  Export::ToGraphviz(builder.residualGraph(), "bin/residual_graph.graph");

  ::system("dot -Tpng bin/flow_network.graph -o bin/flow_network.png");
  ::system("dot -Tpng bin/residual_graph.graph -o bin/residual_graph.png");


  return 0;
}
