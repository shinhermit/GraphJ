#ifndef _MpmNetworkBuilder
#define _MpmNetworkBuilder

#include "MpmNetwork.hpp"
#include "PlanningActivity.hpp"

class MpmNetworkBuilder
{
public:
  MpmNetworkBuilder(Graph<PlanningActivity> & planning);

  void buildInto(MpmNetwork & network);

  MpmNetwork build();

private:
  Graph<PlanningActivity> & _planning;
};

#endif
