#include <string>
#include "Graph.hpp"
#include "Exporter.hpp"

int main()
{
  Graph<std::string> graph(GraphTypes::DIRECTED, GraphTypes::UNWEIGHTED, GraphTypes::CONTAINER);
  std::string nom, choix;
  GraphTypes::node_id id, id2;

  typedef Exporter<std::string> Export;

  std::cout << std::endl << "------ Simulation de la relation \"fourni\" (ou \"vend à\") entre des entreprises ------" << std::endl << "Saisie du graphe: Entrez le nom d'une entreprise et son identifiant unique:" << std::endl;

  choix = "y";
  while(choix != "n" && choix != "N"){
    std::cout << "nom? identifiant(numéro)?";
    std::cin >> nom >> id;

    graph.add_node(id, nom);

    std::cout << "Ajouter une autre entreprise? y/n ";
    std::cin >> choix;
  }

  std::cout << std::endl  << "Définition des relations." << std::endl << "Entrez les couples d'identifiants des entreprises (entr1 \"fourni\" entr2)" << std::endl;

  choix = "y";
  while(choix != "n" && choix != "N"){
    std::cout << "id_fournisseur? id_client? ";
    std::cin >> id >> id2;

    graph.add_edge(id, id2);

    std::cout << "Ajouter une autre relation? y/n ";
    std::cin >> choix;
  }

  std::cout << std::endl  << "Affichage du graphe:"<<std::endl;

  std::cout << "Affichage:"<<std::endl;
  Export::ToStream(graph, std::cout);

  return 0;
}
