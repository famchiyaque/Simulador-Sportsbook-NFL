#ifndef BET_FUNCTIONS_H_
#define BET_FUNCTIONS_H_

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

string trim(string str) { // O(n)
    str.erase(0, str.find_first_not_of(' '));  // Remove leading spaces
    str.erase(str.find_last_not_of(' ') + 1);  // Remove trailing spaces
    return str;
}

bool checkMoney(int money, int bet_amount) { // O(1)
    if (money >= bet_amount) {
        return true;
    } else {
        return false;
    }
}

char overUnder(string name, string bet_line, string over, string under) { // O(1)
    char betChoice;
    cout << "Ingresa 'o' para " << name << " over " << bet_line << " a " << over << " o 'u' para under " << bet_line << " a "  << under << endl;
    cin >> betChoice;
    if (betChoice == 'o' || betChoice == 'u') {
        // char confirm;
        if (betChoice == 'o') {
            cout << name << " para mas que " << bet_line << endl;
            cout << endl;
            return 'o';
        }
        else if (betChoice == 'u') {
            cout << name << " para menos que " << bet_line << endl;
            cout << endl;
            return 'u';
        } else {
            return 'f';
        }
    }
}

int getBetAmount(int money) { // O(1)
    int betAmount;
    cout << "Cuanto quieres apostar? Tienes balance de: $" << money << " o, ingresa '-1' para salir" << endl;
    cin >> betAmount;
    if (betAmount > 0 && betAmount <= money) {
        return betAmount;
    } else if (betAmount == -1) {
        return -1;
    } else {
        return 0;
    }
}

float getPayout(string odd, int bet) { // O(1)
    odd = trim(odd);
    string oddString = "";
    float oddNum;
    float ratio;
    if (odd[0] == '+') {
        oddString = oddString + odd[1] + odd[2] + odd[3];
        oddString = trim(oddString);
        oddNum = stoi(oddString);
        ratio = oddNum / 100; 
        return bet + bet*ratio;
    } else if (odd[0] == '-') {
        oddString = oddString + odd[1] + odd[2] + odd[3];
        oddString = trim(oddString);
        oddNum = stoi(oddString);
        ratio = 100 / oddNum;
        return bet + bet*ratio;
    }
}

float getLimit(string line) { // O(n) n = longitud de la apuesta
    string wholeNum = "";
    for (int i = 0; i < line.length(); i++) {
        if (line[i] != ' ') {
            while (line[i] != '.') {
                wholeNum += line[i];
                i++;
            }
            break;
        }
    }
    float limit = stoi(wholeNum) + 0.5;
    return limit;
}

class Bet {
    public:
        string player_name;
        string player_line;
        string type_bet;
        string type;
        float limit;
        int bet_amount;
        float payout;
        int index;

    // public:
        int minusBetFromBalance();
        void makeBet(string, int, int);
        string printBet();
        int resolveBet(Bet, const vector<int>&);
        Bet();
        Bet(string, int, int);
        // string 

    friend class ParLinkBet;
};

Bet::Bet() { // O(1)
    player_name = "";
    player_line = "";
    type_bet = "";
    type = "";
    limit = 0.0;
    bet_amount = 0;
    payout = 0.0;
    index = 0;
}

Bet::Bet(string line, int money, int index) { 
    makeBet(line, money, index);
}

int Bet::minusBetFromBalance() { // O(1)
    return bet_amount;
}

void Bet::makeBet(string line, int money, int index) { // O(n) n = longitud de apuesta
    string curr = "";
    string name = "";
    string bet_line = "";
    string over = "";
    string under = "";
    string new_id = "";
    int readIndex = 1;
    for (int i = 0; i < line.length(); i++) { // O(n) n = longitud de apuesta
        if (line[i] == '|' || i == line.length() - 1) {
            if (readIndex == 1) {
                name = trim(curr);
                // this->player_name = curr;
            } else if (readIndex == 2) {
                bet_line = trim(curr);
                // this->player_line = curr;
            } else if (readIndex == 3) {
                over = trim(curr);
            } else if (readIndex == 4) {
                curr += line[i];
                under = trim(curr);
            }
            curr = "";
            readIndex++;
        } else {
            curr += line[i];
        }
    }
    // char betChoice;
    // cout << "Quieres tomar el over (ingresa 'o'): " << over << " o el under (ingresa 'u'): " << under << " para " << name << endl;
    // cin >> betChoice;
    char betChoice = overUnder(name, bet_line, over, under); // O(1)
    while (!(betChoice == 'o' || betChoice == 'u')) {
        if (betChoice == 'f') return;
        betChoice = overUnder(name, bet_line, over, under); // O(1)
    }

    int betAmount = getBetAmount(money); // O(1)
    while (betAmount <= 0 || betAmount > money) {
        if (betAmount == -1) return;
        cout << "Monto invalido, intenta otra vez" << endl;
        betAmount = getBetAmount(money); // O(1)
    }

    cout << "Creando apuesta... " << endl;
    cout << endl;
    int new_payout;
    if (betChoice == 'o') {
        new_payout = getPayout(over, betAmount); // O(1)
        cout << "Tu apuesta de " << name << " para mas que " << bet_line << " con monto de $" << betAmount << " y odds de " << over << " tiene payout de $" << new_payout << endl;
    } else if (betChoice == 'u') {
        new_payout = getPayout(under, betAmount); // O(1)
        cout << "Tu apuesta de " << name << " para menos que " << bet_line << " con monto de $" << betAmount << " y odds de " << over << " tiene payout de $" << new_payout << endl;
    }
    cout << endl;

    this->player_name = name;
    if (betChoice == 'o') {
        this->player_line = "over " + bet_line;
        this->type_bet = over;
        this->type = "over";
    } else if (betChoice == 'u') {
        this->player_line = "under " + bet_line;
        this->type_bet = under;
        this->type = "under";
    }
    this->limit = getLimit(bet_line); // O(1)
    this->bet_amount = betAmount;
    this->payout = new_payout;
    this->index = index;
}

