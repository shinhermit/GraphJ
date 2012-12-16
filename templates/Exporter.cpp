template<typename Type>
std::string Exporter<Type>::_graphviz_headers(Graph<Type> & graph)
{
  std::ostringstream oss;

  if( graph.is_directed() )
    oss << "strict digraph G{" << std::endl;
  else
    oss << "strict graph G{" << std::endl;

  return oss.str();
}

template<typename Type>
std::string Exporter<Type>::_graphviz_relations(Graph<Type> & graph)
{
  Traverse<Type> traverse;
  GraphvizVisitor<Type> visitor;
    
  traverse.nodes(graph, visitor);

  return visitor.nodes_representation();
}

template<typename Type>
std::string Exporter<Type>::_graphviz_node_label_mapping(Graph<Type> & graph, std::map<GraphTypes::node_id, std::string> & label_mapper)
{
  typename Graph<Type>::NodeIterator node;
  std::map<GraphTypes::node_id, std::string>::iterator label_it;
  std::ostringstream oss;

  node = graph.nodes_begin();
  while( node != graph.nodes_end() ){

    label_it = label_mapper.find(*node);
    if( label_it != label_mapper.end() ){
      oss << *node <<" [label=\"" << label_it->second << "\"]" << std::endl;
    }

    node++;
  }

  return oss.str();
}

template<typename Type>
std::string Exporter<Type>::_graphviz_node_color_mapping(Graph<Type> & graph, std::map<GraphTypes::node_id, NamedColor::ColorName> & color_mapper)
{
  typename Graph<Type>::NodeIterator node;
  std::map<GraphTypes::node_id, NamedColor::ColorName>::iterator color_it;
  std::ostringstream oss;

  node = graph.nodes_begin();
  while( node != graph.nodes_end() ){

    color_it = color_mapper.find(*node);
    if( color_it != color_mapper.end() ){
      oss << *node <<" [color=" << NamedColor::ToString(color_it->second) << "]" << std::endl;
    }

    node++;
  }

  return oss.str();
}

template<typename Type>
std::string Exporter<Type>::_graphviz_paths_highlighting(Graph<Type> & graph, std::list<GraphTypes::Path> & paths_highlight)
{
  std::set<NamedColor::ColorName> colors;
  std::set<NamedColor::ColorName>::iterator col;
  std::list<GraphTypes::Path>::iterator path;
  std::list<GraphTypes::node_id>::iterator node;
  GraphTypes::node_id sourceNode;
  std::ostringstream oss;

  colors = NamedColor::AllNames();
  col = colors.begin();
  for(path = paths_highlight.begin(); path != paths_highlight.end(); path++){

    oss << "{" << std::endl << "node [color=" << NamedColor::ToString(*col)<< ", style=\"filled\"]" << std::endl;
    oss << "edge [color=" << NamedColor::ToString(*col)<< "]" << std::endl;

    node = path->begin();
    while( node!= path->end() ){
      sourceNode = *node;
      node++;

      if( node != path->end() ){
	oss << sourceNode << "->" << *node;

	if( graph.is_weighted() ){
	  oss << "[label=\"" << graph.getCost(sourceNode, *node) << "\", fontcolor=" << NamedColor::ToString(*col)<< "]";
	}

	oss << std::endl;
      }
    }

    oss << "}" << std::endl;

    col++; if(col == colors.end()) col=colors.begin();
  }

  return oss.str();
}

template<typename Type>
std::string Exporter<Type>::_graphviz_node_meta_mapping(Graph<Type> & graph, std::map<GraphTypes::node_id, std::string> & label_mapper, std::map<GraphTypes::node_id, NamedColor::ColorName> & color_mapper)
{
  std::ostringstream oss;
  std::string stringColor;
  typename Graph<Type>::NodeIterator nodeIt;

  nodeIt = graph.nodes_begin();
  while( nodeIt != graph.nodes_end() ){
    stringColor = NamedColor::ToString(color_mapper[*nodeIt]);

    oss << *nodeIt <<" [label=\"" << label_mapper[*nodeIt] << "\", color=" << stringColor << "]" << std::endl;

    nodeIt++;
  }

  return oss.str();
}

template<typename Type>
std::string Exporter<Type>::_graphviz_footers()
{
  return "}";
}

template<typename Type>
std::string Exporter<Type>::toString(Graph<Type> & graph)
{
  Traverse<Type> traverse;
  DefaultVisitor<Type> visitor;

  traverse.nodes(graph, visitor);

  return visitor.nodes_representation();
}

template<typename Type>
std::string Exporter<Type>::toMathString(Graph<Type> & graph)
{
  Traverse<Type> traverse;
  MathVisitor<Type> visitor;

  traverse.nodes(graph, visitor);

  return visitor.math_representation();
}

