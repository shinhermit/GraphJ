#include "IncompatibleNetwork.hpp"

using namespace GraphException;

IncompatibleNetwork::IncompatibleNetwork(GraphTypes::FlowTypes::Violation violation,
					 const std::string & context):
  BasicGraphException(std::string("Violation: ")+violation.toString(), -1, "", context)
{}
