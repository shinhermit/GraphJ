#ifndef _StringFrom
#define _StringFrom

namespace GraphFunctor
{

  struct StringConverter
  {

    /**
     *@fn
     *converts a (générique) type to std::string
     *espacially meant to convert from int and double
     *@param string the string value to convert
     *@return Type result of the conversio into the (générique) type
     */
    template <typename Literal>
    static std::string StringFrom(Literal value);

    /**
     *@fn
     *converts a std::string to another type
     *espacially meant to convert to int and double
     *@param string the string value to convert
     *@return Type result of the conversion into the (générique) other type
     */
    template <typename Literal>
    static Literal StringTo(std::string);
  };

};

template <typename Literal>
std::string GraphFunctor::StringConverter::StringFrom(Literal value)
{
  std::ostringstream oss;
  std::string res;

  oss << value;
  res = oss.str();
  return res;
}


template <typename Literal>
Literal GraphFunctor::StringConverter::StringTo(std::string stringValue)
{
  std::istringstream iss(stringValue);
  Literal res;
    
  iss >> res;
  return res;
}

#endif
