#ifndef GRAPHTYPES
#define GRAPHTYPES

class GraphTypes{
public:

  typedef float Cost;

  enum EdgeType{DIRECTED, UNDIRECTED};

  enum EdgeState{WEIGHTED, UNWEIGHTED};

  enum What{NODES, CONTENTS};

  enum NodeType{CONTAINER, NOCONTENT};

  enum Default{DEFAULT};
};

#endif
