#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

const int N = 500; // Asumiendo un máximo de 500 torres
int adj[N][N]; // Matriz de adyacencia
int vis[N]; // Arreglo de nodos visitados
int x[N]; // Orden de destrucción de torres
long long sm; // Suma total de energía

void solve() {
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) vis[i] = 0; // Inicializar visitados a 0

    // Leer la matriz de adyacencia
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> adj[i][j];
        }
    }

    // Leer el orden de destrucción
    for (int i = 0; i < n; ++i) cin >> x[i];

    sm = 0; // Inicializar suma total de energía

    // Iterar en orden inverso de destrucción
    for (int i = n - 1; i >= 0; --i) {
        vis[x[i]] = 1; // Marcar el nodo actual como visitado

        // Actualizar la matriz de distancias mínimas usando Floyd-Warshall con el nodo restaurado
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                adj[u][v] = min(adj[u][v], adj[u][x[i]] + adj[x[i]][v]);
            }
        }

        // Sumar las distancias mínimas para los nodos visitados
        for (int u = 0; u < n; ++u) {
            if (vis[u]) {
                for (int v = 0; v < n; ++v) {
                    if (vis[v]) {
                        sm += adj[u][v];
                    }
                }
            }
        }
    }

    cout << sm << endl; // Imprimir la suma total de energía
}

int main() {
    int t;
    cin >> t;

    while (t-- > 0) {
        solve();
    }

    return 0;
}