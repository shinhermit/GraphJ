using namespace GraphFunctor;

template<typename Type>
GraphvizVisitor<Type>::GraphvizVisitor(const Graph<Type> & graph,
				       std::string & buffer):
  _graph(graph),
  _buffer(buffer)
{}

template<typename Type>
GraphvizVisitor<Type>::~GraphvizVisitor(){}

template<typename Type>
void GraphvizVisitor<Type>::operator()(const GraphTypes::node_id & node)
{
  typename Graph<Type>::NodeIterator begin;
  typename Graph<Type>::NodeIterator end;
  typename Graph<Type>::NodeIterator it;
  std::ostringstream oss;
  std::string linkSymbol;

  if( _graph.is_directed() )
    {
      begin = _graph.successors_begin(node);
      end = _graph.successors_end(node);
    }

  else
    {
      begin = _graph.adjacents_begin(node);
      end = _graph.adjacents_end(node);

      _visited.insert(node);
    }

  linkSymbol = ( _graph.is_directed() ) ? " -> " : " -- " ;
    
  for(it = begin; it != end; ++it)
    {

      if( _graph.is_directed() || ( !_visited.count(*it) ) )
	{
	  oss << node << linkSymbol << *it;

	  if( _graph.is_weighted() )
	    oss << " [label=\"" << _graph.getCost(node, *it) << "\"]";

	  oss << std::endl;
	}

    }

  _buffer += oss.str();
}
