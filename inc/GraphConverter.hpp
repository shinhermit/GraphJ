#ifndef _GraphConverter
#define _GraphConverter

#include "Graph.hpp"

template<typename Type=GraphTypes::Default>
class GraphConverter
{
public:
  static Graph<Type> toDirected(Graph<Type> & graph);

  static Graph<Type> toUndirected(Graph<Type> & graph);
};

#include "GraphConverter.cpp"

#endif
