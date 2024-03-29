#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

void backtrack(
    vector<vector<string>>& players, 
    vector<string>& attackers, // current set of attackers
    vector<string>& defenders, // current set of defenders
    int start,                 // index in players. to avoid repetitions
    int& bestAttackSum, 
    int& bestDefenseSum, 
    vector<string>& bestAttackers, 
    vector<string>& bestDefenders
){
    int attackSum = 0, defenseSum = 0;

    // calculo la current suma de ataques y defensas: O(1)
    for (int i = 0; i < 5; i++) {
        attackSum += stoi(attackers[i]);
        defenseSum += stoi(defenders[i]);
    }


    // caso base: si ya tenemos 5 atacantes y 5 defensores
    if (attackers.size() == 5 && defenders.size() == 5) {
        // calculo la suma de los ataques y defensas
 
        // si es mejor que bestAttackSum
        if (attackSum > bestAttackSum || 
            (attackSum == bestAttackSum && defenseSum > bestDefenseSum)) {
            bestAttackSum = attackSum;
            bestDefenseSum = defenseSum;
            bestAttackers = attackers;
            bestDefenders = defenders;
        }
        else if (attackSum == bestAttackSum && defenseSum == bestDefenseSum) {
            // si es igual, comparo por orden lexicografico
            vector<string> temp = attackers;
            sort(temp.begin(), temp.end());
            vector<string> bestTemp = bestAttackers;
            sort(bestTemp.begin(), bestTemp.end());
            if (temp < bestTemp) {
                bestAttackers = attackers;
                bestDefenders = defenders;
            }
        }
        // finalizo la recursion, con esta rama no hay nada mas que hacer
        // otras ramas pueden modificar bestAttackSum y bestDefenseSum si son mejores q esta
        return;
    }

    // caso recursivo
    for (int i = start; i < players.size(); i++) {
        // primero lleno los atacantes. El resto de jugadores van a ir a defensores
        if (attackers.size() < 5) {
            // pruebo con el jugador i como atacante
            attackers.push_back(players[i][0]);
            backtrack(players, attackers, defenders, i + 1, bestAttackSum, bestDefenseSum, bestAttackers, bestDefenders);
            // vuelvo atras para probar con el i+1 como atacante...
            attackers.pop_back();
        }
        else {
            // si los atacantes estan llenos, pruebo meter los jugadores restantes como defensores
            defenders.push_back(players[i][0]);
            backtrack(players, attackers, defenders, i + 1, bestAttackSum, bestDefenseSum, bestAttackers, bestDefenders);
            defenders.pop_back();
        }
    }
}


int main() {
    int testCases;
    cin >> testCases;

    for (int t = 0; t < testCases; t++) {
        vector<vector<string>> players;
        for (int i = 0; i < 10; i++) {
            string name;
            int attack, defense;
            cin >> name >> attack >> defense;
            players.push_back({name, to_string(attack), to_string(defense)});
        }

        vector<string> attackers, defenders;
        int bestAttackSum = 0, bestDefenseSum = 0;
        vector<string> bestAttackers, bestDefenders;
        backtrack(players, attackers, defenders, 0, bestAttackSum, bestDefenseSum, bestAttackers, bestDefenders);

        cout << "Case " << t + 1 << ":" << endl;
        cout << "(";
        for (int i = 0; i < bestAttackers.size(); i++) {
            cout << bestAttackers[i];
            if (i != bestAttackers.size() - 1) cout << ", ";
        }
        cout << ")" << endl;
        cout << "(";
        for (int i = 0; i < bestDefenders.size(); i++) {
            cout << bestDefenders[i];
            if (i != bestDefenders.size() - 1) cout << ", ";
        }
        cout << ")" << endl;
    }

    return 0;
}