/**
 * @file csv_read.hpp
 * @author Arthur
 * @author Louan
 * @brief Permet de lire un fichier csv pour le transformer en une structure
 * lisible.
 * @version 0.1
 * @date 2026-03-20
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef CSV_READ_HPP
#define CSV_READ_HPP

#include <string>
#include <vector>

/**
 * @brief La structure associé à un utilisateur.
 *
 */
struct UserPoint {
  int id;
  double lat;
  double lon;
  double cir;
  double pir;
  double service;
};

/**
 * @brief Permet de lire le csv pour le transformer en des données utilisables
 * @param filename le nom du fichier d'ou extraire les utilisateurs.
 * @param write booleen indicant si on ecrit ou non dans le fichier
 * @param fileUserName le nom du nouveau fichier contenant les utilisateurs avec leurs ID.
 * @return les données sous forme de la structure UserPoint.
 *
 */
std::vector<UserPoint> CsvToUser(const std::string &filename, bool write, const std::string &fileUserName);

/**
 * @brief Permet de lire un csv avec des users 
 * @param filename le nom du fichier d'ou extraire les utilisateurs.
 * @return les données sous forme de la structure UserPoint.
 *
 */
std::vector<UserPoint> CsvIdToUser(const std::string &filename);
#endif // CSV_READ_HPP