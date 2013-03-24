#ifndef _Edge
#define _Edge

#include "Node.hpp"

class Edge
{
protected:
  GraphTypes::node_id _origin;
  GraphTypes::node_id _target;

public:
  Edge();

  Edge(const GraphTypes::node_id & origin,
       const GraphTypes::node_id & target);

  Edge(const Edge & source);

  bool operator==(const Edge & ref)const;
  bool operator<(const Edge & ref)const;
  bool operator<=(const Edge & ref)const;
  bool operator>(const Edge & ref)const;
  bool operator>=(const Edge & ref)const;
  bool operator!=(const Edge & ref)const;

  const GraphTypes::node_id & source()const;
  const GraphTypes::node_id & target()const;
};

#endif
