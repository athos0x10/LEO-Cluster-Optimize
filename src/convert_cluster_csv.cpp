#include "convert_cluster_csv.hpp"
#include <fstream>
#include <iostream>

void clusterToCsv(std::string nomFichier, std::vector<Cluster> clusters) {
    // Création du flux de sortie pour le fichier
    std::ofstream fichier(nomFichier);

    // Vérification si le fichier est bien ouvert
    if (!fichier.is_open()) {
        std::cerr << "Erreur : Impossible de créer ou d'ouvrir le fichier " << nomFichier << std::endl;
        return;
    }

    // Écriture de l'en-tête (Header) du CSV
    fichier << "id,capacite_cluster,center_lon,center_lat,current_load,sum_pir,sum_cir,users_id\n";

    // Parcours de la liste des clusters
    for (const auto& clus : clusters) {
        fichier << clus.id << ","
                << clus.capacite_cluster << ","
                << clus.center_lon << ","
                << clus.center_lat << ","
                << clus.current_load << ","
                << clus.sum_pir << ","
                << clus.sum_cir << ",";

        // Gestion du vecteur users_id
        // On les sépare par un ";" pour ne pas casser la structure du CSV (virgules)
        for (size_t i = 0; i < clus.users_id.size(); ++i) {
            fichier << clus.users_id[i];
            if (i < clus.users_id.size() - 1) {
                fichier << ";"; 
            }
        }
        
        fichier << "\n"; // Fin de ligne pour le cluster actuel
    }

    // Fermeture du fichier
    fichier.close();
    
    std::cout << "Fichier " << nomFichier << " genere avec succes (" << clusters.size() << " clusters)." << std::endl;
}