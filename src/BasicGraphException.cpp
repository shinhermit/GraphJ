#include "BasicGraphException.hpp"

using namespace GraphException;

std::string BasicGraphException::_moreInfo()const
{
  std::ostringstream oss;

  if(_verbosity == GraphTypes::Exceptions::VERBOSE && _file != "")
    {
      oss << "in File \"" << _file << "\"";

      if(_context != ""){
	oss << ", context: \"" << _context << "\"";
      }

      if(_line != -1)
	{
	  oss << ", at Line " << _line;
	}

      oss << std::endl;
    }

  return oss.str();
}

BasicGraphException::BasicGraphException(const std::string & message, const int & line, const std::string & file, const std::string & context, const GraphTypes::Exceptions::Verbosity & verbosity):
  std::runtime_error( message.c_str() ),
  _line(line),
  _file(file),
  _context(context),
  _verbosity(verbosity)
{}

BasicGraphException::BasicGraphException(const BasicGraphException & source):
  std::runtime_error(source),
  _line(source._line),
  _file(source._file),
  _context(source._context),
  _verbosity(source._verbosity)
{}

BasicGraphException & BasicGraphException::operator=(const BasicGraphException & source)
{
  std::runtime_error::operator=(source);
  _line = source._line;
  _file = source._file;
  _context = source._context;
  _verbosity = source._verbosity;

  return *this;
}

BasicGraphException::~BasicGraphException()throw(){}

const char * BasicGraphException::what()const throw()
{
  std::ostringstream oss;

  oss << std::runtime_error::what() << std::endl;

  oss << _moreInfo();

  return oss.str().c_str();
}
