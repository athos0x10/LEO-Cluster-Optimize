/**
 * @file greedy_disk_clustering.hpp
 * @author louan
 * @brief
 * @version 0.1
 * @date 2026-04-01 it's a joke
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef CONVERT_CLUSTER_CSV_HPP
#define CONVERT_CLUSTER_CSV_HPP

#include "greedy_disk_clustering.hpp"
#include <vector>


/**
 * @brief Permet de creer un fichier csv des clusters.
 *
 * @param nomFichier string nom du fichier CSV a creer.
 * @param clusters std::vector<Cluster> la liste de cluster a convertir en csv.
 */
void clusterToCsv(std::string nomFichier, std::vector<Cluster> clusters);



#endif // CONVERT_CLUSTER_CSV_HPP