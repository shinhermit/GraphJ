using namespace GraphFunctor;

template<typename Type>
DefaultVisitor<Type>::DefaultVisitor(const Graph<Type> & graph, std::string & buffer):_graph(graph), _buffer(buffer){}

template<typename Type>
DefaultVisitor<Type>::~DefaultVisitor(){}

template<typename Type>
void DefaultVisitor<Type>::operator()(const GraphTypes::node_id & node)
{
  typename Graph<Type>::NodeIterator it;
  typename Graph<Type>::NodeIterator begin;
  typename Graph<Type>::NodeIterator end;
  std::ostringstream oss;
  std::string linkSymbol;

  linkSymbol = _graph.is_directed() ? " -> " : " -- ";

  oss << "n" << node << linkSymbol;

  if( _graph.is_directed() ){
    begin = _graph.successors_begin(node);
    end = _graph.successors_end(node);
  }

  else{
    begin = _graph.adjacents_begin(node);
    end = _graph.adjacents_end(node);

    _visited.insert(node);
  }

  for(it = begin; it != end; ++it){

    if( _graph.is_directed() || !_visited.count(*it) ){

      oss << "n" << *it << " ";
    }

  }

  oss << std::endl;

  _buffer += oss.str();
}
