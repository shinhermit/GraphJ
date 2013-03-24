#ifndef _Importer
#define _Importer

#include <iostream>
#include <fstream>

#include "GraphvizAttributesHolder.hpp"
#include "FlowNetwork.hpp"
#include "Edge.hpp"
#include <StringJ.hpp>

class Importer
{
public:
  
  static void User(FlowNetwork<> & network,
		   GraphvizAttributesHolder & config);

  static void Raw(FlowNetwork<> & network,
		  GraphvizAttributesHolder & config,
		  const std::string & filename);

private:
  static void _raw(FlowNetwork<> & network,
		   GraphvizAttributesHolder & config,
		   std::istream & in,
		   const std::string & nodesMessage="",
		   const std::string & edgesMessage="");
};

#endif
