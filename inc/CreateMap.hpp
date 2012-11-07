#ifndef CREATEMAP
#define CREATEMAP

#include <string>
#include <sstream>
#include <map>

/**
 *@class CreateMap
 *a class for std::map initialisation
 *usage:
 *std::map<T,U> m = CreateMap<T,U>(T key1, U val1)(T key1, U val2)...(T key_n, U val_n)
 */
template <typename T, typename U>
class CreateMap{
private:
  std::map<T, U> m_map;

public:
  /**
   *@constructor
   *inserts the given (key,val) into the internal map
   *@param T& key first element of a pair<T,U>
   *@param T& key second element of a pair<T,U>
   */
  CreateMap(const T&, const U&);

  /**
   *@operator ()
   *insert a pair<T,U>
   *the advantage here is the chaining:
   *(T key1, U val1)(T key1, U val2)...(T key_n, U val_n)
   *@param T& key first element of a pair<T,U>
   *@param T& key second element of a pair<T,U>
   */
  CreateMap<T, U> & operator()(const T&, const U&);

  /**
   *@operator
   *conversion operator (back to std::map)
   */
  operator std::map<T, U>();
};




/****************************************************************/

template <typename T, typename U>
CreateMap<T,U>::CreateMap(const T& key, const U& val)
{
  m_map[key] = val;
}

template <typename T, typename U>
CreateMap<T, U> & CreateMap<T,U>::operator()(const T& key, const U& val)
{
  m_map[key] = val;
  return *this;
}

template <typename T, typename U>
CreateMap<T,U>::operator std::map<T, U>()
{
  return m_map;
}

#endif
