
template<typename Type>
std::string Exporter<Type>::_graphviz_headers(const Graph<Type> & graph,
					      const GraphvizAttributesHolder & config)
{
  std::ostringstream oss;

  if( graph.is_directed() )
    oss << "strict digraph " << config.graphName() << "{" << std::endl;
  else
    oss << "strict graph " << config.graphName() << "{" << std::endl;

  oss << "graph " << config.globalAttributes().toString() << std::endl;

  oss << "node " << config.nodesGlobalAttributes().toString() << std::endl;

  oss << "edge " << config.edgesGlobalAttributes().toString() << std::endl;

  if(config.graphLegend() != "")
    oss << "{rank=sink;\nLegend [shape=none, fontsize=10, margin=\"0.5,0.2\", label=\"" << config.graphLegend() << "\"]}" << std::endl;

  return oss.str();
}

template<typename Type>
std::string Exporter<Type>::_graphviz_nodes(const Graph<Type> & graph,
					    const GraphvizAttributesHolder & config)
{
  typename Graph<Type>::NodeIterator node;
  std::ostringstream oss;

  node = graph.nodes_begin();
  while( node != graph.nodes_end() )
    {
      oss << *node;

      const GraphvizAttributes & attr = config.attributesOf(*node);

      oss << attr.toString();

      oss << std::endl;

      ++node;
    }

  return oss.str();
}

template<typename Type>
std::string Exporter<Type>::_graphviz_edges(const Graph<Type> & graph,
					    const GraphvizAttributesHolder & config)
{
  typename Graph<Type>::EdgeIterator edge;
  std::ostringstream oss;

  const std::string linkSymbol = graph.is_directed() ? "->" : "--";

  edge = graph.edges_begin();
  while( edge != graph.edges_end() )
    {
      oss << edge->source() << linkSymbol << edge->target();

      GraphvizAttributes & attr = const_cast<GraphvizAttributes&>( config.attributesOf(*edge) );

      if(graph.is_weighted() && attr.label() == "")
	attr.setLabel( GraphFunctor::StringConverter::StringFrom<GraphTypes::Cost>(graph.getCost(edge->source(), edge->target())) );

      oss << attr.toString();

      oss << std::endl;

      ++edge;
    }

  return oss.str();
}

template<typename Type>
void Exporter<Type>::_highlight_node(GraphvizAttributesHolder & config,
				     const GraphTypes::node_id & node,
				     const GraphTypes::Color & color,
				     const GraphTypes::Graphviz::StyleAttribute & nodeStyle)
{

  GraphvizAttributes & attr = config.attributesOf(node);

  attr.setColor(color);
  attr.setStyle(nodeStyle);
}

template<typename Type>
void Exporter<Type>::_highlight_edge(GraphvizAttributesHolder & config,
				     const Edge & edge,
				     const GraphTypes::Color & color)
{

  GraphvizAttributes &  attr = config.attributesOf(edge);

  attr.setColor(color);
  attr.setFontColor(color);
}

template<typename Type>
std::string Exporter<Type>::_graphviz_footers()
{
  return "}";
}

template<typename Type>
std::string Exporter<Type>::ToString(const Graph<Type> & graph)
{
  std::string buffer;
  GraphFunctor::DefaultVisitor<Type> visitor(graph, buffer);

  Traverse<Type>::Nodes(const_cast<Graph<Type>&>(graph), visitor);

  return buffer;
}

template<typename Type>
std::string Exporter<Type>::ToMathString(const Graph<Type> & graph)
{
  std::string S_buffer;
  std::string A_buffer;
  std::string C_buffer;
  GraphFunctor::MathVisitor<Type> visitor(graph, S_buffer, A_buffer, C_buffer);
  std::ostringstream oss;

  Traverse<Type>::Nodes(const_cast<Graph<Type>&>(graph), visitor);

  oss << "S={" + S_buffer + "}" << std::endl
      << "A={" + A_buffer + "}" << std::endl
      << "C={" + C_buffer + "}" << std::endl;

  return oss.str();
}

template<typename Type>
void Exporter<Type>::ToStream(const Graph<Type> & graph,
			      std::ostream & out)
{
  out << ToString(graph) << std::endl;
}

template<typename Type>
void Exporter<Type>::GraphvizPathHighlight(GraphvizAttributesHolder & config,
					   const GraphTypes::Path & path,
					   const GraphTypes::Color & col,
					    const GraphTypes::Graphviz::StyleAttribute & nodeStyle)
{
  std::list<GraphTypes::node_id>::const_iterator node;
  GraphTypes::node_id sourceNode;

  node = path.begin();

  while( node != path.end() )
    {
      _highlight_node(config, *node, col, nodeStyle);

      sourceNode = *node;
      ++node;

      if( node != path.end() )
	{
	  _highlight_edge( config, Edge(sourceNode, *node), col );
	}
    }
}

template<typename Type>
void Exporter<Type>::GraphvizPathsHighlight(GraphvizAttributesHolder & config,
					    const std::list<GraphTypes::Path> & paths,
					    const GraphTypes::Graphviz::StyleAttribute & nodeStyle)
{
  GraphTypes::NamedColor::ColorNameIterator col;
  std::list<GraphTypes::Path>::const_iterator onePath;

  col = ++GraphTypes::NamedColor::Names_begin();
  for(onePath = paths.begin(); onePath != paths.end(); ++onePath)
    {
      GraphvizPathHighlight(config, *onePath, *col, nodeStyle);

      ++col; if( col == GraphTypes::NamedColor::Names_end() ) col = GraphTypes::NamedColor::Names_begin();
    }
}

