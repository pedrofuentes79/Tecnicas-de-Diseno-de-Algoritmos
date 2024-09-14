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

int bottom_up(vector<vector<int>>& acorns, int h, int f){
    // initialize memory
    vector<vector<int>> memo = vector<vector<int>>(acorns.size(), vector<int>(h, 0));

    // initialize for height 0
    for (int l = 0; l < acorns.size(); l++){
        memo[l][0] = acorns[l][0];
    }

    // resto de alturas
    for (int l = 0; l < acorns.size(); l++){ // l es el arbol
        for (int k = 1; k < h; k++){ // k es la altura
            
            // CASO 0: el salto cae en el 0
            if (k-f == 0){
                // busco el maximo de saltar a otro en altura 0
                int maxSaltar = 0;
                for (int m = 0; m < acorns.size(); m++){
                    // obtener la cantidad maxima de acorns en el k-esimo arbol
                    if (m == l){
                        // evito el caso de saltar al mismo arbol pues no tiene sentido
                        continue;
                    }
                    maxSaltar = max(maxSaltar, memo[m][0]);
                }
                memo[l][k] = maxSaltar + acorns[l][k];
            }


            // CASO 1: no puede saltar a otro arbol y se queda
            if (k-f < 0){
                // devolver la sumatoria de acorns del arbol actual
                int sumatoria = 0;
                for (int m = k; m>=0; m--){
                    sumatoria += acorns[l][m];
                }
                memo[l][k] = sumatoria;
            } else {
                // CASO 2: PUEDE SALTAR A OTRO ARBOL
                // dos opciones, saltar a cualquier arbol, o quedarse en el arbol i
                int maxQuedarse = memo[l][k-1];

                int maxSaltar = 0;
                // iterar sobre todos los posibles arboles
                for (int m = 0; m < acorns.size(); m++){
                    // obtener la cantidad maxima de acorns en el k-esimo arbol
                    if (m == l){
                        // evito el caso de saltar al mismo arbol pues no tiene sentido
                        continue;
                    }
                    maxSaltar = max(maxSaltar, memo[m][k-f]);
                }
                int maxAcorns = max(maxQuedarse, maxSaltar);
                memo[l][k] = maxAcorns + acorns[l][k];
            }
        }
    }

    // get max acorns: iterate over all trees starting from the top
    int maxAcorns = 0;
    for (int l = 0; l < acorns.size(); l++){
        maxAcorns = max(maxAcorns, memo[l][acorns[0].size()-1]);
    }
    return maxAcorns;
}


vector<vector<int>> bottom_upv2(vector<vector<int>>& acorns, int h, int f){
    // initialize memory
    vector<vector<int>> memo = vector<vector<int>>(acorns.size(), vector<int>(h, 0));

    // initialize for height 0
    for (int l = 0; l < acorns.size(); l++){
        memo[l][0] = acorns[l][0];
    }

    // resto de alturas

    
    for (int k = 1; k < h; k++){ // l es el arbol
        for (int l = 0; l < acorns.size(); l++){ // k es la altura
            
            // CASO 0: el salto cae en el 0
            if (k-f == 0){
                // busco el maximo de saltar a otro en altura 0
                int maxSaltar = 0;
                for (int m = 0; m < acorns.size(); m++){
                    // obtener la cantidad maxima de acorns en el k-esimo arbol
                    if (m == l){
                        // evito el caso de saltar al mismo arbol pues no tiene sentido
                        continue;
                    }
                    maxSaltar = max(maxSaltar, memo[m][0]);
                }
                memo[l][k] = maxSaltar + acorns[l][k];
            }

            else if (k-f < 0){
                // CASO 1: no puede saltar a otro arbol y se queda => devolver el maximo de acorns de no saltar ahora y quedarse
                memo[l][k] = memo[l][k-1] + acorns[l][k];
            } 
            else {
                // CASO 2: PUEDE SALTAR A OTRO ARBOL: saltar a cualquier arbol, o quedarse en el arbol l
                int maxQuedarse = memo[l][k-1];

                int maxSaltar = 0;
                // iterar sobre todos los posibles arboles
                for (int m = 0; m < acorns.size(); m++){
                    // obtener la cantidad maxima de acorns en el k-esimo arbol

                    if (m == l){
                        // evito el caso de saltar al mismo arbol pues no tiene sentido
                        // y si lo tuviese, no seria el maximo de todas maneras
                        continue;
                    }

                    maxSaltar = max(maxSaltar, memo[m][k-f]);
                }
                int maxAcorns = max(maxQuedarse, maxSaltar);
                memo[l][k] = maxAcorns + acorns[l][k];
            }
        }
    }

    return memo;
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

    // SOLVE: BOTTOM-UPv2
    // for (int i = 0; i < testCases; i++){
    //     vector<vector<int>> matrix = bottom_upv2(ACORNS[i], H[i], F[i]);

    //     int maxAcorns = 0;
    //     for (int l = 0; l < ACORNS[i].size(); l++){
    //         // busco el maximo entre la altura maxima de los arboles
    //         // para ver desde cual arbol se pueden obtener mas acorns
    //         maxAcorns = max(maxAcorns, matrix[l][H[i]-1]);
    //     }
    //     cout << maxAcorns << endl;
    // }

    // SOLVE: BOTTOM-UP
    // for (int i = 0; i < testCases; i++){
    //     int maxAcorns = bottom_up(ACORNS[i], H[i], F[i]);
    //     cout << maxAcorns << endl;
    // }


    cout << endl;

    return 0;
}