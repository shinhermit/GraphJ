#include "InvalidNodeIDException.hpp"

using namespace GraphException;

InvalidNodeIDException::InvalidNodeIDException(GraphTypes::node_id badID, std::string message, int line, std::string file, std::string context, GraphTypes::Exceptions::Verbosity verbosity):BasicGraphException(message, line, file, context, verbosity), _badID(badID){}

InvalidNodeIDException::InvalidNodeIDException(const InvalidNodeIDException & source):BasicGraphException(source), _badID(source._badID){}

InvalidNodeIDException & InvalidNodeIDException::operator=(const InvalidNodeIDException & source)
{
  BasicGraphException::operator=(source);
  _badID = source._badID;

  return *this;
}

const char * InvalidNodeIDException::what()const throw()
{
  std::ostringstream oss;

  oss << std::runtime_error::what() << std::endl;

  oss << "Given invalid ID is: " << _badID << std::endl;

  oss << _moreInfo();

  return oss.str().c_str();
}
