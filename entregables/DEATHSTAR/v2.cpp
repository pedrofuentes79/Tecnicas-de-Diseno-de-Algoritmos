#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// const int N = 500; // Asumiendo un máximo de 500 torres
// int M[N][N]; // Matriz de adyacencia
// int destruido[N]; // Arreglo de nodos destruidos (0 o 1)
// int orden[N]; // Orden de destrucción de torres
// long long energia_total; // Suma total de energía

void solve() {
    int n;
    cin >> n;

    vector<vector<int>> D(n, vector<int>(n)); // Matriz de adyacencia
    vector<bool> restaurado(n, false); 
    vector<int> orden(n); // Orden de destrucción de torres
    long long energia_total = 0;

    // Leer la matriz de adyacencia
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> D[i][j];
        }
    }

    // Leer el orden de destrucción
    for (int i = 0; i < n; ++i) cin >> orden[i];

    // Iterar en orden inverso de destrucción
    for (int iter = n - 1; iter >= 0; --iter) {
        int z = orden[iter];
        restaurado[z] = true; // Marcar el nodo actual como restaurado

        // Actualizar la matriz de distancias mínimas usando Floyd-Warshall con el nodo restaurado
        for (int k = 0; k < n; ++k) {
            for (int j = 0; j < n; ++j) {
                D[k][j] = min(D[k][j], D[k][z] + D[z][j]);
            }
        }

        // Sumar las distancias mínimas para los nodos restaurados
        for (int k = 0; k < n; ++k) {
            if (restaurado[k]) {
                for (int j = 0; j < n; ++j) {
                    if (restaurado[j]) {
                        energia_total += D[k][j];
                    }
                }
            }
        }
    }

    cout << energia_total << endl; // Imprimir la suma total de energía
}

int main() {
    int t;
    cin >> t;

    while (t-- > 0) {
        solve();
    }

    return 0;
}
