#include "InvalidNodeID.hpp"

using namespace GraphException;

InvalidNodeID::InvalidNodeID(const GraphTypes::node_id & badID,
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
  _badID(badID)
{}

InvalidNodeID::InvalidNodeID(const InvalidNodeID & source):
  BasicGraphException(source),
  _badID(source._badID){}

InvalidNodeID & InvalidNodeID::operator=(const InvalidNodeID & source)
{
  BasicGraphException::operator=(source);
  _badID = source._badID;

  return *this;
}

const char * InvalidNodeID::what()const throw()
{
  std::ostringstream oss;

  oss << BasicGraphException::what() << std::endl;

  oss << "Given invalid ID is: " << _badID << std::endl;

  return oss.str().c_str();
}
