#ifndef _GraphvizAttributesHolder
#define _GraphvizAttributesHolder

#include <map>
#include <memory>
#include "Edge.hpp"
#include "GraphvizAttributes.hpp"

class GraphvizAttributesHolder
{
private:
  std::string _graphName;

  std::string _graphLegend;

  GraphvizAttributes _graph_global_attributes;

  GraphvizAttributes _nodes_global_attributes;

  GraphvizAttributes _edges_global_attributes;

  std::map<GraphTypes::node_id, GraphvizAttributes> _nodes_attributes;

  std::map<Edge, GraphvizAttributes> _edges_attributes;

public:

  GraphvizAttributesHolder(const std::string & graphLabel="",
			   const std::string & graphName="G");

  void setGraphName(const std::string & graphName);

  void setGraphLabel(const std::string & graphLabel);

  void setGraphLegend(const std::string & graphLegend);

  void clear();

  const std::string &  graphName()const;

  const std::string &  graphLabel()const;

  const std::string &  graphLegend()const;

  GraphvizAttributes &  globalAttributes();
  const GraphvizAttributes &  globalAttributes()const;

  GraphvizAttributes & nodesGlobalAttributes();
  const GraphvizAttributes & nodesGlobalAttributes()const;

  GraphvizAttributes & edgesGlobalAttributes();
  const GraphvizAttributes & edgesGlobalAttributes()const;

  GraphvizAttributes & attributesOf(const GraphTypes::node_id & node);
  const GraphvizAttributes & attributesOf(const GraphTypes::node_id & node)const;

  GraphvizAttributes & attributesOf(const Edge & edge);
  const GraphvizAttributes & attributesOf(const Edge & edge)const;
};

#endif
