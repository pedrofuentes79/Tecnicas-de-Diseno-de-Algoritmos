#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Player {
    string name;
    int attack;
    int defense;

    // Custom comparison function to sort players
    bool operator<(const Player& other) const {
        if (attack != other.attack) {
            return attack > other.attack; // Sort by attacking ability (non-ascending)
        } else if (defense != other.defense) {
            return defense > other.defense; // If attacking abilities are tied, sort by defending ability (non-ascending)
        } else {
            return name < other.name; // If both abilities are tied, select the lexicographically earliest name
        }
    }
};

int main() {
    int testCases;
    cin >> testCases;

    for (int t = 0; t < testCases; ++t) {
        vector<Player> players(10);
        for (int i = 0; i < 10; ++i) {
            cin >> players[i].name >> players[i].attack >> players[i].defense;
        }
        cout << players[0].name << endl;
        // Sort the players based on the custom comparison function
        sort(players.begin(), players.end());

        // Select the top 5 players as attackers and the next 5 as defenders
        vector<Player> attackers(players.begin(), players.begin() + 5);
        vector<Player> defenders(players.begin() + 5, players.end());


        // before outputting the selected players, sort them by name
        sort(attackers.begin(), attackers.end(), [](const Player& a, const Player& b) {
            return a.name < b.name;
        });

        // Output the selected attackers and defenders
        cout << "Case " << t + 1 << ":" << endl;
        cout << "(";
        for (int i = 0; i < 5; ++i) {
            cout << attackers[i].name;
            if (i != 4) cout << ", ";
        }
        cout << ")" << endl;
        cout << "(";
        for (int i = 0; i < 5; ++i) {
            cout << defenders[i].name;
            if (i != 4) cout << ", ";
        }
        cout << ")" << endl;
    }

    return 0;
}
