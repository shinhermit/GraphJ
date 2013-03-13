
template<typename Type>
CanonicalNetwork<Type>::CanonicalNetwork(const GraphTypes::node_id & sourceNode,
					 const GraphTypes::node_id & sinkNode,
					 const GraphTypes::EdgeState & state,
					 const GraphTypes::NodeType & nodeType)
  :_flowGraph( Graph<Type>(GraphTypes::DIRECTED, state, nodeType) ),
   _sourceNode(sourceNode),
   _sinkNode(sinkNode)
{}

template<typename Type>
CanonicalNetwork<Type>::CanonicalNetwork(const GraphTypes::EdgeState & state,
					 const GraphTypes::NodeType & nodeType)
  :_flowGraph( Graph<Type>(GraphTypes::DIRECTED, state, nodeType) ),
   _sourceNode(0),
   _sinkNode(1)
{}

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
void CanonicalNetwork<Type>::setSource(const GraphTypes::node_id & sourceNode)
{
  _sourceNode = sourceNode;
}

template<typename Type>
void CanonicalNetwork<Type>::setSink(const GraphTypes::node_id & sinkNode)
{
  _sinkNode = sinkNode;
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
