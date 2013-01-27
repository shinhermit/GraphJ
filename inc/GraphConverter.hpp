#ifndef _GraphConverter
#define _GraphConverter

#include "Graph.hpp"

template<typename Type=GraphTypes::Default>
class GraphConverter
{
private:
  static void _copyNodes(const Graph<Type> & graph, Graph<Type> & convertion);

public:
  static Graph<Type> toDirected(const Graph<Type> & graph);

  static Graph<Type> toUndirected(const Graph<Type> & graph);
};

#include "GraphConverter.cpp"

#endif
