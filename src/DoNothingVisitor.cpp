#include "DoNothingVisitor.hpp"

using namespace GraphFunctor;

DoNothingVisitor::DoNothingVisitor(){}

DoNothingVisitor::~DoNothingVisitor(){}

void DoNothingVisitor::operator()(const GraphTypes::node_id & node){}
