using namespace GraphFunctor;

template<typename Type>
MathVisitor<Type>::MathVisitor(const Graph<Type> & graph, std::string & S_buffer, std::string & A_buffer, std::string & C_buffer):_graph(graph), _S_buffer(S_buffer), _A_buffer(A_buffer), _C_buffer(C_buffer){}

template<typename Type>
MathVisitor<Type>::~MathVisitor(){}

template<typename Type>
void MathVisitor<Type>::operator()(const GraphTypes::node_id & node)
{
  typename Graph<Type>::NodeIterator begin;
  typename Graph<Type>::NodeIterator end;
  typename Graph<Type>::NodeIterator it;
  std::ostringstream oss1;
  std::ostringstream oss2;
  std::ostringstream oss3;

  //Set S of vertices
  if( _S_buffer.size() > 0 )
    oss1 << ", ";

  oss1 << node;

  _S_buffer += oss1.str();

  //Sets A of edges, and C of weights
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

  for(it = begin; it != end; ++it)
    {

      if( _graph.is_directed() || ( !_visited.count(*it) ) )
	{

	  oss2 << "(";

	  oss2 << node << ", " << *it;
 
	  oss2 << "), ";

	  if( _graph.is_weighted() )
	    {
	      oss3 << "coût(";
	      oss3 << node << ", " << *it;
	      oss3 << ")=" << _graph.getCost(node, *it) << "; ";
	    }

	}
    }

  _A_buffer += oss2.str();
  _C_buffer += oss3.str();
}
