#include "Graph.hpp"
#include "Color.hpp"

int main(){
  //Graph<Type> graph(DirectableGraph::DIRECTED, PonderableGraph::WEIGHTED);
  //Graph<Type> graph(DirectableGraph::UNDIRECTED, PonderableGraph::UNWEIGHTED);

  Graph<Color> graph; //non orienté valué par défaut

  //Affichage
  Printer<Color> printer;
  Algorithms::breadth_first_search<Color>(graph, printer);

  graph.is_empty();
  graph.add_node(id);
  graph.remove_node(id);
  graph.add_edge(id1, id2);
  graph.remove_edge(id1, id2);

  graph.is_empty();
  graph.has_node(id);
  graph.has_edge(id1, id2);

  //observateurs
  size = graph.size();
  succs = graph.successors(node);
  preds = graph.predecessors(node);
  adjacents = graph.adjacents(node);

  nodeId = graph.first_node();
  nodeId = graph.next_node();
  nodeId = graph.previous_node();
  nodeId = graph.last_node();

  degPos = graph.internally(node);
  degNeg = graph.externally(node);
  deg = graph.degree(node);

  graph.setCost(node1, node2, cost);
  cost = graph.getCost(node1, node2);


  return 0;
}