template<typename Type>
std::string Exporter<Type>::toMathString(Graph<Type> & graph, std::map<GraphTypes::node_id, std::string> & label_mapper)
{
  std::map<GraphTypes::node_id, std::string>::iterator it;
  std::ostringstream oss;

  for(it = label_mapper.begin(); it != label_mapper.end(); it++){
    oss << "s" << it->first << " |--> " << it->second << std::endl;
  }
  oss << toMathString(graph);

  return oss.str();
}

template<typename Type>
void Exporter<Type>::toStream(Graph<Type> & graph, std::ostream & out)
{
  out << toString(graph) << std::endl;
}

template<typename Type>
std::string Exporter<Type>::toGraphviz(Graph<Type> & graph)
{
  std::ostringstream oss;
  oss << _graphviz_headers(graph);
  oss << _graphviz_relations(graph);
  oss << _graphviz_footers();

  return oss.str();
}

template<typename Type>
std::string Exporter<Type>::toGraphviz(Graph<Type> & graph, std::map<GraphTypes::node_id, std::string> & label_mapper)
{
  std::ostringstream oss117;

  oss117 << _graphviz_headers(graph);

  oss117 << _graphviz_relations(graph);

  oss117 << _graphviz_node_label_mapping(graph, label_mapper);

  oss117 << _graphviz_footers();

  return oss117.str();
  
}

template<typename Type>
std::string Exporter<Type>::toGraphviz(Graph<Type> & graph, std::map<GraphTypes::node_id, NamedColor::ColorName> & color_mapper)
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
std::string Exporter<Type>::toGraphviz(Graph<Type> & graph, std::list<GraphTypes::Path> & paths_highlight)
{
  std::ostringstream oss117;

  oss117 << _graphviz_headers(graph);

  oss117 << _graphviz_paths_highlighting(graph, paths_highlight);

  oss117 << _graphviz_relations(graph);

  oss117 << _graphviz_footers();

  return oss117.str();
}

template<typename Type>
std::string Exporter<Type>::toGraphviz(Graph<Type> & graph, std::map<GraphTypes::node_id, std::string> & label_mapper, std::map<GraphTypes::node_id, NamedColor::ColorName> & color_mapper)
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
std::string Exporter<Type>::toGraphviz(Graph<Type> & graph, std::map<GraphTypes::node_id, std::string> & label_mapper, std::list<GraphTypes::Path> & paths_highlight)
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
void Exporter<Type>::toGraphviz(Graph<Type> & graph, std::string filename)
{
  std::ofstream file;
  file.open(filename.c_str(), std::ios::out | std::ios::trunc);

  file << toGraphviz(graph);

  file.close();
}

template<typename Type>
void Exporter<Type>::toGraphviz(Graph<Type> & graph, std::map<GraphTypes::node_id, std::string> & label_mapper, std::string filename)
{
  std::ofstream file;
  file.open(filename.c_str(), std::ios::out | std::ios::trunc);

  file << toGraphviz(graph, label_mapper);

  file.close();
}

template<typename Type>
void Exporter<Type>::toGraphviz(Graph<Type> & graph, std::map<GraphTypes::node_id, NamedColor::ColorName> & color_mapper, std::string filename)
{
  std::ofstream file;
  file.open(filename.c_str(), std::ios::out | std::ios::trunc);

  file << toGraphviz(graph, color_mapper);

  file.close();
}

template<typename Type>
void Exporter<Type>::toGraphviz(Graph<Type> & graph, std::list<GraphTypes::Path> & paths_highlight, std::string filename)
{
  std::ofstream file;
  file.open(filename.c_str(), std::ios::out | std::ios::trunc);

  file << toGraphviz(graph, paths_highlight);

  file.close();
}

template<typename Type>
void Exporter<Type>::toGraphviz(Graph<Type> & graph, std::map<GraphTypes::node_id, std::string> & label_mapper, std::map<GraphTypes::node_id, NamedColor::ColorName> & color_mapper, std::string filename)
{
  std::ofstream file;
  file.open(filename.c_str(), std::ios::out | std::ios::trunc);

  file << toGraphviz(graph, label_mapper, color_mapper);

  file.close();
}

template<typename Type>
void Exporter<Type>::toGraphviz(Graph<Type> & graph, std::map<GraphTypes::node_id, std::string> & label_mapper, std::list<GraphTypes::Path> & paths_highlight, std::string filename)
{
  std::ofstream file;
  file.open(filename.c_str(), std::ios::out | std::ios::trunc);

  file << toGraphviz(graph, label_mapper, paths_highlight);

  file.close();
}
