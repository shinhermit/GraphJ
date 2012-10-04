#ifndef EDGE
#define EDGE

class Edge{
private:
  int _source;
  int _target;
public:
  Edge(int node_id1, int node_id2);
  Edge(const Edge & source);
  ~Edge();
};

#endif
