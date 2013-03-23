
template<typename Type>
CanonicalNetwork<Type>::CanonicalNetwork(const GraphTypes::node_id & sourceNode,
					 const GraphTypes::node_id & sinkNode,
					 const GraphTypes::EdgeState & state,
					 const GraphTypes::NodeType & nodeType)
  throw (GraphException::InvalidOperation)
  :_flowGraph( Graph<Type>(GraphTypes::DIRECTED, state, nodeType) ),
   _sourceNode(sourceNode),
   _sinkNode(sinkNode)
{
  try
    {
      _flowGraph.add_node(sourceNode);

      _flowGraph.add_node(sinkNode);
    }

  catch(const GraphException::InvalidOperation & io)
    {
      throw GraphException::InvalidOperation("Container graph : you need to map nodes to a content. Consider using CanonicalNetwork<Type>::CanonicalNetwork(const GraphTypes::node_id&, const Type&, const GraphTypes::node_id&, const Type&, const GraphTypes::EdgeState&=GraphTypes::WEIGHTED, const GraphTypes::NodeType&=GraphTypes::NOCONTENT).", __LINE__, __FILE__, "CanonicalNetwork<Type>::CanonicalNetwork(const GraphTypes::node_id&, const GraphTypes::node_id&, const GraphTypes::EdgeState&=GraphTypes::WEIGHTED, const GraphTypes::NodeType&=GraphTypes::NOCONTENT)");
    }
}

template<typename Type>
CanonicalNetwork<Type>::CanonicalNetwork(const GraphTypes::EdgeState & state,
					 const GraphTypes::NodeType & nodeType)
  throw (GraphException::InvalidOperation)
  :_flowGraph( Graph<Type>(GraphTypes::DIRECTED, state, nodeType) ),
   _sourceNode(0),
   _sinkNode(1)
{
  try
    {
      _flowGraph.add_node(_sourceNode);

      _flowGraph.add_node(_sinkNode);
    }

  catch(const GraphException::InvalidOperation & io)
    {
      throw GraphException::InvalidOperation("Container graph : you need to map nodes to a content. Consider using CanonicalNetwork<Type>::CanonicalNetwork(const Type&, const Type&, const GraphTypes::EdgeState&=GraphTypes::WEIGHTED, const GraphTypes::NodeType&=GraphTypes::NOCONTENT).", __LINE__, __FILE__, "CanonicalNetwork<Type>::CanonicalNetwork(const GraphTypes::EdgeState&=GraphTypes::WEIGHTED, const GraphTypes::NodeType&=GraphTypes::NOCONTENT)");
    }
}

template<typename Type>
CanonicalNetwork<Type>::CanonicalNetwork(const GraphTypes::node_id & sourceNode,
					 const Type & sourceNodeContent,
					 const GraphTypes::node_id & sinkNode,
					 const Type & sinkNodeContent,
					 const GraphTypes::EdgeState & state,
					 const GraphTypes::NodeType & nodeType)
  :_flowGraph( Graph<Type>(GraphTypes::DIRECTED, state, nodeType) ),
   _sourceNode(sourceNode),
   _sinkNode(sinkNode)
{
  _flowGraph.add_node(sourceNode, sourceNodeContent);

  _flowGraph.add_node(sinkNode, sinkNodeContent);
}

template<typename Type>
CanonicalNetwork<Type>::CanonicalNetwork(const Type & sourceNodeContent,
					 const Type & sinkNodeContent,
					 const GraphTypes::EdgeState & state,
					 const GraphTypes::NodeType & nodeType)
  :_flowGraph( Graph<Type>(GraphTypes::DIRECTED, state, nodeType) ),
   _sourceNode(0),
   _sinkNode(1)
{
  _flowGraph.add_node(_sourceNode, sourceNodeContent);

  _flowGraph.add_node(_sinkNode, sinkNodeContent);
}

template<typename Type>
CanonicalNetwork<Type>::CanonicalNetwork(const CanonicalNetwork & source)
  :_flowGraph(source._flowGraph),
   _sourceNode(source._sourceNode),
   _sinkNode(source._sinkNode)
{}

template<typename Type>
CanonicalNetwork<Type> & CanonicalNetwork<Type>::operator=(const CanonicalNetwork & source)
{
  _flowGraph = source._flowGraph;
  _sourceNode = source._sourceNode;
  _sinkNode = source._sinkNode;

  return *this;
}

template<typename Type>
void CanonicalNetwork<Type>::setSource(const GraphTypes::node_id & sourceNode) throw(GraphException::InvalidOperation)
{
  try
    {
      _flowGraph.add_node(sourceNode);
      _sourceNode = sourceNode;
    }

  catch(const GraphException::InvalidOperation & io)
    {
      throw GraphException::InvalidOperation("Container graph : you need to map nodes to a content. Consider using CanonicalNetwork<Type>::setSource(const GraphTypes::node_id&, const Type&).", __LINE__, __FILE__, "CanonicalNetwork<Type>::setSource(const GraphTypes::node_id&)");
    }
}

template<typename Type>
void CanonicalNetwork<Type>::setSink(const GraphTypes::node_id & sinkNode) throw(GraphException::InvalidOperation)
{
  try
    {
      _flowGraph.add_node(sinkNode);
      _sinkNode = sinkNode;
    }

  catch(const GraphException::InvalidOperation & io)
    {
      throw GraphException::InvalidOperation("Container graph : you need to map nodes to a content. Consider using CanonicalNetwork<Type>::setSink(const GraphTypes::node_id&, const Type&).", __LINE__, __FILE__, "CanonicalNetwork<Type>::setSink(const GraphTypes::node_id&)");
    }
}

template<typename Type>
void CanonicalNetwork<Type>::setSource(const GraphTypes::node_id & sourceNode,
				       const Type & content)
{
  _sourceNode = sourceNode;

  _flowGraph.add_node(source, content);
}

template<typename Type>
void CanonicalNetwork<Type>::setSink(const GraphTypes::node_id & sinkNode,
				     const Type & content)
{
  _sinkNode = sinkNode;

  _flowGraph.add_node(sink, content);
}

template<typename Type>
const GraphTypes::node_id & CanonicalNetwork<Type>::source()const
{
  return _sourceNode;
}

template<typename Type>
const GraphTypes::node_id & CanonicalNetwork<Type>::sink()const
{
  return _sinkNode;
}

template<typename Type>
Graph<Type> & CanonicalNetwork<Type>::flowGraph()
{
  return _flowGraph;
}

template<typename Type>
const Graph<Type> & CanonicalNetwork<Type>::flowGraph()const
{
  return _flowGraph;
}

template<typename Type>
CanonicalNetwork<Type>::operator Graph<Type>&()
{
  return _flowGraph;
}
