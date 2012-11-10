#ifndef CREATESET
#define CREATESET

#include <set>

/**
 *@class CreateSet
 *a class for std::set initialisation
 *usage:
 *std::set<int> v = CreateSet<int>(1,2,3)(1,2)(1)
 *you can insert from 1 to 3 values with on brace ()
 */
template <typename T>
class CreateSet{
private:
  std::set<T> _set;

public:
  /**
   *@constructor
   *inserts a single element
   *@param T& element to insert
   */
  CreateSet(const T&);

  /**
   *@constructor
   *inserts two elements
   *@param T& element to insert
   *@param T& element to insert
   */
  CreateSet(const T&, const T&);

  /**
   *@constructor
   *inserts three elements
   *@param T& element to insert
   *@param T& element to insert
   *@param T& element to insert
   */
  CreateSet(const T&, const T&, const T&);

  /**
   *@constructor
   *inserts all the elements of the given set into the new created set
   *useful to "complete" a set in order to initialize another one
   *@param std::set<T>& set of elements to insert
   */
  CreateSet(const std::set<T>&);

  /**
   *@operator ()
   *inserts single element
   *@param T& element to insert
   */
  CreateSet<T> & operator()(const T&);

  /**
   *@operator ()
   *inserts two elements
   *@param T& element to insert
   *@param T& element to insert
   */
  CreateSet<T> & operator()(const T&, const T&);

  /**
   *@operator ()
   *inserts three elements
   *@param T& element to insert
   *@param T& element to insert
   *@param T& element to insert
   */
  CreateSet<T> & operator()(const T&, const T&, const T&);

  /**
   *@operator ()
   *inserts all the elements of the given set into the new created set
   *useful to "complete" a set in order to initialize another one
   *@param std::set<T>& set of elements to insert
   */
  CreateSet<T> & operator()(const std::set<T>&);

  /**
   *@operator
   *conversion operator (back to std::set)
   */
  operator std::set<T>();
};




/****************************************************************/
  
template <typename T>
CreateSet<T>::CreateSet(const T& val)
{
  _set.insert(val);
}

template <typename T>
CreateSet<T>::CreateSet(const T& val1, const T& val2)
{
  _set.insert(val1);
  _set.insert(val2);
}

template <typename T>
CreateSet<T>::CreateSet(const T& val1, const T& val2, const T& val3)
{
  _set.insert(val1);
  _set.insert(val2);
  _set.insert(val3);
}

template <typename T>
CreateSet<T>::CreateSet(const std::set<T> & v)
{
  _set.insert(v.begin(), v.end());
}

template <typename T>
CreateSet<T> & CreateSet<T>::operator()(const T& val)
{
  _set.insert(val);
  return *this;
}

template <typename T>
CreateSet<T> & CreateSet<T>::operator()(const T& val1, const T& val2)
{
  _set.insert(val1);
  _set.insert(val2);
  return *this;
}

template <typename T>
CreateSet<T> & CreateSet<T>::operator()(const T& val1, const T& val2, const T& val3)
{
  _set.insert(val1);
  _set.insert(val2);
  _set.insert(val3);
  return *this;
}

template <typename T>
CreateSet<T> & CreateSet<T>::operator()(const std::set<T> & v)
{

  _set.insert(v.begin(), v.end());
  return *this;
}

template <typename T>
CreateSet<T>::operator std::set<T>()
{
  return _set;
}

#endif
