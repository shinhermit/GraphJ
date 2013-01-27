#include "Visitor.hpp"

using namespace GraphFunctor;

Visitor::Visitor(){}

Visitor::~Visitor(){}

void Visitor::operator()(const GraphTypes::node_id & node)
{
  std::cout << "Erethic calling of abstract Method Visitor::operator() !!!!" << std::endl;
}
