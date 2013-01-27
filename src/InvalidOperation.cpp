#include "InvalidOperation.hpp"

using namespace GraphException;

InvalidOperation::InvalidOperation(const std::string & message, const int & line, const std::string & file, const std::string & context, const GraphTypes::Exceptions::Verbosity & verbosity): BasicGraphException(message, line, file, context, verbosity){}

