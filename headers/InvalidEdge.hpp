#ifndef _InvalidEdge
#define _InvalidEdge

#include "BasicGraphException.hpp"

namespace GraphException
{
  class InvalidEdge : public BasicGraphException
  {
  private:
    GraphTypes::node_id _origin;
    GraphTypes::node_id _target;

  public:
    InvalidEdge(const GraphTypes::node_id & origin,
		const GraphTypes::node_id & target,
		const std::string & message="InvalidEdge",
		const int & line=-1,
		const std::string & file="",
		const std::string & context="",
		const GraphTypes::Exceptions::Verbosity & verbosity=GraphTypes::Exceptions::VERBOSE);

    InvalidEdge(const InvalidEdge & source);

    InvalidEdge & operator=(const InvalidEdge & source);

    const char * what()const throw();
  };
};

#endif
