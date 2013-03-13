#ifndef _GraphTypes
#define _GraphTypes

#include <list>
#include <string>

#include "ShapeAttribute.hpp"
#include "StyleAttribute.hpp"
#include "Color.hpp"
#include "ColorIntensity.hpp"
#include "ColorIncrementor.hpp"
#include "NamedColor.hpp"

namespace GraphTypes
{
  typedef unsigned long node_id;

  typedef float Cost;

  typedef std::list<node_id> Path;

  enum EdgeType{DIRECTED, UNDIRECTED};

  enum EdgeState{WEIGHTED, UNWEIGHTED};

  // enum What{NODES, CONTENTS};

  enum NodeType{CONTAINER, NOCONTENT};

  enum Default{DEFAULT};

  namespace Exceptions
  {
    enum Verbosity{BRIEVE, VERBOSE};
  };

  namespace Iterator
  {
    enum Type{SIMPLE, DOUBLE};
  };

  namespace Algorithms
  {
    typedef unsigned int Color;

    enum SearchAlgorithm{DIJKSTRA, BELLMAN};

    enum AlgorithmicClass{GREEDY, DYNAMIC};

    enum OptimizationType{MAXIMIZE, MINIMIZE};

    const float POSITIVE_INFINITY = 20000.F;
    const float NEGATIVE_INFINITY = -20000.F;
  };

  namespace Planning
  {
    typedef unsigned int Activity_id;
    typedef float Duration;

    enum EdgeDirection{DIRECT, REVERSED};
  };

};

#endif
