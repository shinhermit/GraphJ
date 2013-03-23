#include <iostream>
#include "CanonicalNetwork.hpp"

int main()
{
  CanonicalNetwork<> network(2,3);

  assert( network.source() == 2);
  assert( network.sink() == 3);

  network.setSource(0);
  network.setSink(1);

  assert( network.source() == 0);
  assert( network.sink() == 1);

  Graph<> & flowGraph = network.flowGraph();

  flowGraph.add_edge(0,2, 1);
  flowGraph.add_edge(0,3, 2);
  flowGraph.add_edge(2,3, 3);
  flowGraph.add_edge(2,1, 4);
  flowGraph.add_edge(3,1, 4);

  Graph<> graph = flowGraph;

  std::cout << "Half trust worthy (validator not complete!)" << std::endl;

  return 0;
}
