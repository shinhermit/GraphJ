template<typename Type>
Exporter<Type>::Exporter(GraphTypes::What what):_what(what){}

template<typename Type>
void Exporter<Type>::what(GraphTypes::What what){
  _what = what;
}

template<typename Type>
std::string Exporter<Type>::toString(Graph<Type> & graph)
{
  Traverse<Type> traverse;
  DefaultVisitor<Type> visitor(_what);

  traverse.breadth(graph, visitor);

  return visitor.nodes_representation();
}

template<typename Type>
void Exporter<Type>::toStream(Graph<Type> & graph, std::ostream & out)
{
  out << toString(graph);
}

template<typename Type>
std::string Exporter<Type>::toGraphviz(Graph<Type> & graph)
{
  Traverse<Type> traverse;
  GraphvizVisitor<Type> visitor(_what);
  std::ostringstream oss;

  if( graph.is_directed() )
    oss << "digraph G{" << std::endl;
  else
    oss << "graph G{" << std::endl;
    
  traverse.breadth(graph, visitor);

  oss << visitor.nodes_representation() << "}";

  return oss.str();
}

template<typename Type>
void Exporter<Type>::toGraphviz(Graph<Type> & graph, std::string filename)
{
  std::ofstream file;
  file.open(filename.c_str(), std::ios::out | std::ios::trunc);

  file << toGraphviz(graph);

  file.close();
}
