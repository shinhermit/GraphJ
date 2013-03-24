#ifndef _InvalidNodeID
#define _InvalidNodeID

#include "BasicGraphException.hpp"

namespace GraphException
{
  class InvalidNodeID : public BasicGraphException
  {
  private:
    GraphTypes::node_id _badID;

  public:
    InvalidNodeID(const GraphTypes::node_id & badID,
		  const std::string & message="InvalidNodeID",
		  const int & line=-1,
		  const std::string & file="",
		  const std::string & context="",
		  const GraphTypes::Exceptions::Verbosity & verbosity=GraphTypes::Exceptions::VERBOSE);

    InvalidNodeID(const InvalidNodeID & source);

    InvalidNodeID & operator=(const InvalidNodeID & source);

    const char * what()const throw();
  };
};

#endif
