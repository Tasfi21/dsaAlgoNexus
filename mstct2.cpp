
/*#include <bits/stdc++.h>
using namespace std;

// Structure for the input with city names (strings)
struct RawEdge {
    string city1;
    string city2;
    int weight;
    string type; // "Safe" or "Unsafe"
};

// Structure for converted edges using city IDs (ints)
struct Edge {
    int city1;
    int city2;
    int weight;
    string type; // "Safe" or "Unsafe"
};

// Comparator for sorting edges by weight
bool compareEdges(Edge& a, Edge& b) {
    return a.weight < b.weight;
}

// Disjoint Set Union-Find structure
class DisjointSet {
    vector<int> parent, rank;
public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int findSet(int v) {
        if (v != parent[v])
            parent[v] = findSet(parent[v]);
        return parent[v];
    }

    void unionSets(int a, int b) {
        a = findSet(a);
        b = findSet(b);
        if (a != b) {
            if (rank[a] < rank[b]) swap(a, b);
            parent[b] = a;
            if (rank[a] == rank[b]) rank[a]++;
        }
    }
};

// Kruskal's algorithm to find MST with only "Safe" edges
int kruskalMST(int n, vector<Edge>& edges, vector<string>& idToCity) {
    sort(edges.begin(), edges.end(), compareEdges);

    DisjointSet ds(n);
    int mst_weight = 0;
    int edges_in_mst = 0;

    cout << "Edges in MST (Safe only):\n";
    for (int i = 0; i < edges.size(); i++) {
        if (edges[i].type != "Safe") {
            continue; // Skip unsafe edges
        }

        int u = edges[i].city1;
        int v = edges[i].city2;

        if (ds.findSet(u) != ds.findSet(v)) {
            ds.unionSets(u, v);
            mst_weight += edges[i].weight;
            edges_in_mst++;

            cout << idToCity[u] << " - " << idToCity[v]
                 << " (weight: " << edges[i].weight << ")\n";
        }
    }

    // Check if we have a valid MST
    if (edges_in_mst != n - 1) {
        cout << "Impossible to connect all cities using only Safe roads.\n";
        return -1;
    }

    return mst_weight;
}

// Your unchanged main function
int main() {
    int vertex = 6;
    int edgeCount = 9;

    // Input using city names (strings)
    vector<RawEdge> inputEdges = {
        {"Nexara", "Zenith", 2, "Safe"},
        {"Nexara", "Voltra", 3, "Unsafe"},
        {"Zenith", "Voltra", 4, "Safe"},
        {"Voltra", "Lumina", 1, "Safe"},
        {"Lumina", "Solaria", 6, "Unsafe"},
        {"Solaria", "Aether", 5, "Safe"},
        {"Zenith", "Aether", 2, "Safe"},
        {"Voltra", "Aether", 7, "Unsafe"},
        {"Lumina", "Zenith", 1, "Safe"}
    };

    // Step 1: Assign integer IDs to cities
    map<string, int> cityToID;
    vector<string> idToCity;
    int idCounter = 0;

    for (int i = 0; i < inputEdges.size(); i++) {
        string c1 = inputEdges[i].city1;
        string c2 = inputEdges[i].city2;

        if (cityToID.find(c1) == cityToID.end()) {
            cityToID[c1] = idCounter;
            idToCity.push_back(c1);
            idCounter++;
        }

        if (cityToID.find(c2) == cityToID.end()) {
            cityToID[c2] = idCounter;
            idToCity.push_back(c2);
            idCounter++;
        }
    }

    // Step 2: Convert inputEdges to edges with integer city IDs
    vector<Edge> edges;
    for (int i = 0; i < inputEdges.size(); i++) {
        Edge e;
        e.city1 = cityToID[inputEdges[i].city1];
        e.city2 = cityToID[inputEdges[i].city2];
        e.weight = inputEdges[i].weight;
        e.type = inputEdges[i].type;
        edges.push_back(e);
    }

    // Step 3: Run Kruskal's algorithm
    int mst_weight = kruskalMST(vertex, edges, idToCity);

    if (mst_weight != -1) {
        cout << "Total weight of MST = " << mst_weight << endl;
    }

    return 0;
}*/
#include <bits/stdc++.h>
using namespace std;

// Structure for raw input (with city names)
struct RawEdge {
    string city1;
    string city2;
    int weight;
    string type; // "Safe" or "Unsafe"
};

// Structure for converted edges (integer IDs)
struct Edge {
    int city1;
    int city2;
    int weight;
    string type; // "Safe" or "Unsafe"
};

// Global adjacency list
vector<vector<pair<int, int>>> adj;

// Add a Safe edge (undirected)
void addEdge(int u, int v, int w) {
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
}

// Prim’s MST algorithm (only for Safe roads)
int primMST(int V, vector<string>& idToCity) {
    vector<int> key(V, INT_MAX);
    vector<bool> inMST(V, false);
    vector<int> parent(V, -1);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    key[0] = 0;
    pq.push({0, 0});

    int mstWeight = 0;
    int connected = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;
        inMST[u] = true;
        mstWeight += key[u];
        connected++;

        for (auto& neighbor : adj[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }

    if (connected != V) {
        cout << "Impossible to connect all cities using only Safe roads.\n";
        return -1;
    }

    cout << "Edges in MST (Safe only):\n";
    for (int i = 1; i < V; i++) {
        cout << idToCity[parent[i]] << " - " << idToCity[i]
             << " (weight: " << key[i] << ")\n";
    }

    return mstWeight;
}

int main() {
    // Input with city names
    vector<RawEdge> inputEdges = {
        {"Nexara", "Zenith", 2, "Safe"},
        {"Nexara", "Voltra", 3, "Unsafe"},
        {"Zenith", "Voltra", 4, "Safe"},
        {"Voltra", "Lumina", 1, "Safe"},
        {"Lumina", "Solaria", 6, "Unsafe"},
        {"Solaria", "Aether", 5, "Safe"},
        {"Zenith", "Aether", 2, "Safe"},
        {"Voltra", "Aether", 7, "Unsafe"},
        {"Lumina", "Zenith", 1, "Safe"}
    };

    // Step 1: Map city names to IDs
    map<string, int> cityToID;
    vector<string> idToCity;
    int idCounter = 0;

    for (auto& e : inputEdges) {
        if (cityToID.find(e.city1) == cityToID.end()) {
            cityToID[e.city1] = idCounter++;
            idToCity.push_back(e.city1);
        }
        if (cityToID.find(e.city2) == cityToID.end()) {
            cityToID[e.city2] = idCounter++;
            idToCity.push_back(e.city2);
        }
    }

    int V = idToCity.size();
    adj.resize(V);

    // Step 2: Add only Safe edges to adjacency list
    for (auto& e : inputEdges) {
        if (e.type == "Safe") {
            addEdge(cityToID[e.city1], cityToID[e.city2], e.weight);
        }
    }

    // Step 3: Run Prim’s MST
    int totalWeight = primMST(V, idToCity);

    if (totalWeight != -1)
        cout << "Total weight of MST = " << totalWeight << endl;

    return 0;
}



