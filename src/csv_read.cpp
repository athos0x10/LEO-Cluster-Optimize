#include "csv_read.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

std::vector<UserPoint> CsvToUser(const std::string &filename) {
  std::vector<UserPoint> users;
  std::ifstream file(filename);

  // Vérification de l'ouverture du fichier
  if (!file.is_open())
    return users;

  std::string line;
  // Lecture du header
  std::getline(file, line);

  int id = 1;
  while (std::getline(file, line)) {
    line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
    line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
    // Si la ligne est vide on l'ignore
    if (line.find_first_not_of(" \t") == std::string::npos) {
      continue;
    }

    std::stringstream ss(line);
    std::string value;
    UserPoint u;

    try {
      u.id = id;
      // Lecture dans l'ordre du header : LON, LAT, PIR, CIR, SERVICE
      if (!std::getline(ss, value, ','))
        continue;
      u.lon = std::stod(value);
      if (!std::getline(ss, value, ','))
        continue;
      u.lat = std::stod(value);
      if (!std::getline(ss, value, ','))
        continue;
      u.pir = std::stod(value);
      if (!std::getline(ss, value, ','))
        continue;
      u.cir = std::stod(value);
      if (!std::getline(ss, value, ','))
        continue;
      u.service = std::stoi(value);

      // Ajout dans le vector
      users.push_back(u);
      id++;
    } catch (...) {
      // On ignore les lignes malformées
      continue;
    }
  }
  file.close();
  return users;
}