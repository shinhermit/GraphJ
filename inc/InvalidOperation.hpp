#ifndef _InvalidOperation
#define _InvalidOperation

#include "BasicGraphException.hpp"

namespace GraphException
{
  class InvalidOperation : public BasicGraphException
  {
  public:
    InvalidOperation(const std::string & message="BasicGraphException", const int & line=-1, const std::string & file="", const std::string & context="", const GraphTypes::Exceptions::Verbosity & verbosity=GraphTypes::Exceptions::VERBOSE);
  };
};

#endif
