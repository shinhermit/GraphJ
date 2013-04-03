#ifndef _FordFulkerson
#define _FordFulkerson

#include <cmath>

#include "FlowNetwork.hpp"
#include "Traverse.hpp"
#include "FnResidualBuilder.hpp"

template<typename Content=GraphTypes::Default>
class FordFulkerson
{
public:
  FordFulkerson(FlowNetwork<Content> & network);

  void maximize();

private:
  FlowNetwork<Content> & _network;
  FnResidualBuilder<Content> _residualBuilder;
  Traverse<Content> _traverser;
  std::list<GraphTypes::node_id> _path;

  void _nil_flow();

  bool _exists_path_to_sink()const;

  void _extract_path_to_sink();

  GraphTypes::Flow _min_residual_on_path();

  void _change_flow(const GraphTypes::Flow & delta);
};

#include "FordFulkerson.cpp"

#endif
