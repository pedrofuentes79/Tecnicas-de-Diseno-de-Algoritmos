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


int dijkstra(const Graph& graph, int start, vector<int>& possible_ends) {
    vector<int> distances(graph.getNumNodes(), numeric_limits<int>::max());
    distances[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    pq.emplace(0, start);

    while (!pq.empty()) {
        int current_time = pq.top().first;
        int current_node = pq.top().second;
        pq.pop();

        // check if current node is in possible_ends
        // O(n)... could be optimized to O(1) with a hash set?
        if (possible_ends.find(current_node) != possible_ends.end()){
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

int main(){
    return 0;
}
