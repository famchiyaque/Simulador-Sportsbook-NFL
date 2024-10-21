#include <iostream>
#include <vector>
#include "bet_functions.h"
#include "util.h"
using namespace std;

// Avance 2: Parlay Maker!!!
// Linked Lists para hacer parlays de apuestas de futból Americano
// Aquí puedes hacer apuestas y/o un parlay de las líneas dadas por
// "Las Vegas" y ver cómo te va en la vida real!


// vectores globales de las apuestas/parlays del usuario
vector<Bet> user_bets;
Parlay parlay = Parlay();
vector<string> bet_lines = {""};
vector<int> bet_results = {0};
int money;

void createParlay() {
  int index;
  while (index != -1) {
    readBets(bet_lines);
    cout << "Ingresa el numero de la apuesta para agregarla a tu parlay, -1 para quitar la ultima apuesta que le agregaste, -2 para cancelar este parlay, o 0 para guardar " << endl;
    cin >> index;
    if (index == -2) {
      parlay.~Parlay();
    } else if (index == -1) {
      money += parlay.undoBet();
    } else if (index == 0) {
      break;
    } else if (index > 0 && index < bet_lines.size()) {
      string currLine = bet_lines[index];
      int minus = parlay.addBet(currLine, money, index);
      money -= minus;
    } else {
      cout << "input invalido " << endl;
    }
    parlay.readParlay();
  }
}

int main() {  
  welcomeMessage();

  bool valid_money = false;
  while (!valid_money) {
    cout << "Antes que nada, deposita alguna cantidad de dinero en tu cuenta" << endl;
    cin >> money;
    if (money > 0) {
      valid_money = true;
    } else {
      cout << "Invalid deposito, intenta otra vaz (ingresa un numero en tu teclado)" << endl;
    }
  }

  cout << "Balance: " << money << endl;
  cout << "Cargando apuestas disponibles..." << endl;
  readOffers("offers.txt", bet_lines);
  cout << endl;

  int input = -1;
  while (input != 0) {
        readBets(bet_lines);
        cout << "Ingresa el numero de la oferta para apostar, '-1' para empezar un parlay, o '0' para guardar ." << endl;
        cin >> input;
        cout << endl;
        if (input == 0) {
          cout << "guardando tus apuestas..." << endl;
          cout << endl;
          break;
        } else if (input > 0 && input < bet_lines.size()) {
          string currLine = bet_lines[input];
          cout << "Apuesta elegida: " << currLine << endl;
          cout << endl;
            Bet new_bet;
            new_bet.makeBet(currLine, money, input);
            user_bets.push_back(new_bet);
            money -= new_bet.minusBetFromBalance();
        } else if (input == -1) {
          cout << endl;
          cout << "Cargando Editor de Parlay..." << endl;
          cout << endl;
          createParlay();
          
          // cout << "Ingresa el numero de la apuesta para agregarla a tu parlay" << endl;
          // new_parlay;
        } else {
          cout << "Input invalido, intenta otra vez" << endl;
        }
        char seguir;
        cout << "Quieres salir del bet-maker? (y/n)" << endl;
        cin >> seguir;
        if (seguir == 'y') break;
  }

    cout << endl;
  
  cout << "________________________________________________________" << endl;
  cout << "Tu balance despues de crear apuestas/parlays: $" << money << endl;

    if (user_bets.size() == 0 && parlay.sizeParlay() == 0) {
      cout << "Saliste sin hacer una apuesta, no hay resultados entonces" << endl;
      cout << "Balance final: " << money << endl;
    } else {
        cout << "________________________________________________________" << endl;
        cout << endl;
        cout << "**Ya pasaron los partidos**" << endl;
        cout << "Cargando los resultados" << endl;
        readResults("results.txt", bet_results);

      if (user_bets.size() > 0) {
        cout << "Resultados de tus apuestas normales: " << endl;
        cout << endl;
        for (int i = 0; i < user_bets.size(); i++) {
          Bet curr = user_bets[i];
          cout << curr.player_name << " para " << curr.type << " " << curr.player_line << endl;
          cout << "Resultado: " << curr.player_name << " tuvo " << bet_results[curr.index] << endl;
          int winnings = resolveBet(user_bets[i], bet_results);
          cout << "Winnings de apuestas: $" << winnings << endl;
          money += winnings;
          cout << "--------------------------------------------------------" << endl;
        }
      }
      if (parlay.sizeParlay() > 0) {
        money += parlay.gradeParlay(bet_results);
      }

      cout << "Dinero despues de esta semana: $" << money << endl;
  }

  return 0;
}