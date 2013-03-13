
template <typename Type>
Graph<Type>::Graph(const GraphTypes::EdgeType & edgeType,
		   const GraphTypes::EdgeState & state,
		   const GraphTypes::NodeType & nodeType):
  PonderableGraph::PonderableGraph(edgeType, state),
  _nodeType(nodeType)
{}

template <typename Type>
Graph<Type>::Graph(const Graph<Type> & source):
  PonderableGraph::PonderableGraph(source),
  _nodeType(source._nodeType),
  _contents(source._contents)
{}

template <typename Type>
Graph<Type> & Graph<Type>::operator=(const Graph<Type> & source)
{

  PonderableGraph::operator=(source);

  _nodeType = source._nodeType;
  _contents = source._contents;
  return *this;
}

template <typename Type>
bool Graph<Type>::is_container()const
{
  return (_nodeType == GraphTypes::CONTAINER);
}

template <typename Type>
void Graph<Type>::add_node(const GraphTypes::node_id &  node, const Type & content)
{

  PonderableGraph::add_node(node);

  if(_nodeType == GraphTypes::CONTAINER)
    {
      _contents.insert( std::pair<GraphTypes::node_id, Type>(node, content) );
    }
}

template <typename Type>
void Graph<Type>::add_node(const GraphTypes::node_id & node)
  throw(GraphException::InvalidOperation)
{

  if(_nodeType == GraphTypes::CONTAINER)
    {
      throw GraphException::InvalidOperation("Container graph : you need to map nodes to a content. Consider using Graph<Type>::add_node(const GraphTypes::node_id&, const Type&).", __LINE__, __FILE__, "Graph<Type>::add_node(const GraphTypes::node_id&)");
    }

  else
    {
      PonderableGraph::add_node(node);
    }
}

template <typename Type>
void Graph<Type>::remove_node(const GraphTypes::node_id & node)
{

  PonderableGraph::remove_node(node);

  if(_nodeType == GraphTypes::CONTAINER)
    {
      _contents.erase(node);
    }
}

template <typename Type>
void Graph<Type>::add_edge(const GraphTypes::node_id & src_node,
			   const Type & content1,
			   const GraphTypes::node_id & target_node,
			   const Type & content2,
			   const GraphTypes::Cost & cost)
{

  PonderableGraph::add_edge(src_node, target_node, cost);

  if(_nodeType == GraphTypes::CONTAINER)
    {
      _contents.insert( std::pair<GraphTypes::node_id, Type>(src_node, content1) );
      _contents.insert( std::pair<GraphTypes::node_id, Type>(target_node, content2) );
    }

}

template <typename Type>
void Graph<Type>::add_edge(const GraphTypes::node_id & existing_src,
			   const GraphTypes::node_id & existing_target,
			   const GraphTypes::Cost & cost
			   ) throw(GraphException::InvalidOperation){

  if( _nodeType == GraphTypes::CONTAINER && ( !has_node(existing_src) || !has_node(existing_target) ) )
    {
      throw GraphException::InvalidOperation("Given node IDs must already be in the Graph.\n Consider using:\n Graph<Type>::add_edge(const GraphTypes::node_id&, const Type&, const GraphTypes::node_id&, const Type&, const GraphTypes::Cost&).", __LINE__, __FILE__, "Graph<Type>::add_edge(const GraphTypes::node_id&, const GraphTypes::node_id&, const GraphTypes::Cost&)");
    }

  else
    {
      PonderableGraph::add_edge(existing_src, existing_target, cost);
    }
}

template <typename Type>
GraphTypes::NodeType Graph<Type>::nodeType()const
{
  return _nodeType;
}

template <typename Type>
void Graph<Type>::set_node_content(const GraphTypes::node_id & node,
				   const Type & content
				   ) throw(GraphException::InvalidNodeID, GraphException::InvalidOperation)
{

  if( has_node(node) )
    {
      if(_nodeType == GraphTypes::CONTAINER)
	{
	  _contents[node] = content;
	}

      else
	{
	  throw GraphException::InvalidOperation("attempt to add content in non container graph", __LINE__, __FILE__, "Graph<Type>::set_node_content(const GraphTypes::node_id&, const Type&)");
	}
    }

  else
    {
      throw GraphException::InvalidNodeID(node, "Invalid node ID.", __LINE__, __FILE__, "Graph<Type>::set_node_content(const GraphTypes::node_id&, const Type&)");
    }
}

template <typename Type>
Type & Graph<Type>::get_node_content(const GraphTypes::node_id & node)
  throw(GraphException::InvalidNodeID, GraphException::InvalidOperation)
{
  typename std::map<GraphTypes::node_id, Type>::iterator it;

  if( has_node(node) )
    {

      if(_nodeType == GraphTypes::CONTAINER)
	{
	  it = _contents.find(node);

	  assert( it != _contents.end() );

	  return it->second;
	}

      else
	{
	  throw GraphException::InvalidOperation("Attempt to access content in a non-container graph", __LINE__, __FILE__, "Graph<Type>::get_node_content(const GraphTypes::node_id&)const");
	}

    }

  else
    {
      throw GraphException::InvalidNodeID(node, "Invalid Node ID.", __LINE__, __FILE__, "Graph<Type>::get_node_content(const GraphTypes::node_id&)const");
    }

}

template <typename Type>
const Type & Graph<Type>::get_node_content(const GraphTypes::node_id & node)const
  throw(GraphException::InvalidNodeID, GraphException::InvalidOperation)
{
  Graph<Type> * _this = const_cast<Graph<Type>*>(this);

  return _this->get_node_content(node);
}
