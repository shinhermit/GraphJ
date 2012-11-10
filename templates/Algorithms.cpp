template<typename Type>
void Algorithms::breadth_visit(Graph<Type> & graph, Node::node_id node, Visitor<Type> & visitor, std::set<Node::node_id> & marker){
  Node::node_id son, grand_son;
  std::deque<Node::node_id> waiters, grand_successors;
  std::set<Node::node_id> nodes_set;

  waiters.push_back(node);

  while( waiters.size() > 0 ){
    son = waiters.front();
    waiters.pop_front();
    visitor.treat(graph, son);

    nodes_set = graph.successors(son);
    grand_successors.assign(nodes_set.begin(), nodes_set.end());
    nodes_set.clear();

    while( grand_successors.size() > 0 ){
      grand_son = grand_successors.front();
      if( !marker.count(grand_son) ){
	marker.insert(grand_son);
	waiters.push_back(grand_son);
      }

      grand_successors.pop_front();
    }
  }
}

template<typename Type>
void Algorithms::breadth_first_search(Graph<Type> & graph, Visitor<Type> & visitor){
  unsigned long i, size;
  Node::node_id node;
  std::set<Node::node_id> marker;

  size = graph.nodes_size();
  if(size > 0){
    node = graph.first_node();

    for(i=0; i < size; i++){
      if( !marker.count(node) )
	breadth_visit(graph, node, visitor, marker);

      node = graph.next_node();
    }
  }

}

template<typename Type>
void Algorithms::depth_visit(Graph<Type> & graph, Node::node_id node, Visitor<Type> & visitor, std::set<Node::node_id> & marker){
  Node::node_id curr_node;
  std::deque<Node::node_id> successors;
  std::set<Node::node_id> nodes_set;

  visitor.treat(graph, node);
  marker.insert(node);

  nodes_set = graph.successors(node);
  successors.assign( nodes_set.begin(), nodes_set.end() );
  nodes_set.clear();

  while( successors.size() > 0 ){
    curr_node = successors.front();

    if( !marker.count(curr_node) ){
      depth_visit(graph, curr_node, visitor, marker);
    }

    successors.pop_front();
  }
}

template<typename Type>
void Algorithms::depth_first_search(Graph<Type> & graph, Visitor<Type> & visitor){
  Node::node_id node;
  unsigned long i, size;
  std::set<Node::node_id> marker;

  size = graph.nodes_size();
  if( size > 0 ){

    node = graph.first_node();

    for(i=0; i < size; i++){
      if( !marker.count(node) )
	depth_visit(graph, node, visitor, marker);

      node = graph.next_node();
    }
  }

}

template<typename Type>
std::map<Node::node_id, unsigned long> Algorithms::color_each_node(Graph<Type> & graph){
  std::map<Node::node_id, int> colored;
  Node::node_id node;
  unsigned long nodes_size, color;

  nodes_size = graph.nodes_size();
  node = graph.first_node();
  color = 0;

  while( color < nodes_size ){

    colored.insert(node, color);

    node = graph.next_node();
    color++;
  }

  return colored;
}

template<typename Type>
std::set<WeightedEdge> Algorithms::sort_edges_by_weights(Graph<Type> & graph){
  std::set<WeightedEdge> sorted_edges;
  std::set<Node::node_id> successors;
  std::set<Node::node_id>::iterator it;
  Node::node_id node;
  GraphTypes::Cost cost;
  unsigned long i, graph_size;

  node = graph.first_node();
  graph_size = graph.nodes_size();
  i = 0;

  while(i < graph_size){

    successors = graph.successors(node);

    for(it = successors.begin(); it != successors.end(); it++){

      cost = graph.getCost(node, *it);

      if( graph.is_oriented() ){
	sorted_edges.insert( WeightedEdge(node, *it, cost) );
      }
      else{
	if( !graph.has_edge(*it, node) ){
	  sorted_edges.insert( WeightedEdge(node, *it, cost) );
	}
      }

    }
    i++;
    node = graph.next_node();
  }

  return sorted_edges;
}

template<typename Type>
Graph<Type> Algorithms::acm_kruskal(Graph<Type> & graph){
  std::map<Node::node_id, unsigned long> color_mapper;
  std::set<WeightedEdge> sorted_edges;
  std::set<WeightedEdge>::iterator it;
  Graph<Type> acm; //il faudrait récupérer les options de graph ( is_directed(), is_weighted() )
  Node::node_id node1, node2;
  Type node1_content, node2_content;
  unsigned long i, graph_size, node1_color, node2_color, acm_color;
  GraphTypes::Cost cost;

  color_mapper = color_each_node<Type>(graph);

  sorted_edges = sort_edges_by_weights<Type>(graph);

  graph_size = graph.nodes_size();
  acm_color = color_mapper.size() + 1;
  it = sorted_edges.begin();

  while( it != sorted_edges.end() && acm.nodes_size() < graph_size ){
    node1 = it->source();
    node1_content = graph.getContent(node1);

    node2 = it->target();
    node2_content = graph.getContent(node2);

    cost = it->cost();

    node1_color = color_mapper[node1];
    node2_color = color_mapper[node2];

    if( node1_color != node2_color ){
      color_mapper[node1] = acm_color;
      color_mapper[node2] = acm_color;

      acm.add_edge( node1, node1_content, node2, node2_content, cost );
    }

    it++;
  }

  return acm;
}

