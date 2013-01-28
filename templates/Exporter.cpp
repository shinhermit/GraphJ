template<typename Type>
std::string Exporter<Type>::_graphviz_headers(const Graph<Type> & graph)
{
  std::ostringstream oss;

  if( graph.is_directed() )
    oss << "strict digraph G{" << std::endl;
  else
    oss << "strict graph G{" << std::endl;

  return oss.str();
}

template<typename Type>
std::string Exporter<Type>::_graphviz_relations(const Graph<Type> & graph)
{
  std::string buffer;
  GraphFunctor::GraphvizVisitor<Type> visitor(graph, buffer);
    
  Traverse<Type>::Nodes(const_cast<Graph<Type>&>(graph), visitor);

  return buffer;
}

template<typename Type>
std::string Exporter<Type>::_graphviz_node_label_mapping(const Graph<Type> & graph,
							 const std::map<GraphTypes::node_id, std::string> & label_mapper)
{
  typename Graph<Type>::NodeIterator node;
  std::map<GraphTypes::node_id, std::string>::const_iterator label_it;
  std::ostringstream oss;

  node = graph.nodes_begin();
  while( node != graph.nodes_end() )
    {

      label_it = label_mapper.find(*node);

      if( label_it != label_mapper.end() )
	{
	  oss << *node <<" [label=\"" << label_it->second << "\"]" << std::endl;
	}

      ++node;
    }

  return oss.str();
}

template<typename Type>
std::string Exporter<Type>::_graphviz_node_color_mapping(const Graph<Type> & graph,
							 const std::map<GraphTypes::node_id, NamedColor::ColorName> & color_mapper)
{
  typename Graph<Type>::NodeIterator node;
  std::map<GraphTypes::node_id, NamedColor::ColorName>::const_iterator color_it;
  std::ostringstream oss;

  node = graph.nodes_begin();
  while( node != graph.nodes_end() )
    {

      color_it = color_mapper.find(*node);
      if( color_it != color_mapper.end() )
	{
	  oss << *node <<" [color=" << NamedColor::ToString(color_it->second) << "]" << std::endl;
	}

      ++node;
    }

  return oss.str();
}

template<typename Type>
std::string Exporter<Type>::_graphviz_paths_highlighting(const Graph<Type> & graph,
							 const std::list<GraphTypes::Path> & paths_highlight)
{
  NamedColor::NameToStringIterator col;
  std::list<GraphTypes::Path>::const_iterator path;
  std::list<GraphTypes::node_id>::const_iterator node;
  GraphTypes::node_id sourceNode;
  std::ostringstream oss;

  col = NamedColor::NamesToString_begin();
  for(path = paths_highlight.begin(); path != paths_highlight.end(); ++path)
    {

      oss << "{" << std::endl << "node [color=" << col->second << ", style=\"filled\"]" << std::endl;
      oss << "edge [color=" << col->second << "]" << std::endl;

      node = path->begin();

      while( node!= path->end() )
	{
	  sourceNode = *node;
	  ++node;

	  if( node != path->end() )
	    {
	      oss << sourceNode << "->" << *node;

	      if( graph.is_weighted() )
		{
		  oss << "[label=\"" << graph.getCost(sourceNode, *node) << "\", fontcolor=" << col->second << "]";
		}

	      oss << std::endl;
	    }
	}

      oss << "}" << std::endl;

      ++col; if( col == NamedColor::NamesToString_end() ) col = NamedColor::NamesToString_begin();
    }

  return oss.str();
}

