#include <string>
#include <cstdlib>

#include "Graph.hpp"
#include "Algorithms.hpp"
#include "GraphvizVisitor.hpp"

int main(){
  Graph<std::string> graph(GraphTypes::DIRECTED, GraphTypes::UNWEIGHTED);
  std::string nom, choix;
  Node::node_id id, id2;

  std::cout << std::endl << "------ Simulation de la relation \"fourni\" (ou \"vend à\") entre des entreprises ------" << std::endl << "Saisie du graphe: Entrez le nom d'une entreprise et son identifiant unique:" << std::endl;

  choix = "y";
  while(choix != "n" && choix != "N"){
    std::cout << "nom? identifiant(numéro)?";
    std::cin >> nom >> id;

    graph.add_node(id, nom);

    std::cout << "Ajouter une autre entreprise? y/n ";
    std::cin >> choix;
  }

  std::cout << std::endl << "Définition des relations." << std::endl << "Entrez les couples d'identifiants des entreprises (entr1 \"fourni\" entr2)" << std::endl;

  choix = "y";
  while(choix != "n" && choix != "N"){
    std::cout << "id_fournisseur? id_client? ";
    std::cin >> id >> id2;

    graph.add_edge(id, id2);

    std::cout << "Ajouter une autre relation? y/n ";
    std::cin >> choix;
  }
  
  std::cout << "Génération du script de config par id..."<<std::endl;
  std::string file_name = "test";
  {
    GraphvizDisplay<std::string> graphvizInterface(graph.is_directed());
    Algorithms::breadth_first_search<std::string>(graph, graphvizInterface);
    graphvizInterface.generate_file(file_name + "id.dot");
  }
  std::system("dot -Tjpg -otestid.jpg testid.dot");
  std::cout << "Graphe généré avec succès: " << file_name << "id.jpg" << std::endl;
  
  std::cout << "Génération du script de config par contenu..."<<std::endl;
  {
    GraphvizDisplay<std::string> graphvizInterface(GraphvizDisplay<std::string>::CONTENTS);
    graphvizInterface.generate_file(file_name + "content.dot");
    Algorithms::breadth_first_search<std::string>(graph, graphvizInterface);
  }
  std::system("dot -Tjpg -otestcontent.jpg testcontent.dot");
  std::cout << "Graphe généré avec succès: " << file_name << "content.jpg" << std::endl;
  
  return 0;
}
