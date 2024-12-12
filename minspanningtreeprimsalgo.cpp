#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void addEdge(vector<pair<int, int>> adj[], int u, int v, int weight) {
    adj[u].push_back({v, weight});
    adj[v].push_back({u, weight});
}

void primMST(vector<pair<int, int>> adj[], int V) {
    vector<int> key(V, INT_MAX);
    vector<bool> inMST(V, false);
    vector<int> parent(V, -1);

    key[0] = 0;

    for (int count = 0; count < V - 1; count++) {
        int minKey = INT_MAX, u;

        for (int v = 0; v < V; v++) {
            if (!inMST[v] && key[v] < minKey) {
                minKey = key[v];
                u = v;
            }
        }

        inMST[u] = true;

        for (auto [v, weight] : adj[u]) {
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
            }
        }
    }

    cout << "Minimum Spanning Tree:\n";
    for (int i = 1; i < V; i++) {
        cout << parent[i] << " - " << i << "\n";
    }
}

int main() {
    int V = 5; // Number of nodes
    vector<pair<int, int>> adj[V];

    addEdge(adj, 0, 1, 2);
    addEdge(adj, 0, 3, 6);
    addEdge(adj, 1, 2, 3);
    addEdge(adj, 1, 3, 8);
    addEdge(adj, 1, 4, 5);
    addEdge(adj, 2, 4, 7);
    addEdge(adj, 3, 4, 9);

    primMST(adj, V);

    return 0;
}
