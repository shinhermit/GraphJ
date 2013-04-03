#ifndef _DoNothingVisitor
#define _DoNothingVisitor

#include "Visitor.hpp"

namespace GraphFunctor
{

  struct DoNothingVisitor : Visitor
  {
    DoNothingVisitor();

    ~DoNothingVisitor();

    void operator()(const GraphTypes::node_id & node);
  };

};

#endif
