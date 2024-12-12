#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void addEdge(vector<pair<int, int>> adj[], int u, int v, int weight)
{
    adj[u].push_back({v, weight});
    adj[v].push_back({u, weight});
}

void primMST(vector<pair<int, int>> adj[], int V)
{
    vector<int> key(V, INT_MAX);
    vector<bool> inMST(V, false);
    vector<int> parent(V, -1);

    key[0] = 0;

    for (int count = 0; count < V - 1; count++)
    {
        int minKey = INT_MAX, u;

        for (int v = 0; v < V; v++)
        {
            if (!inMST[v] && key[v] < minKey)
            {
                minKey = key[v];
                u = v;
            }
        }

        inMST[u] = true;

        for (auto [v, weight] : adj[u])
        {
            if (!inMST[v] && weight < key[v])
            {
                key[v] = weight;
                parent[v] = u;
            }
        }
    }

    cout << "Minimum Spanning Tree:\n";
    for (int i = 1; i < V; i++)
    {
        cout << parent[i] << " - " << i << "\n";
    }
}

int main()
{
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

/*
FUNCTION addEdge(adj, u, v, weight):
    ADD edge (v, weight) to adj[u]
    ADD edge (u, weight) to adj[v]

FUNCTION primMST(adj, V):
    CREATE key array with value INT_MAX
    CREATE inMST array with value false
    CREATE parent array with value -1

    key[0] = 0  // Start with the first node

    FOR count = 0 to V - 1:
        SET minKey = INT_MAX
        FOR v = 0 to V - 1:
            IF v is not in MST AND key[v] < minKey:
                minKey = key[v]
                u = v

        MARK u as included in MST (inMST[u] = true)

        FOR each adjacent vertex v and its weight from adj[u]:
            IF v is not in MST AND weight < key[v]:
                UPDATE key[v] = weight
                SET parent[v] = u

    PRINT "Minimum Spanning Tree"
    FOR i = 1 to V - 1:
        PRINT parent[i] - i  // Display the edge in MST

MAIN:
    SET number of vertices V = 5
    CREATE adjacency list adj for V vertices
    CALL addEdge to add edges
    CALL primMST to compute and print MST

*/