template<typename Type>
void Exporter<Type>::_mpm_node_prepare(const MpmNetwork & network,
				       GraphvizAttributesHolder & config,
				       const GraphTypes::node_id & node)
{
  std::string cartouche("");

  const MpmTask & task = network.flowGraph().get_node_content(node);

  const GraphTypes::Planning::Duration & earlyStart = task.earlyStart();
  const GraphTypes::Planning::Duration & lateStart = task.lateStart();
  const GraphTypes::Planning::Duration & duration = task.duration();

  const GraphTypes::Planning::Duration & totalSlack = task.totalSlack();
  const GraphTypes::Planning::Duration & freeSlack = task.freeSlack();
  const GraphTypes::Planning::Duration & sureSlack = task.sureSlack();

  cartouche = cartouche+"|"+task.label()+"|";

  if( node != network.source() && node != network.sink() )
    {
      cartouche += GraphFunctor::StringConverter::StringFrom<GraphTypes::Planning::Duration>(duration) + "|";
    }

  cartouche += "\\n|";

  cartouche += GraphFunctor::StringConverter::StringFrom<GraphTypes::Planning::Duration>(earlyStart) + "|";
  cartouche += GraphFunctor::StringConverter::StringFrom<GraphTypes::Planning::Duration>(lateStart) + "|";

  if( node != network.source() && node != network.sink() )
    {
      cartouche += "\\n|";

      cartouche += GraphFunctor::StringConverter::StringFrom<GraphTypes::Planning::Duration>(totalSlack) + "|";
      cartouche += GraphFunctor::StringConverter::StringFrom<GraphTypes::Planning::Duration>(freeSlack) + "|";
      cartouche += GraphFunctor::StringConverter::StringFrom<GraphTypes::Planning::Duration>(sureSlack) + "|";
    }

  config.attributesOf(node).setLabel(cartouche);
}

template<typename Type>
void Exporter<Type>::GraphvizMpmPrepare(const MpmNetwork & network,
					GraphvizAttributesHolder & config)
{
  const Graph<MpmTask> & flowGraph = network.flowGraph();

  config.nodesGlobalAttributes().setShape(GraphTypes::Graphviz::ShapeAttribute::BOX);
  config.setGraphLegend("|Task label| duration|\\n|Early Start| Late Start|\\n|Total Slack| Free Slack| Sure Slack|");

  for(Graph<MpmTask>::NodeIterator node = flowGraph.nodes_begin();
      node != flowGraph.nodes_end();
      ++node)
    {
      _mpm_node_prepare(network, config, *node);
    }
}

template<typename Type>
void Exporter<Type>::SetFnCapacities(const FlowNetwork<Type> & network,
				     GraphvizAttributesHolder & config)
{
  std::string label;
  const Graph<Type> & flowGraph = network.flowGraph();
  GraphTypes::FlowTypes::Flow minCapacity, maxCapacity, flow;

  for(typename Graph<Type>::EdgeIterator edge=flowGraph.edges_begin();
      edge!=flowGraph.edges_end();
      ++edge)
    {
      minCapacity = network.minCapacity( edge->source(), edge->target() );
      maxCapacity = network.maxCapacity( edge->source(), edge->target() );
      flow = network.flow( edge->source(), edge->target() );

      label = "(";
      label += StringJ::From<GraphTypes::FlowTypes::Flow>(minCapacity)+","+StringJ::From<GraphTypes::FlowTypes::Flow>(maxCapacity)+","+StringJ::From<GraphTypes::FlowTypes::Flow>(flow)+")";
      config.attributesOf(*edge).setLabel(label);
    }
}


template<typename Type>
GraphvizAttributesHolder Exporter<Type>::SetFnCapacities(const FlowNetwork<Type> & network)
{
  GraphvizAttributesHolder config;
  SetFnCapacities(network, config);

  return config;
}

template<typename Type>
std::string Exporter<Type>::ToGraphviz(const Graph<Type> & graph,
				       const GraphvizAttributesHolder & config)
{
  std::ostringstream oss;
  oss << _graphviz_headers(graph, config);

  oss << _graphviz_nodes(graph, config);

  oss << _graphviz_edges(graph, config);

  oss << _graphviz_footers();

  return oss.str();
}

template<typename Type>
std::string Exporter<Type>::ToGraphviz(const Graph<Type> & graph)
{
  GraphvizAttributesHolder config;

  return ToGraphviz(graph, config);
}

template<typename Type>
void Exporter<Type>::ToGraphviz(const Graph<Type> & graph,
				const GraphvizAttributesHolder & config,
				const std::string & filename)
{
  std::ofstream file;
  file.open(filename.c_str(), std::ios::out | std::ios::trunc);

  file << ToGraphviz(graph, config);

  file.close();
}

template<typename Type>
void Exporter<Type>::ToGraphviz(const Graph<Type> & graph,
				const std::string & filename)
{
  std::ofstream file;
  file.open(filename.c_str(), std::ios::out | std::ios::trunc);

  file << ToGraphviz(graph);

  file.close();
}
