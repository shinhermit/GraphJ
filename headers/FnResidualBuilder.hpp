#ifndef _FnResidualBuilder
#define _FnResidualBuilder

#include "FlowNetwork.hpp"

template<typename Type=GraphTypes::Default>
class FnResidualBuilder
{
public:
  FnResidualBuilder(const FlowNetwork<Type> & network);

  void build();

  const Graph<> & residualGraph();

private:
  const FlowNetwork<Type> & _network;
  Graph<> _residualGraph;

  void _copy_nodes();
};

#include "FnResidualBuilder.cpp"

#endif
