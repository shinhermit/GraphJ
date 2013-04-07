#include "Importer.hpp"

void Importer::_raw(FlowNetwork<> & network,
		    GraphvizAttributesHolder & config,
		    std::istream & in,
		    const std::string & nodesMessage,
		    const std::string & edgesMessage)
{
  std::string label(""), sourceNodeLabel(""), targetNodeLabel("");
  std::map<std::string, GraphTypes::node_id> labelToIdMapper;
  GraphTypes::Flow minCapacity, maxCapacity, flow;
  int i, j;

  //nodes
  if(nodesMessage != "")
    std::cout << nodesMessage << std::endl;

  if( in.good() )
    in >> label;

  i=0;
  while(label != "fin.")
    {
      network.add_node(i);
      config.attributesOf(i).setLabel(label);
      labelToIdMapper[label] = i;

      if( in.good() )
	in >> label;

      ++i;
    }

  //edges
  if(edgesMessage != "")
    std::cout << edgesMessage << std::endl;

  if( in.good() )
    in >> sourceNodeLabel;

  while(sourceNodeLabel != "fin.")
    {
      in >> targetNodeLabel >> minCapacity >> maxCapacity >> flow;
      i = labelToIdMapper[sourceNodeLabel];
      j = labelToIdMapper[targetNodeLabel];
      network.add_flow(i, j, minCapacity, flow, maxCapacity);

      label = "(";
      label += StringJ::From<GraphTypes::Flow>(minCapacity)+","+StringJ::From<GraphTypes::Flow>(maxCapacity)+","+StringJ::From<GraphTypes::Flow>(flow)+")";
      config.attributesOf( Edge(i,j) ).setLabel(label);

      if( in.good() )
	in >> sourceNodeLabel;
    }

  //source and sink
  if( in.good() )
    {
      in >> label;
      network.setSource( labelToIdMapper[label] );
    }

  if( in.good() )
    {
      in >> label;
      network.setSink( labelToIdMapper[label] );
    }
  
  
}
  
void Importer::User(FlowNetwork<> & network,
		    GraphvizAttributesHolder & config)
{
  std::string nodesMessage = "Acquisition des noeuds. Entrez les étiquettes (ex: A).\n";
  std::string edgesMessage = "Acquisition des flux: label_source label_cible capacité_min capacité_max valeur_flux.\nEx: A B 0 2 1";

  _raw(network, config, std::cin, nodesMessage, edgesMessage);
}

void Importer::Raw(FlowNetwork<> & network,
		   GraphvizAttributesHolder & config,
		   const std::string & filename)
{
  std::ifstream file;

  file.open(filename.c_str(), std::ios::in );

  _raw(network, config, file);

  file.close();
  
}
