#include "csv_read.hpp"
#include <iomanip>
#include <iostream>

int main() {
  std::string path = "../data/generated.csv";

  std::cout << "--- Chargement des utilisateurs depuis " << path << " ---"
            << std::endl;

  std::vector<UserPoint> users = CsvToUser(path);

  if (users.empty()) {
    std::cerr << "Aucun utilisateur charge. Verifiez le chemin ou le contenu "
                 "du fichier."
              << std::endl;
    return 1;
  }

  std::cout << "Succes ! " << users.size() << " utilisateurs charges.\n"
            << std::endl;

  // Affichage des 5 premiers pour verification
  std::cout << std::left << std::setw(5) << "ID" << std::setw(12) << "Lat"
            << std::setw(12) << "Lon" << std::setw(10) << "PIR" << std::setw(10)
            << "CIR" << std::endl;
  std::cout << std::string(50, '-') << std::endl;

  double total_pir = 0;
  int limit = (users.size() < 5) ? users.size() : 5;

  for (int i = 0; i < users.size(); ++i) {
    if (i < limit) {
      std::cout << std::left << std::setw(5) << users[i].id << std::setw(12)
                << users[i].lat << std::setw(12) << users[i].lon
                << std::setw(10) << users[i].pir << std::setw(10)
                << users[i].cir << std::endl;
    }
    total_pir += users[i].pir;
  }

  std::cout << std::string(50, '-') << std::endl;
  std::cout << "Charge totale PIR cumulee : " << total_pir / 1000.0
            << " Gbps (approx)" << std::endl;
  std::cout << "Nombre theorique de clusters (si cap=3Gbps) : "
            << (total_pir / 1000.0) / 3.0 << std::endl;

  return 0;
}