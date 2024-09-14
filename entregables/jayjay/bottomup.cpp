# include <iostream>
# include <vector>
using namespace std;


vector<vector<int>> bottom_upv2(vector<vector<int>>& acorns, int h, int f){
    vector<vector<int>> memo = vector<vector<int>>(acorns.size(), vector<int>(h, 0));

    // initialize for height 0
    for (int l = 0; l < acorns.size(); l++){
        memo[l][0] = acorns[l][0];
    }

    // resto de alturas    
    for (int k = 1; k < h; k++){ // k es la altura
        for (int l = 0; l < acorns.size(); l++){ // l es el arbol
            
            if (k-f < 0){
                // CASO 1: no puede saltar a otro arbol y se queda => 
                // devolver el maximo de acorns de no saltar ahora y quedarse
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
    cin.tie(NULL);

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

    // SOLVE: BOTTOM-UP
    for (int i = 0; i < testCases; i++){
        vector<vector<int>> matrix = bottom_upv2(ACORNS[i], H[i], F[i]);

        int maxAcorns = 0;
        for (int l = 0; l < ACORNS[i].size(); l++){
            // busco el maximo entre la altura maxima de los arboles
            // para ver desde cual arbol se pueden obtener mas acorns
            maxAcorns = max(maxAcorns, matrix[l][H[i]-1]);
        }
        cout << maxAcorns << endl;
    }

    cout << endl;

    return 0;
}