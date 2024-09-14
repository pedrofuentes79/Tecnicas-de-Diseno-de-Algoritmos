#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

// Clase que representa un borde en el grafo
struct Edge {
    int from, to, weight;
    Edge(int f, int t, int w) : from(f), to(t), weight(w) {}
};

class Graph {
public:
    Graph(int n) : adjList(n), numNodes(n) {}

    void addEdge(int u, int v, int weight) {
        adjList[u].push_back(Edge(u, v, weight));
        adjList[v].push_back(Edge(v, u, weight));
    }

    const vector<Edge>& getEdges(int node) const {
        return adjList[node];
    }

    int getNumNodes() const {
        return numNodes;
    }

private:
    // esto podria ser una vector de listas? para mayor eficiencia I guess
    vector<vector<Edge> > adjList;
    int numNodes;
};

// Clase que implementa una cola de prioridad mínima
class PriorityQueue {
public:
    void push(int weight, int node) {
        pq.push(make_pair(weight, node));
    }

    pair<int, int> pop() {
        pair<int, int> top = pq.top();
        pq.pop();
        return top;
    }

    bool empty() const {
        return pq.empty();
    }

private:
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
};

// Función para calcular el costo de rodar de una clave a otra
int calculate_roll_cost(const string& key1, const string& key2) {
    int cost = 0;
    for (int i = 0; i < 4; ++i) {
        int digit1 = key1[i] - '0';
        int digit2 = key2[i] - '0';
        int forward_roll = (digit2 - digit1 + 10) % 10;
        int backward_roll = (digit1 - digit2 + 10) % 10;
        cost += min(forward_roll, backward_roll);
    }
    return cost;
}

// Función para encontrar el costo mínimo para desbloquear todas las claves
int findMinimumRolls(int numKeys, vector<string>& keys) {
    Graph graph(numKeys);

    for (int i = 0; i < numKeys; ++i) {
        for (int j = i + 1; j < numKeys; ++j) {
            int weight = calculate_roll_cost(keys[i], keys[j]);
            graph.addEdge(i, j, weight);
        }
    }

    // busco el nodo minimo de inicio
    // es decir, el que tenga menor rolling cost desde 0000
    int min_start_cost = INT_MAX;
    int start_node = -1;
    for (int i = 0; i < numKeys; ++i) {
        int cost = calculate_roll_cost("0000", keys[i]);
        if (cost < min_start_cost) {
            min_start_cost = cost;
            start_node = i;
        }
    }

    int total_cost = min_start_cost;
    vector<bool> visited(numKeys, false);
    visited[start_node] = true;

    // Inicializar min heap con las aristas que salen del nodo inicial
    PriorityQueue pq;

    const vector<Edge>& edges = graph.getEdges(start_node);
    for (size_t i = 0; i < edges.size(); ++i) {
        const Edge& edge = edges[i];
        pq.push(edge.weight, edge.to);
    }

    // Algoritmo de Prim desde el nodo inicial
    while (!pq.empty()) {
        pair<int, int> top = pq.pop();
        int cost = top.first;
        int u = top.second;
        if (visited[u]) continue;

        visited[u] = true;
        total_cost += cost;

        const vector<Edge>& edges = graph.getEdges(u);
        for (size_t i = 0; i < edges.size(); ++i) {
            const Edge& edge = edges[i];
            int v = edge.to;
            if (!visited[v]) {
                pq.push(edge.weight, v);
            }
        }
    }

    return total_cost;
}

// Función principal para manejar la entrada y salida del programa
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;

    vector<int> results;

    for (int t = 0; t < T; ++t) {
        int N;
        cin >> N;
        vector<string> keys(N);
        for (int i = 0; i < N; ++i) {
            cin >> keys[i];
        }

        int result = findMinimumRolls(N, keys);
        results.push_back(result);
    }

    for (size_t i = 0; i < results.size(); ++i) {
        cout << results[i] << endl;
    }

    return 0;
}
