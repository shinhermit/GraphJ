
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
				     const GraphTypes::NamedColor::E_NamedColor & color)
{

  GraphvizAttributes & attr = config.attributesOf(node);

  attr.setColor( GraphTypes::Color(color) );
  attr.setStyle(GraphTypes::Graphviz::StyleAttribute::FILLED);
}

template<typename Type>
void Exporter<Type>::_highlight_edge(GraphvizAttributesHolder & config,
				     const Edge & edge,
				     const GraphTypes::NamedColor::E_NamedColor & color)
{

  GraphvizAttributes &  attr = config.attributesOf(edge);

  attr.setColor( GraphTypes::Color(color) );
  attr.setFontColor( GraphTypes::Color(color) );
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
void Exporter<Type>::GraphvizPathsHighlight(GraphvizAttributesHolder & config,
					    const std::list<GraphTypes::Path> & paths_highlight)
{
  GraphTypes::NamedColor::ColorNameIterator col;
  std::list<GraphTypes::Path>::const_iterator path;
  std::list<GraphTypes::node_id>::const_iterator node;
  GraphTypes::node_id sourceNode;

  col = GraphTypes::NamedColor::Names_begin();
  for(path = paths_highlight.begin(); path != paths_highlight.end(); ++path)
    {
      node = path->begin();

      while( node != path->end() )
	{
	  _highlight_node(config, *node, *col);

	  sourceNode = *node;
	  ++node;

	  if( node != path->end() )
	    {
	      _highlight_edge( config, Edge(sourceNode, *node), *col );
	    }
	}

      ++col; if( col == GraphTypes::NamedColor::Names_end() ) col = GraphTypes::NamedColor::Names_begin();
    }
}

template<typename Type>
void Exporter<Type>::_mpm_node_prepare(const MpmNetwork & network,
				       GraphvizAttributesHolder & config,
				       const GraphTypes::node_id & node,
				       const std::string & label)
{
  std::string cartouche("");

  const MpmTask & task = network.flowGraph().get_node_content(node);

  const GraphTypes::Planning::Duration & earlyBegin = task.earlyBegin();
  const GraphTypes::Planning::Duration & latelyBegin = task.latelyBegin();
  const GraphTypes::Planning::Duration & duration = task.duration();

  if(label != "")
    cartouche = cartouche+"|"+label+"|";

  else
    cartouche = cartouche+"|"+task.label()+"|";

  if(node != network.source() && node != network.sink())
    {
      cartouche += GraphFunctor::StringConverter::StringFrom<GraphTypes::Planning::Duration>(duration) + "|";
    }

  cartouche += "\\n|";

  cartouche += GraphFunctor::StringConverter::StringFrom<GraphTypes::Planning::Duration>(earlyBegin) + "|";
  cartouche += GraphFunctor::StringConverter::StringFrom<GraphTypes::Planning::Duration>(latelyBegin) + "|";

  config.attributesOf(node).setLabel(cartouche);
}

template<typename Type>
void Exporter<Type>::GraphvizMpmPrepare(const MpmNetwork & network,
					GraphvizAttributesHolder & config,
					const std::string & beginNodeLabel,
					const std::string & endNodeLabel)
{
  const Graph<MpmTask> & flowGraph = network.flowGraph();

  config.nodesGlobalAttributes().setShape(GraphTypes::Graphviz::ShapeAttribute::BOX);

  //source and sink
  _mpm_node_prepare( network, config, network.source(), beginNodeLabel );
  _mpm_node_prepare( network, config, network.sink(), endNodeLabel );

  //other nodes
  for(Graph<MpmTask>::NodeIterator node = flowGraph.nodes_begin();
      node != flowGraph.nodes_end();
      ++node)
    {
      if( *node != network.source() && *node != network.sink() )
	_mpm_node_prepare(network, config, *node);
    }
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
