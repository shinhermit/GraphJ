using namespace GraphFunctor;

template<typename T, typename V>
bool MapValueComparator<T,V>::operator()(const std::pair<T,V> & pair_min,
					 const std::pair<T,V> & pair_max)const
{
  return pair_min.second < pair_max.second;
}