template<typename Type>
std::string Exporter<Type>::_graphviz_node_meta_mapping(const Graph<Type> & graph,
							const std::map<GraphTypes::node_id, std::string> & label_mapper,
							const std::map<GraphTypes::node_id, NamedColor::ColorName> & color_mapper)
{
  std::ostringstream oss;
  std::string stringColor;
  typename Graph<Type>::NodeIterator nodeIt;

  nodeIt = graph.nodes_begin();
  while( nodeIt != graph.nodes_end() )
    {
      stringColor = NamedColor::ToString( color_mapper.find(*nodeIt)->second );

      oss << *nodeIt <<" [label=\"" << label_mapper.find(*nodeIt)->second << "\", color=" << stringColor << "]" << std::endl;

      ++nodeIt;
    }

  return oss.str();
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
std::string Exporter<Type>::ToMathString(const Graph<Type> & graph,
					 const std::map<GraphTypes::node_id, std::string> & label_mapper)
{
  std::map<GraphTypes::node_id, std::string>::const_iterator it;
  std::ostringstream oss;

  for(it = label_mapper.begin(); it != label_mapper.end(); ++it)
    {
      oss << "s" << it->first << " |--> " << it->second << std::endl;
    }

  oss << toMathString(graph);

  return oss.str();
}

template<typename Type>
void Exporter<Type>::ToStream(const Graph<Type> & graph,
			      std::ostream & out)
{
  out << ToString(graph) << std::endl;
}

template<typename Type>
std::string Exporter<Type>::ToGraphviz(const Graph<Type> & graph)
{
  std::ostringstream oss;
  oss << _graphviz_headers(graph);
  oss << _graphviz_relations(graph);
  oss << _graphviz_footers();

  return oss.str();
}

template<typename Type>
std::string Exporter<Type>::ToGraphviz(const Graph<Type> & graph,
				       const std::map<GraphTypes::node_id, std::string> & label_mapper)
{
  std::ostringstream oss117;

  oss117 << _graphviz_headers(graph);

  oss117 << _graphviz_relations(graph);

  oss117 << _graphviz_node_label_mapping(graph, label_mapper);

  oss117 << _graphviz_footers();

  return oss117.str();
  
}

template<typename Type>
std::string Exporter<Type>::ToGraphviz(const Graph<Type> & graph,
				       const std::map<GraphTypes::node_id, NamedColor::ColorName> & color_mapper)
{
  std::ostringstream oss117;

  oss117 << _graphviz_headers(graph);

  oss117 << "node [style=filled]" << std::endl << std::endl;

  oss117 << _graphviz_relations(graph);

  oss117 << _graphviz_node_color_mapping(graph, color_mapper);

  oss117 << _graphviz_footers();

  return oss117.str();
  
}

template<typename Type>
std::string Exporter<Type>::ToGraphviz(const Graph<Type> & graph,
				       const std::list<GraphTypes::Path> & paths_highlight)
{
  std::ostringstream oss117;

  oss117 << _graphviz_headers(graph);

  oss117 << _graphviz_paths_highlighting(graph, paths_highlight);

  oss117 << _graphviz_relations(graph);

  oss117 << _graphviz_footers();

  return oss117.str();
}

template<typename Type>
std::string Exporter<Type>::ToGraphviz(const Graph<Type> & graph,
				       const std::map<GraphTypes::node_id, std::string> & label_mapper,
				       const std::map<GraphTypes::node_id, NamedColor::ColorName> & color_mapper)
{
  std::ostringstream oss117;

  oss117 << _graphviz_headers(graph);

  oss117 << "node [style=filled]" << std::endl << std::endl;

  oss117 << _graphviz_relations(graph);

  oss117 << _graphviz_node_meta_mapping(graph, label_mapper, color_mapper);

  oss117 << _graphviz_footers();

  return oss117.str();
  
}

template<typename Type>
std::string Exporter<Type>::ToGraphviz(const Graph<Type> & graph,
				       const std::map<GraphTypes::node_id, std::string> & label_mapper,
				       const std::list<GraphTypes::Path> & paths_highlight)
{
  std::ostringstream oss117;

  oss117 << _graphviz_headers(graph);

  oss117 << _graphviz_paths_highlighting(graph, paths_highlight);

  oss117 << _graphviz_node_label_mapping(graph, label_mapper);

  oss117 << _graphviz_relations(graph);

  oss117 << _graphviz_footers();

  return oss117.str();
}

template<typename Type>
void Exporter<Type>::ToGraphviz(const Graph<Type> & graph, const std::string & filename)
{
  std::ofstream file;
  file.open(filename.c_str(), std::ios::out | std::ios::trunc);

  file << ToGraphviz(graph);

  file.close();
}

template<typename Type>
void Exporter<Type>::ToGraphviz(const Graph<Type> & graph,
				const std::map<GraphTypes::node_id, std::string> & label_mapper,
				const std::string & filename)
{
  std::ofstream file;
  file.open(filename.c_str(), std::ios::out | std::ios::trunc);

  file << ToGraphviz(graph, label_mapper);

  file.close();
}

template<typename Type>
void Exporter<Type>::ToGraphviz(const Graph<Type> & graph,
				const std::map<GraphTypes::node_id, NamedColor::ColorName> & color_mapper,
				const std::string & filename)
{
  std::ofstream file;
  file.open(filename.c_str(), std::ios::out | std::ios::trunc);

  file << ToGraphviz(graph, color_mapper);

  file.close();
}

template<typename Type>
void Exporter<Type>::ToGraphviz(const Graph<Type> & graph,
				const std::list<GraphTypes::Path> & paths_highlight,
				const std::string & filename)
{
  std::ofstream file;
  file.open(filename.c_str(), std::ios::out | std::ios::trunc);

  file << ToGraphviz(graph, paths_highlight);

  file.close();
}

template<typename Type>
void Exporter<Type>::ToGraphviz(const Graph<Type> & graph,
				const std::map<GraphTypes::node_id, std::string> & label_mapper,
				const std::map<GraphTypes::node_id, NamedColor::ColorName> & color_mapper,
				const std::string & filename)
{
  std::ofstream file;
  file.open(filename.c_str(), std::ios::out | std::ios::trunc);

  file << ToGraphviz(graph, label_mapper, color_mapper);

  file.close();
}

template<typename Type>
void Exporter<Type>::ToGraphviz(const Graph<Type> & graph,
				const std::map<GraphTypes::node_id, std::string> & label_mapper,
				const std::list<GraphTypes::Path> & paths_highlight,
				const std::string & filename)
{
  std::ofstream file;
  file.open(filename.c_str(), std::ios::out | std::ios::trunc);

  file << ToGraphviz(graph, label_mapper, paths_highlight);

  file.close();
}
