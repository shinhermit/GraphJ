template<typename Type>
std::string Exporter<Type>::_graphviz_headers(Graph<Type> & graph)
{
  std::ostringstream oss;

  if( graph.is_directed() )
    oss << "digraph G{" << std::endl;
  else
    oss << "graph G{" << std::endl;

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
std::string Exporter<Type>::_graphviz_color_mapping(Graph<Type> & graph, std::map<Node::node_id, NamedColor::ColorName> & color_mapper)
{
  std::ostringstream oss;
  Node::node_id node;
  std::string stringColor;

  node = graph.first_node();
  while( !graph.at_nodes_end() ){
    stringColor = NamedColor::ToString(color_mapper[node]);
    oss << node <<" [color=" << stringColor << "]" << std::endl;

    node = graph.next_node();
  }

  return oss.str();
}

template<typename Type>
std::string Exporter<Type>::_graphviz_label_mapping(Graph<Type> & graph, std::map<Node::node_id, std::string> & label_mapper)
{
  std::ostringstream oss;
  Node::node_id node;

  node = graph.first_node();
  while( !graph.at_nodes_end() ){
    oss << node <<" [label=\"" << label_mapper[node] << "\"]" << std::endl;

    node = graph.next_node();
  }

  return oss.str();
}

template<typename Type>
std::string Exporter<Type>::_graphviz_meta_mapping(Graph<Type> & graph, std::map<Node::node_id, std::string> & label_mapper, std::map<Node::node_id, NamedColor::ColorName> & color_mapper)
{
  std::ostringstream oss;
  Node::node_id node;
  std::string stringColor;

  node = graph.first_node();
  while( !graph.at_nodes_end() ){
    stringColor = NamedColor::ToString(color_mapper[node]);

    oss << node <<" [label=\"" << label_mapper[node] << "\", color=" << stringColor << "]" << std::endl;

    node = graph.next_node();
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
std::string Exporter<Type>::toGraphviz(Graph<Type> & graph, std::map<Node::node_id, std::string> & label_mapper)
{
  std::ostringstream oss117;

  oss117 << _graphviz_headers(graph);

  oss117 << _graphviz_relations(graph);

  oss117 << _graphviz_label_mapping(graph, label_mapper);

  oss117 << _graphviz_footers();

  return oss117.str();
  
}

template<typename Type>
std::string Exporter<Type>::toGraphviz(Graph<Type> & graph, std::map<Node::node_id, NamedColor::ColorName> & color_mapper)
{
  std::ostringstream oss117;

  oss117 << _graphviz_headers(graph);

  oss117 << "node [style=filled]" << std::endl << std::endl;

  oss117 << _graphviz_relations(graph);

  oss117 << _graphviz_color_mapping(graph, color_mapper);

  oss117 << _graphviz_footers();

  return oss117.str();
  
}

template<typename Type>
std::string Exporter<Type>::toGraphviz(Graph<Type> & graph, std::map<Node::node_id, std::string> & label_mapper, std::map<Node::node_id, NamedColor::ColorName> & color_mapper)
{
  std::ostringstream oss117;

  oss117 << _graphviz_headers(graph);

  oss117 << "node [style=filled]" << std::endl << std::endl;

  oss117 << _graphviz_relations(graph);

  oss117 << _graphviz_meta_mapping(graph, label_mapper, color_mapper);

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
void Exporter<Type>::toGraphviz(Graph<Type> & graph, std::map<Node::node_id, std::string> & label_mapper, std::string filename)
{
  std::ofstream file;
  file.open(filename.c_str(), std::ios::out | std::ios::trunc);

  file << toGraphviz(graph, label_mapper);

  file.close();
}

template<typename Type>
void Exporter<Type>::toGraphviz(Graph<Type> & graph, std::map<Node::node_id, NamedColor::ColorName> & color_mapper, std::string filename)
{
  std::ofstream file;
  file.open(filename.c_str(), std::ios::out | std::ios::trunc);

  file << toGraphviz(graph, color_mapper);

  file.close();
}

template<typename Type>
void Exporter<Type>::toGraphviz(Graph<Type> & graph, std::map<Node::node_id, std::string> & label_mapper, std::map<Node::node_id, NamedColor::ColorName> & color_mapper, std::string filename)
{
  std::ofstream file;
  file.open(filename.c_str(), std::ios::out | std::ios::trunc);

  file << toGraphviz(graph, label_mapper, color_mapper);

  file.close();
}
