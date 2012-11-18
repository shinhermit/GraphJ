#ifndef GRAPHVIZDISPLAY
#define GRAPHVIZDISPLAY

#include "Visitor.hpp"
#include <fstream>
#include <sstream>
#include <string>

template<typename Type>
class GraphvizVisitor : public Visitor<Type>{
private:
  GraphTypes::What _what;
  std::string _buffer;

public:
  GraphvizVisitor(GraphTypes::What what_to_display=GraphTypes::NODES);
  virtual ~GraphvizVisitor();

  virtual void treat(Graph<Type> graph, Node::node_id node);

  void display_what(GraphTypes::What what);

  std::string nodes_representation()const;

  void flush();
};

#include "GraphvizVisitor.cpp"

#endif
