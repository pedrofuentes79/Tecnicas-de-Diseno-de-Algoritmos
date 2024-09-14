# include <iostream>
# include <vector>
using namespace std;

int maxAcornsv2(vector<vector<int>>& acorns, int h, int f, int i, int j, vector<vector<int>>& memo){
    // i is the current tree
    // j is the current height

    // h is the height of the tree.
    // f is the fall height
    // acorns is of shape (t, h)

    // caso base
    // llego al final
    if (j==0){
        return acorns[i][j];
    }
    // no puede saltar a otro arbol
    if (j-f < 0){
        // devolver la sumatoria de acorns a obtener en el arbol actual
        int sumatoria = 0;
        for (int k = j; k>=0; k--){
            sumatoria += acorns[i][k];
        }
        return sumatoria;
    }

    if (memo[i][j] == -1) {
        // dos opciones, saltar a cualquier arbol, o quedarse en el arbol i
        int maxQuedarse = maxAcornsv2(acorns, h, f, i, j-1, memo);

        int maxSaltar = 0;
        // iterar sobre todos los posibles arboles
        for (int k = 0; k < acorns.size(); k++){
            // obtener la cantidad maxima de acorns en el k-esimo arbol
            if (k == i){
                // evito el caso de saltar al mismo arbol pues no tiene sentido
                continue;
            }
            maxSaltar = max(maxSaltar, maxAcornsv2(acorns, h, f, k, j-f, memo));
        }
        int maxAcorns = max(maxQuedarse, maxSaltar);
        memo[i][j] = maxAcorns + acorns[i][j];
    }

    return memo[i][j]; 
}

int main(){
    // speed up?
    ios_base::sync_with_stdio(false);

    int testCases;
    cin >> testCases;

    vector<int> T(testCases), H(testCases), F(testCases);

    vector<vector<vector<int>>> ACORNS = vector<vector<vector<int>>>(testCases);

    // PARSE INPUTS
    for (int i = 0; i < testCases; i++){
        int t, h, f;
        cin >> t >> h >> f;
        T[i] = t;
        H[i] = h;
        F[i] = f;

        //
        vector<vector<int>> acorns = vector<vector<int>>(t, vector<int>(h, 0));
        // get trees
        for (int i = 0; i < t; i++){
            // get amount of acorns in the current tree
            int a;
            cin >> a;
            for (int j = 0; j < a; j++){
                int height;
                cin >> height;
                // the floor doesn't exist as an index. It would be -1
                acorns[i][height-1]++;
            }
        }
        ACORNS[i] = acorns;
    }
    // read zero to end input
    int zero;
    cin >> zero;

    // SOLVE: TOP DOWN
    for (int i = 0; i < testCases; i++){
        // initialize memory. 
        // H[i] is this test case's height, T[i] is this case's tree count
        vector<vector<int>> memo = vector<vector<int>>(T[i], vector<int>(H[i], -1));
        int maxAcorns = 0;
        for (int l = 0; l < T[i]; l++){
            // llamo a la funcion con todos los arboles posibles (l)
            // y la altura maxima H[i]-1, que es el valor mas alto posible del arbol
            maxAcorns = max(maxAcorns, maxAcornsv2(ACORNS[i], H[i], F[i], l, H[i]-1, memo));
        }
        cout << maxAcorns << endl;
    }


    cout << endl;

    return 0;
}