string Bet::printBet() { // O(1)
    string stringBet;
    stringBet += this->player_name + " para ";
    stringBet += this->player_line + " a ";
    stringBet += this->type_bet + " con apuesta de $";
    stringBet += std::to_string(this->bet_amount) + " y payout de $";
    stringBet += std::to_string(this->payout);
    return stringBet;
    // cout << this.player_name << " para " << this.player_line << " a " << this.type_bet << " con apuesta de " << this.bet_amount << " y payout de: " << this.payout << endl;
}

int resolveBet(Bet bet, const vector<int>& bet_results) { // O(1)
    int betIndex = bet.index;
    int result = bet_results[betIndex];
    if ((result > bet.limit && bet.type == "over") || (result < bet.limit && bet.type == "under")) {
        return bet.payout;
    } else {
        return 0;
    }
}


class ParLinkBet {
    private:
        ParLinkBet * next;
        Bet * betptr;

    friend class Parlay;
    public:
        ParLinkBet();
};

ParLinkBet::ParLinkBet() { // O(1)
    next = NULL;
    betptr = NULL;
}

class Parlay {
    private:
        ParLinkBet * head;
        int size;
        float totalBetWager;
        float payout;

    public:
        int addBet(string, int, int);
        int undoBet();
        void readParlay();
        void updateTotalBetWager();
        int sizeParlay();
        float gradeParlay(const vector<int>&);
        Parlay();
        ~Parlay();
};

Parlay::Parlay() { // O(1)
    head = NULL;
    size = 0;
    payout = 0;
}

Parlay::~Parlay() { // O(1)
    size = 0;
    head = NULL;
    payout = 0;
}

int Parlay::sizeParlay() { // O(1)
    return size;
}

int Parlay::undoBet() { // O(1)
    ParLinkBet * victim = head;
    totalBetWager -= head->betptr->payout;
    int moneyBack = head->betptr->bet_amount;
    if (victim->next != NULL) {
        head = victim->next;
        delete victim;
    } else {
        head = NULL;
    }
    size--;
    payout = totalBetWager * pow(1.1, size-1);
    return moneyBack;
}

int Parlay::addBet(string line, int money, int index) { // O(1)
    ParLinkBet * new_parlay_bet = new ParLinkBet;
    Bet * new_bet = new Bet(line, money, index);
    new_parlay_bet->betptr = new_bet;
    if (head == NULL) {
        head = new_parlay_bet;
    } else {
        new_parlay_bet->next = head;
        head = new_parlay_bet;
    }
    totalBetWager += new_bet->payout;
    size++;
    payout = totalBetWager * pow(1.1, size - 1);
    return new_bet->bet_amount;
}

float Parlay::gradeParlay(const vector<int>& bet_results) { // O(n)
    cout << "Resultados de tu Parlay: " << endl;
    ParLinkBet * currPBet = head;
    int counter = 1;
    while (currPBet != NULL) {
        Bet * currBet = currPBet->betptr;
        int betIndex = currBet->index;
        float betLimit = currBet->limit;
        int result = bet_results[betIndex];
        string type = currBet->type;
        
        cout << "Tu apuesta " << counter << ": " << currBet->player_name << " para " << currBet->player_line << endl;
        cout << "Resultado: " << currBet->player_name << " tuvo " << result << endl;
        if ((betLimit < result && type == "over") || (betLimit > result && type == "under")) {
            cout << "Este fue un exito, a seguir" << endl;
        } else {
            cout << "Esta apuesta de tu parlay no pego, perdiste todo el parlay " << endl;
            return 0;
        }
        currPBet = currPBet->next;
        counter++;
    }
    cout << endl;
    cout << "Felicidades, ganaste tu parlay! " << endl;
    cout << "Te llevas el payout de este parlay, que fue: $" << payout << endl;
    return payout;
}

void Parlay::readParlay() { // O(n)
    cout << "Tu parlay hasta ahora: " << endl;
    ParLinkBet * currPBet = head;
    // Bet currBet = currPBet->betptr;
    while (currPBet != NULL) {
        Bet * currBet = currPBet->betptr;
        cout << currBet->player_name << " para " << currBet->player_line << " con monto de: $" << currBet->bet_amount << endl;
        currPBet = currPBet->next;
    }
    cout << "payout total para este parlay: $" << payout << endl;
    cout << endl;
}

#endif