#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <tuple>
#include <algorithm>

using namespace std;

struct Edge {
    int from, to, weight;
    Edge(int f, int t, int w) : from(f), to(t), weight(w) {}
};

class Graph {
public:
    Graph(int n) : numNodes(n) {}

    void addEdge(int u, int v, int weight) {
        adjList[u].emplace_back(u, v, weight);
    }

    const vector<Edge>& getEdges(int node) const {
        if (adjList.find(node) != adjList.end()) {
            return adjList.at(node);
        } else {
            return emptyList;
        }
    }

    int getNumNodes() const {
        return numNodes;
    }

private:
    unordered_map<int, vector<Edge> > adjList;
    vector<Edge> emptyList;
    int numNodes;
};

int encode(int floor, int elevator, int numElevators) {
    return floor * numElevators + elevator;
}

// se puede modificar para que 'frene' cuando llega a un nodo que representa k, pero ya pasa el limite de tiempo.
int dijkstra(const Graph& graph, int start, int end) {
    vector<int> distances(graph.getNumNodes(), numeric_limits<int>::max());
    distances[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    pq.emplace(0, start);

    while (!pq.empty()) {
        int current_time = pq.top().first;
        int current_node = pq.top().second;
        pq.pop();

        if (current_node == end) {
            return current_time;
        }

        if (current_time > distances[current_node]) {
            continue;
        }

        for (const Edge& edge : graph.getEdges(current_node)) {
            int time = current_time + edge.weight;
            if (time < distances[edge.to]) {
                distances[edge.to] = time;
                pq.emplace(time, edge.to);
            }
        }
    }

    return numeric_limits<int>::max();
}

int solve_case(int n, int k, const vector<int>& times, const vector<vector<int> >& floors) {
    int numNodes = 100 * n + 1; // agrego un nodo mas para el fantasma
    int ghostNode = numNodes - 1;
    Graph graph(numNodes);

    // construyo los nodos del grafo que tienen los pisos conectados por aristas
    for (int i = 0; i < n; ++i) {
        for (size_t j = 0; j < floors[i].size(); ++j) {
            int u = encode(floors[i][j], i, n);

            if (j > 0) {
                int v = encode(floors[i][j - 1], i, n);
                int travel_time = times[i] * abs(floors[i][j] - floors[i][j - 1]);
                graph.addEdge(u, v, travel_time);
                graph.addEdge(v, u, travel_time);
            }
        }
    }

    // mapeo los pisos a los ascensores que pasan por ellos
    // esto es para luego unir los distintos nodos de pisos iguales con 60segundos
    // lo puedo hacer pues tengo el piso, el ascensor y el total de ascensores
    unordered_map<int, vector<int> > floorToElevators;
    for (int i = 0; i < n; ++i) {
        for (int floor : floors[i]) {
            floorToElevators[floor].push_back(i);
        }
    }

    // agrego las aristas de 'cambio de piso' entre los distintos ascensores
    // es todos a todos, pero solo entre los ascensores que pasan por el mismo piso
    for (const auto& entry : floorToElevators) {
        int floor = entry.first;
        const vector<int>& elevators = entry.second;
        for (size_t i = 0; i < elevators.size(); ++i) {
            for (size_t j = i + 1; j < elevators.size(); ++j) {
                int u = encode(floor, elevators[i], n);
                int v = encode(floor, elevators[j], n);
                graph.addEdge(u, v, 60);
                graph.addEdge(v, u, 60);
            }
        }
    }

    // conecto el nodo fantasma con los nodos que representan los pisos 0
    for (int i = 0; i < n; ++i) {
        if (find(floors[i].begin(), floors[i].end(), 0) != floors[i].end()) {
            int startNode = encode(0, i, n);
            graph.addEdge(ghostNode, startNode, 0);
        }
    }

    // hago dijsktra desde el nodo fantasma a los nodos que representan el piso k
    // se podria intervenir el codigo de dijkstra para que frene cuando llega a un piso que represente k
    // es decir, le podriamos dar un vector de nodos finales y que frene cuando llegue a uno de esos nodos
    // quizas es lo mismo? los nodos finales son O(n), esa busqueda quizas se puede optimizar si sabemos el ascensor actual por el que esta dijkstra
    // se podria optimizar pero ya pasa el tiempo, fue.
    int min_time = numeric_limits<int>::max();
    for (int i = 0; i < n; ++i) {
        if (find(floors[i].begin(), floors[i].end(), k) != floors[i].end()) {
            int endNode = encode(k, i, n);
            min_time = min(min_time, dijkstra(graph, ghostNode, endNode));
        }
    }
    // uso numeric limits max para representar infinito, si el min_time sigue siendo infinito, no se puede llegar al piso k
    return min_time == numeric_limits<int>::max() ? -1 : min_time;
}

int main() {
    int n, k;
    while (cin >> n >> k) {
        vector<int> times(n);
        for (int i = 0; i < n; ++i) {
            cin >> times[i];
        }

        vector<vector<int> > floors(n);
        for (int i = 0; i < n; ++i) {
            int num;
            while (cin >> num) {
                floors[i].push_back(num);
                if (cin.peek() == '\n' || cin.peek() == EOF) {
                    break;
                }
            }
        }

        int result = solve_case(n, k, times, floors);
        if (result == -1) {
            cout << "IMPOSSIBLE" << endl;
        } else {
            cout << result << endl;
        }
    }

    return 0;
}
