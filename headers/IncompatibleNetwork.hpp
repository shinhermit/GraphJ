#ifndef _IncompatibleNetwork
#define _IncompatibleNetwork

#include "BasicGraphException.hpp"
#include "GraphTypes.hpp"

namespace GraphException
{

  class IncompatibleNetwork : public BasicGraphException
  {
  public:
    IncompatibleNetwork(GraphTypes::FlowTypes::Violation violation,
			const std::string & context="");
  };

}

#endif
