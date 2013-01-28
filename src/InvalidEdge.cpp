#include "InvalidEdge.hpp"

using namespace GraphException;

InvalidEdge::InvalidEdge(const GraphTypes::node_id & origin,
			 const GraphTypes::node_id & target,
			 const std::string & message,
			 const int & line,
			 const std::string & file,
			 const std::string & context,
			 const GraphTypes::Exceptions::Verbosity & verbosity):
  BasicGraphException(message,
		      line,
		      file,
		      context,
		      verbosity),
  _origin(origin),
  _target(target)
{}

InvalidEdge::InvalidEdge(const InvalidEdge & source):
  BasicGraphException(source),
  _origin(source._origin),
  _target(source._target)
{}

InvalidEdge & InvalidEdge::operator=(const InvalidEdge & source)
{
  BasicGraphException::operator=(source);
  _origin = source._origin;
  _target = source._target;

  return *this;
}

const char * InvalidEdge::what()const throw()
{
  std::ostringstream oss;

  oss << BasicGraphException::what() << std::endl;

  oss << "Given Edge is: (" << _origin << "," << _target << ")" << std::endl;

  return oss.str().c_str();
}
