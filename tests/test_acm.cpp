#include <iostream>
#include <cstdlib>
#include "Graph.hpp"
#include "Acm.hpp"
#include "Exporter.hpp"

int main()
{
  Graph<> graph(GraphTypes::UNDIRECTED, GraphTypes::WEIGHTED, GraphTypes::NOCONTENT);
  Graph<> min_tree( graph.edgeType(), graph.edgeState(), GraphTypes::NOCONTENT );

  typedef Acm<> Acm;
  typedef Exporter<> Export;

  /*
    Graphe de l'annale: contrôle continu Novembre 2008
    C2 vers C1, C7 vers C1, C8 vers C1, C6 vers C2, C2 vers C3, C4 vers C3, C5 vers C4, C3 vers C5, C1 vers C6, C6 vers C7 et C7 vers C8

    coût(s2,s1)=1, coût(s7,s1)=0, coût(s8,s1)=3, coût(s6,s2)=9, coût(s2,s3)=4, coût(s4,s3)=5, coût(s5,s4)=7,coût(s3,s5)=6, coût(s1,s6) = 2, coût(s6,s7)=10, coût(s7,s8) = 11
  */
  graph.add_edge(2,1, 1);
  graph.add_edge(7,1, 0);
  graph.add_edge(8,1, 3);
  graph.add_edge(6,2, 9);
  graph.add_edge(2,3, 4);
  graph.add_edge(4,3, 5);
  graph.add_edge(5,4, 7);
  graph.add_edge(3,5, 6);
  graph.add_edge(1,6, 2);
  graph.add_edge(6,7, 10);
  graph.add_edge(7,8, 11);

  try
    {
      std::cout << Export::ToMathString(graph) << std::endl << std::endl;
      std::cout << Export::ToGraphviz(graph) << std::endl << std::endl;
      std::cout << "Coût: " << graph.cost() << std::endl << std::endl;

      Export::ToGraphviz(graph, "graph_res_route.graph");
      std::cout << "Le graph a été exporté dans le fichier graph_res_route.graph" << std::endl << std::endl;

      min_tree = Acm::Prim(graph);
      std::cout << "Prim:" << std::endl;
      std::cout << Export::ToGraphviz(min_tree) << std::endl;
      std::cout << "Coût: " << min_tree.cost() << std::endl << std::endl;

      Export::ToGraphviz(min_tree, "acm_prim.graph");
      std::cout << "L'arbre couvrant a été exporté dans le fichier acm_prim.graph" << std::endl << std::endl;

      min_tree = Acm::Kruskal(graph);
      std::cout << "Kruskal:" << std::endl;
      std::cout << Export::ToGraphviz(min_tree) << std::endl;
      std::cout << "Coût: " << min_tree.cost() << std::endl << std::endl;

      Export::ToGraphviz(min_tree, "acm_kruskal.graph");
      std::cout << "L'arbre couvrant a été exporté dans le fichier acm_kruskal.graph" << std::endl << std::endl;

#ifdef _SYSTEM

      system("dot -Tpng graph_res_route.graph -o graph_res_route.png");
      system("dot -Tpng acm_kruskal.graph -o acm_kruskal.png");
      system("dot -Tpng acm_prim.graph -o acm_prim.png");

#endif

    }

  catch(const GraphException::InvalidEdge & ie)
    {
      std::cout << "Caught GraphException::InvalidEdge: " << std::endl << ie.what() << std::endl;
    }

  catch(const GraphException::InvalidOperation & io)
    {
      std::cout << "Caught GraphException::InvalidOperation: " << std::endl << io.what() << std::endl;
    }

  catch(const GraphException::InvalidNodeID & in)
    {
      std::cout << "Caught GraphException::InvalidNodeID: " << std::endl << in.what() << std::endl;
    }

  catch(const GraphException::BasicGraphException & be)
    {
      std::cout << "Caught GraphException::BasicGraphException: " << std::endl << be.what() << std::endl;
    }

  catch(...)
    {
      std::cout << "Caught unexpected exception." << std::endl;
    }

  return 0;
}
