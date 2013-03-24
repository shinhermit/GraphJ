#include <iostream>
#include <cstdlib>

#include "FlowNetwork.hpp"
#include "Importer.hpp"
#include "Exporter.hpp"
#include <CommandLineParser.hpp>

int main(int argc, char ** argv)
{
  CommandLineParser parser(argc, argv);
  std::map<std::string, std::string>  commands;
  std::map<std::string, std::string>::iterator it;

  FlowNetwork<> network(GraphTypes::NOCONTENT);
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

  Export::ToGraphviz(network, config, "bin/test_flow_network.graph");

  ::system("dot -Tpng bin/test_flow_network.graph -o bin/test_flow_network.png");

  return 0;
}
