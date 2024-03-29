#include <iostream>
#include <vector>
#include <algorithm>

struct Player {
    std::string name;
    int attack;
    int defense;
};

void backtrack(const std::vector<Player>& players, 
                std::vector<Player>& attackers, 
                std::vector<Player>& defenders,
               size_t index, 
               int& bestAttackSum, 
               int& bestDefenseSum, 
               std::vector<std::string>& bestAttackersNames,
               std::vector<std::string>& bestDefendersNames) {


    // CASO BASE: AGREGUE TODOS LOS PLAYERS
    if (index == players.size()) {
        int attackSum = 0;
        int defenseSum = 0;
        for (const auto& player : attackers) {
            attackSum += player.attack;
        }
        for (const auto& player : defenders) {
            defenseSum += player.defense;
        }

        // REEMPLAZOS
        if (attackSum > bestAttackSum || (attackSum == bestAttackSum && defenseSum > bestDefenseSum)) {
            bestAttackSum = attackSum;
            bestDefenseSum = defenseSum;
            bestAttackersNames.clear();
            for (const auto& player : attackers) {
                bestAttackersNames.push_back(player.name);
            }
            bestDefendersNames.clear();
            for (const auto& player : defenders) {
                bestDefendersNames.push_back(player.name);
            }
        } else if (attackSum == bestAttackSum && defenseSum == bestDefenseSum) {
            // CASO DESEMPATE LEXICOGRAFICO

            std::vector<std::string> attackersNames;
            for (const auto& player : attackers) {
                attackersNames.push_back(player.name);
            }
            // Ordeno los nombres de ambas listas para compararlas
            std::sort(attackersNames.begin(), attackersNames.end());
            std::sort(bestAttackersNames.begin(), bestAttackersNames.end());

            if (attackersNames < bestAttackersNames) {
                bestAttackSum = attackSum;
                bestDefenseSum = defenseSum;
                bestAttackersNames.clear();
                for (const auto& player : attackers) {
                    bestAttackersNames.push_back(player.name);
                }
                bestDefendersNames.clear();
                for (const auto& player : defenders) {
                    bestDefendersNames.push_back(player.name);
                }
            }
        }
        return;
    }

    if (attackers.size() < 5) {
        attackers.push_back(players[index]);
        backtrack(players, attackers, defenders, index + 1, bestAttackSum, bestDefenseSum, bestAttackersNames, bestDefendersNames);
        attackers.pop_back();
    } else {
        defenders.push_back(players[index]);
        backtrack(players, attackers, defenders, index + 1, bestAttackSum, bestDefenseSum, bestAttackersNames, bestDefendersNames);
        defenders.pop_back();
    }
}

int main() {
    int test_cases;
    std::cin >> test_cases;

    for (int i = 0; i < test_cases; ++i) {
        std::vector<Player> players(10);
        for (int j = 0; j < 10; ++j) {
            std::cin >> players[j].name >> players[j].attack >> players[j].defense;
        }

        int bestAttackSum = 0;
        int bestDefenseSum = 0;
        std::vector<Player> attackers;
        std::vector<Player> defenders;
        std::vector<std::string> bestAttackersNames;
        std::vector<std::string> bestDefendersNames;

        backtrack(players, attackers, defenders, 0, bestAttackSum, bestDefenseSum, bestAttackersNames, bestDefendersNames);

        // Sort the answer
        std::sort(bestAttackersNames.begin(), bestAttackersNames.end());
        std::sort(bestDefendersNames.begin(), bestDefendersNames.end());
        
        // Print the answer
        std::cout << "Case " << i + 1 << ":\n";
        std::cout << "(";
        for (size_t j = 0; j < bestAttackersNames.size(); ++j) {
            if (j > 0) {
                std::cout << ", ";
            }
            std::cout << bestAttackersNames[j];
        }
        std::cout << ")\n";

        std::cout << "(";
        for (size_t j = 0; j < bestDefendersNames.size(); ++j) {
            if (j > 0) {
                std::cout << ", ";
            }
            std::cout << bestDefendersNames[j];
        }
        std::cout << ")\n";
    }

    return 0;
}

