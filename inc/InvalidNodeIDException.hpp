#ifndef _InvalidNodeIDException
#define _InvalidNodeIDException

#include "BasicGraphException.hpp"

namespace GraphException
{
  class InvalidNodeIDException : public BasicGraphException
  {
  private:
    GraphTypes::node_id _badID;
  public:
    InvalidNodeIDException(GraphTypes::node_id badID, std::string message="InvalidNodeIDException", int line=-1, std::string file="", std::string context="", GraphTypes::Exceptions::Verbosity verbosity=GraphTypes::Exceptions::VERBOSE);

    InvalidNodeIDException(const InvalidNodeIDException & source);

    InvalidNodeIDException & operator=(const InvalidNodeIDException & source);

    const char * what()const throw();
  };
};

#endif
