#ifndef _FordFulkerson
#define _FordFulkerson

#include <cmath>
#include <cstdlib>

#include "FlowNetwork.hpp"
#include "Traverse.hpp"
#include "DoNothingVisitor.hpp"
#include "FnResidualBuilder.hpp"

#include <cstdio>
#include "Exporter.hpp"

template<typename Content=GraphTypes::Default>
class FordFulkerson
{
public:
  FordFulkerson(FlowNetwork<Content> & network);

  void maximizeFlow();

private:
  FlowNetwork<Content> & _network;
  FnResidualBuilder<Content> _residualBuilder;
  Traverse<Content> _traverser;
  std::list<GraphTypes::node_id> _path;
  GraphFunctor::DoNothingVisitor _noaction;

  void _nil_flow();

  bool _exists_path_to_sink();

  void _extract_path_to_sink();

  GraphTypes::Flow _min_residual_on_path();

  void _change_flow(const GraphTypes::Flow & delta);
};

#include "FordFulkerson.cpp"

#endif
