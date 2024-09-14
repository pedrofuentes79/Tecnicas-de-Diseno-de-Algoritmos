#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <tuple>
#include <sstream>

using namespace std;


int dp_inc(vector<int>& heights, vector<int>& widths, int i, int j, vector<vector<int>>& memo) {
    // i is the end, j is the beginning

    // casos base
    // caso subseq de 1 elem
    if (i == j) return widths[i];

    // caso recursivo
    if (memo[i][j] == -1) {
        // busco el maximo ancho de todas las subsecuencias decrecientes entre 0 e i
        int max_width = 0;
        for (int k = j; k < i; k++) {
            if (heights[k] < heights[i]) {
                max_width = max(max_width, dp_inc(heights, widths, k, j, memo));
            }
        }

        memo[i][j] = max_width + widths[i];
    }
    return memo[i][j];
}




int dp_dec(vector<int>& heights, vector<int>& widths, int i, int j, vector<vector<int>>& memo) {
    // i is the end, j is the beginning

    // casos base
    // caso subseq de 1 elem
    if (i == j) return widths[i];

    // caso recursivo
    if (memo[i][j] == -1) {
        // busco el maximo ancho de todas las subsecuencias decrecientes entre 0 e i
        int max_width = 0;
        for (int k = j; k < i; k++) {
            if (heights[k] > heights[i]) {
                max_width = max(max_width, dp_dec(heights, widths, k, j, memo));
            }
        }

        memo[i][j] = max_width + widths[i];
    }
    return memo[i][j];
}



int main() {
    // top-down implementation btw


    int testCases;
    cin >> testCases;

    // armar un vector con los casos de prueba. Cada caso de prueba tiene un vector de alturas y de anchos
    vector<vector<int>> H = vector<vector<int>>(testCases);
    vector<vector<int>> W = vector<vector<int>>(testCases);

    // parse input
    for (int t = 0; t < testCases; t++) {
        int n;
        cin >> n;
        cin.ignore();

        // tomar los n elementos separados por espacios y asignarselos a heights
        std::string input_heights;
        std::getline(std::cin, input_heights);
        std::istringstream iss1(input_heights);
        int num1;
        while (iss1 >> num1) {
            H[t].push_back(num1);
        }

        std::string input_widths;
        std::getline(std::cin, input_widths);
        std::istringstream iss2(input_widths);
        int num2;
        while (iss2 >> num2) {
            W[t].push_back(num2);
        }
    }

    for (int t = 0; t < testCases; t++) {
        // INICIALIZO MEMORIA   
        int n = H[t].size();

        vector<vector<int>> memo_increasing = vector<vector<int>>(n, vector<int>(n, -1));
        vector<vector<int>> memo_decreasing = vector<vector<int>>(n, vector<int>(n, -1));

        // RES
        int max_length_inc = 0;
        int max_length_dec = 0;
        for (int i = 0; i < n; i++) {
            int curr_length_inc = dp_inc(H[t], W[t], i, 0, memo_increasing);
            int curr_length_dec = dp_dec(H[t], W[t], i, 0, memo_decreasing);
            max_length_inc = max(max_length_inc, curr_length_inc);
            max_length_dec = max(max_length_dec, curr_length_dec);
        }
        cout << "Case " << t+1 << ". ";
        if (max_length_inc >= max_length_dec) {
            cout << "Increasing (" << max_length_inc << "). Decreasing (" << max_length_dec << ")." << endl;
        } else {
            cout << "Decreasing (" << max_length_dec << "). Increasing (" << max_length_inc << ")." << endl;
        }
    }
    
}