template<typename Type>
std::set<WeightedEdge> Algorithms::weightedNeighboursFromSuccessors(Graph<Type> graph, Node::node_id node){
  std::set<WeightedEdge> weightedNeighbours;
  std::set<Node::node_id> successors;
  std::set<Node::node_id>::iterator it ;

  successors = graph.successors(node);

  for(it = successors.begin(); it != successors.end(); it++){    
    weightedNeighbours.insert( WeightedEdge( node, *it, graph.getCost(node, *it) ) );
  }

  return weightedNeighbours;
}

template<typename Type>
Graph<Type> Algorithms::acm_prim(Graph<Type> & graph){
  std::set<WeightedEdge> fusion, newNeighbours;
  Graph<Type> alterableCopy;
  Graph<Type> acm;
  WeightedEdge min_edge;
  Node::node_id first_node, source_node, target_node;
  Type content;
  GraphTypes::Cost cost;

  alterableCopy = graph;

  first_node = alterableCopy.first_node();
  acm.add_node( first_node, alterableCopy.getContent(first_node) );

  fusion = weightedNeighboursFromSuccessors(alterableCopy, first_node);
  
  alterableCopy.remove_node(first_node);

  while( alterableCopy.size() > 0 ){
    min_edge = *fusion.begin();

    source_node = min_edge.source();
    target_node = min_edge.target();
    cost = min_edge.cost();
    content = alterableCopy.getContent(target_node);

    acm.add_node(target_node, content);
    acm.add_edge(source_node, target_node, cost);

    fusion.erase( fusion.begin() );

    newNeighbours = weightedNeighboursFromSuccessors(alterableCopy, target_node);

    fusion.insert( newNeighbours.begin(), newNeighbours.end() );

    alterableCopy.remove_node(target_node);
  }

  return acm;
}

template<typename Type>
std::set<WeightedNode> Algorithms::sort_nodes_by_degrees(Graph<Type> & graph){
  std::set<WeightedNode> sorted_nodes;
  Node::node_id node;
  unsigned long i, nodes_size;

  node = graph.first_node();
  nodes_size = graph.nodes_size();
  i = 0;

  while(i < nodes_size)
    {
      sorted_nodes.insert( WeightedNode(node, graph.degree(node)) );

      node = graph.next_node();
      i++;
    }

  return sorted_nodes;
}

template<typename Type>
bool Algorithms::partite_compatible(Graph<Type> graph, Node::node_id node, std::set<Node::node_id> partite){
  std::set<Node::node_id>::iterator it;
  bool compatible;

  compatible = true;
  it = partite.begin();
  while( it != partite.end() && compatible )
    {
      if( graph.has_edge(node, *it) )
	compatible = false;

      it++;
    }

  return compatible;
}

template<typename Type>
std::map<Node::node_id, NamedColor::ColorName> Algorithms::welsh_coloring(Graph<Type> graph){
  std::set<WeightedNode> sorted_nodes;
  std::set<WeightedNode>::iterator it_sn;
  std::set<NamedColor::ColorName> allColors;
  std::set<NamedColor::ColorName>::iterator it_color;
  std::map<NamedColor::ColorName, std::set<Node::node_id> > partites_list; //liste des stables
  std::map<Node::node_id, NamedColor::ColorName> color_mapper;
  Node::node_id node, current_node;

  sorted_nodes = sort_nodes_by_degrees<Type>(graph);
  allColors = NamedColor::allNames();
  it_color = allColors.begin();

  while( sorted_nodes.size() > 0 ) //should check for color lack
    {
      node = sorted_nodes.rbegin()->id();

      color_mapper.insert( std::pair<Node::node_id, NamedColor::ColorName>(node, *it_color) );
      partites_list.insert( std::pair<NamedColor::ColorName, std::set<Node::node_id> >( *it_color, std::set<Node::node_id>() ) );
      partites_list[*it_color].insert(node);

      sorted_nodes.erase( --sorted_nodes.end() ); //same as --rbegin().base()

      for( it_sn = sorted_nodes.begin(); it_sn != sorted_nodes.end(); it_sn++ )
	{
	  current_node = it_sn->id();

	  if( partite_compatible<Type>(graph, current_node, partites_list[*it_color]) )
	    {
	      color_mapper.insert( std::pair<Node::node_id, NamedColor::ColorName>(current_node, *it_color) );
	      partites_list[*it_color].insert(current_node);
	      sorted_nodes.erase(it_sn++);
	    }

	}

      it_color++;
    }

  return color_mapper;
}
