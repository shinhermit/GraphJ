#ifndef _MapValueComparator
#define _MapValueComparator

#include <map>

namespace GraphFunctor
{
  template<typename T, typename V>
  struct MapValueComparator
  {
    bool operator()(const std::pair<T,V> & pair_min, const std::pair<T,V> & pair_max)const;
  };
};

#include "MapValueComparator.cpp"

#endif
