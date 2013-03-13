#ifndef _MpmDatesComputer
#define _MpmDatesComputer

#include <memory>

#include "MpmNetwork.hpp"
#include "MpmEdgeWeighter.hpp"
#include "PathFinding.hpp"

class MpmDatesComputer
{
public:
  MpmDatesComputer(MpmNetwork & network,
		   const GraphTypes::Planning::Duration & ProjectStart=0);

  void compute();

  const GraphTypes::Path & criticalPath()const;

private:
  MpmNetwork & _network;

  PathFinding<MpmTask> _lookup;

  GraphTypes::Path _critical_path;

  void _early_start_computation();

  void _late_start_computation();

  const GraphTypes::Planning::Duration & _min_following_early_start(const GraphTypes::node_id & node);

  void _slacks_computation();
};

#endif
