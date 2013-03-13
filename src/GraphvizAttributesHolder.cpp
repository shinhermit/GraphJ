#include "GraphvizAttributesHolder.hpp"

GraphvizAttributesHolder::GraphvizAttributesHolder(const std::string & graphName)
  :_graphName(graphName),
   _graph_global_attributes( GraphvizAttributes() ),
   _nodes_global_attributes( GraphvizAttributes() ),
   _edges_global_attributes( GraphvizAttributes() )
{}

void GraphvizAttributesHolder::setGraphName(const std::string & graphName)
{
  _graphName = graphName;
}

void GraphvizAttributesHolder::clear()
{
  _graphName.clear();

  _graph_global_attributes.clear();

  _nodes_global_attributes.clear();

  _edges_global_attributes.clear();

  _nodes_attributes.clear();

  _edges_attributes.clear();
}

const std::string & GraphvizAttributesHolder::graphName()const
{
  return _graphName;
}

GraphvizAttributes &  GraphvizAttributesHolder::globalAttributes()
{
  return _graph_global_attributes;
}

const GraphvizAttributes &  GraphvizAttributesHolder::globalAttributes()const
{
  return _graph_global_attributes;
}

GraphvizAttributes & GraphvizAttributesHolder::nodesGlobalAttributes()
{
  return _nodes_global_attributes;
}

const GraphvizAttributes & GraphvizAttributesHolder::nodesGlobalAttributes()const
{
  return _nodes_global_attributes;
}

GraphvizAttributes & GraphvizAttributesHolder::edgesGlobalAttributes()
{
  return _edges_global_attributes;
}

const GraphvizAttributes & GraphvizAttributesHolder::edgesGlobalAttributes()const
{
  return _edges_global_attributes;
}

GraphvizAttributes & GraphvizAttributesHolder::attributesOf(const GraphTypes::node_id & node)
{
  std::map<GraphTypes::node_id, GraphvizAttributes>::iterator attr_it;

  attr_it = _nodes_attributes.find(node);

  if( attr_it == _nodes_attributes.end() )
    {
      attr_it = _nodes_attributes.insert( std::pair<GraphTypes::node_id, GraphvizAttributes>( node, GraphvizAttributes() ) ).first;
    }

  return attr_it->second;
}

const GraphvizAttributes & GraphvizAttributesHolder::attributesOf(const GraphTypes::node_id & node)const
{
  GraphvizAttributesHolder * _this = const_cast<GraphvizAttributesHolder*>(this);

  return _this->attributesOf(node);
}

GraphvizAttributes & GraphvizAttributesHolder::attributesOf(const Edge & edge)
{
  std::map<Edge, GraphvizAttributes>::iterator attr_it;

  attr_it = _edges_attributes.find(edge);

  if( attr_it == _edges_attributes.end() )
    {
      attr_it = _edges_attributes.insert( std::pair<Edge, GraphvizAttributes>( edge, GraphvizAttributes() ) ).first;
    }

  return attr_it->second;
}

const GraphvizAttributes & GraphvizAttributesHolder::attributesOf(const Edge & edge)const
{
  GraphvizAttributesHolder * _this = const_cast<GraphvizAttributesHolder*>(this);

  return _this->attributesOf(edge);
}
