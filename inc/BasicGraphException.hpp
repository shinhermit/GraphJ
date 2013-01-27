#ifndef _BasicGraphException
#define _BasicGraphException

#include <stdexcept>
#include <string>
#include <sstream>
#include "GraphTypes.hpp"

namespace GraphException
{
  class BasicGraphException : public std::runtime_error
  {
  protected:
    int _line;
    std::string _file;
    std::string _context;
    GraphTypes::Exceptions::Verbosity _verbosity;

    std::string _moreInfo()const;

  public:
    BasicGraphException(const std::string & message="BasicGraphException", const int & line=-1, const std::string & file="", const std::string & context="", const GraphTypes::Exceptions::Verbosity & verbosity=GraphTypes::Exceptions::VERBOSE);

    BasicGraphException(const BasicGraphException & source);

    BasicGraphException & operator=(const BasicGraphException & source);

    virtual ~BasicGraphException() throw();

    virtual const char * what()const throw();
  };
};

#endif
