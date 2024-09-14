
# include <iostream>
# include <vector>
#include <sstream>
#include <string>
using namespace std;


vector<vector<int>> bottom_upv2(vector<vector<int>>& acorns, int h, int f){
    vector<vector<int>> memo = vector<vector<int>>(acorns.size(), vector<int>(h, 0));
    vector<int> maxes = vector<int>(h, -1);

    // Inicializo para altura 0
    int max_0 = 0;
    for (int l = 0; l < acorns.size(); l++){
        memo[l][0] = acorns[l][0];
        max_0 = max(max_0, acorns[l][0]);
    }
    maxes[0] = max_0;

    // Computo el resto de alturas 
    for (int k = 1; k < h; k++){
        int max_k = 0;

        for (int l = 0; l < acorns.size(); l++){ // l es el arbol
            // CASO 1: no puede saltar a otro arbol y se queda =>
            if (k-f < 0){
                memo[l][k] = memo[l][k-1] + acorns[l][k];
            } 
            // CASO 2: PUEDE SALTAR A OTRO ARBOL: saltar a cualquier arbol, o quedarse en el arbol l
            else {
                int maxQuedarse = memo[l][k-1];
                int maxSaltar = maxes[k-f];
                
                int maxAcorns = max(maxQuedarse, maxSaltar);
                memo[l][k] = maxAcorns + acorns[l][k];
            }

            // comparo el max_k anterior con lo que acabo de calcular
            max_k = max(max_k, memo[l][k]);
        }
        // guardo max_k
        maxes[k] = max_k;

    }
    return memo;
}


int main() {
    // speed up
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string line;
    getline(cin, line);
    int testCases = stoi(line);

    vector<int> T(testCases), H(testCases), F(testCases);
    vector<vector<vector<int>>> ACORNS = vector<vector<vector<int>>>(testCases);

    // PARSE INPUTS
    for (int i = 0; i < testCases; i++) {
        getline(cin, line);
        stringstream ss(line);
        int t, h, f;
        ss >> t >> h >> f;
        T[i] = t;
        H[i] = h;
        F[i] = f;

        vector<vector<int>> acorns = vector<vector<int>>(t, vector<int>(h, 0));
        for (int j = 0; j < t; j++) {
            getline(cin, line);
            stringstream tss(line);
            int a;
            tss >> a;
            for (int k = 0; k < a; k++) {
                int height;
                tss >> height;
                acorns[j][height - 1]++;
            }
        }
        ACORNS[i] = acorns;
    }

    // read zero to end input
    getline(cin, line);

    // SOLVE: BOTTOM-UP
    for (int i = 0; i < testCases; i++){
        vector<vector<int>> matrix = bottom_upv2(ACORNS[i], H[i], F[i]);

        int maxAcorns = 0;
        for (int l = 0; l < ACORNS[i].size(); l++){
            // busco el maximo #acorns en el nivel mas alto de los arboles
            maxAcorns = max(maxAcorns, matrix[l][H[i]-1]);
        }
        cout << maxAcorns << endl;
    }
    return 0;
}