#ifndef UTIL_H_
#define UTIL_H_

#include <cmath>
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void welcomeMessage() {
    cout << "-------------Bienvenidos al Betting-Booth!---------------" << endl;
    cout << "Aqui puedes hacer apuestas con las lineas que tenemos de los jugadores de la NFL, " << endl;
    cout << "o si te sientes muy confiado, puedes crear un parlay de varios apuestas, donde " << endl;
    cout << "el payout se multiplica por 1.1^(n-1), n siendo la cantidad de apuestas en tu parlay" << endl;
    cout << "Buena suerte! " << endl;
    cout << endl;
}

void readBets(const vector<string>& vec) {
    cout << "--------------OFERTA--------------" << endl;
    for (int i = 1; i < vec.size(); i++) {
        cout << i << ". " << vec[i] << endl;
    }
}

void readResults(string fileName, vector<int>& vec) {
  string line;
  ifstream file_open_results(fileName);
  if (file_open_results.is_open()) {
    while (getline(file_open_results, line)) {
      vec.push_back(stoi(line));
    }
  }
}

void readOffers(string fileName, vector<string>& vec) {
    string line;
    ifstream file_open_offers(fileName);
    if (file_open_offers.is_open()) {
      while (getline(file_open_offers, line)) {
        vec.push_back(line);
      }
    }
}


#endif