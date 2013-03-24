#ifndef _Visitor
#define _Visitor

#include <iostream>
#include "GraphTypes.hpp"

namespace GraphFunctor
{

  struct Visitor{
    Visitor();

    virtual ~Visitor();

    virtual void operator()(const GraphTypes::node_id & node)=0;
  };

};

#endif
