#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

void backtrack(
    vector<vector<string>>& players,
    vector<string>& attackers,
    vector<string>& defenders,
    int start,
    int& bestAttackSum,
    int& bestDefenseSum,
    vector<string>& bestAttackers,
    vector<string>& bestDefenders
) {
    // Base case: if we have selected 5 attackers and 5 defenders
    if (attackers.size() == 5 && defenders.size() == 5) {
        int attackSum = 0, defenseSum = 0;

        // Calculate the sum of attacking and defending abilities of the current set
        for (const string& attacker : attackers) {
            for (const vector<string>& player : players) {
                if (player[0] == attacker) {
                    attackSum += stoi(player[1]); // Add attacking ability
                    break;
                }
            }
        }
        for (const string& defender : defenders) {
            for (const vector<string>& player : players) {
                if (player[0] == defender) {
                    defenseSum += stoi(player[2]); // Add defending ability
                    break;
                }
            }
        }

        // If the current combination is better, or it is lexicographically earlier,
        // update the best results
        if (attackSum > bestAttackSum ||
            (attackSum == bestAttackSum && defenseSum > bestDefenseSum) ||
            (attackSum == bestAttackSum && defenseSum == bestDefenseSum && attackers < bestAttackers)) {
            bestAttackSum = attackSum;
            bestDefenseSum = defenseSum;
            bestAttackers = attackers;
            bestDefenders = defenders;
        }
        return;
    }

    // Recursive case
    for (int i = start; i < players.size(); ++i) {
        if (attackers.size() < 5) {
            attackers.push_back(players[i][0]);
            backtrack(players, attackers, defenders, i + 1, bestAttackSum, bestDefenseSum, bestAttackers, bestDefenders);
            attackers.pop_back();
        } else {
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

        // Local copies of attackers and defenders to preserve sorting
        vector<string> attackers, defenders;
        int bestAttackSum = 0, bestDefenseSum = 0;
        vector<string> bestAttackers, bestDefenders;
        
        // Ordenar los jugadores por nombre antes de llamar a backtrack
        // sort(players.begin(), players.end());

        backtrack(players, attackers, defenders, 0, bestAttackSum, bestDefenseSum, bestAttackers, bestDefenders);

        // ordenar antes de tirar output
        sort(bestAttackers.begin(), bestAttackers.end());
        sort(bestDefenders.begin(), bestDefenders.end());
        
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
