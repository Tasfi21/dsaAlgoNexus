
#include <bits/stdc++.h>

using namespace std;


vector<vector<pair<int, int>>> adj;


int primMST(int V) {
    vector<int>key(V,INT_MAX) ;
    vector<bool >inMST(V,false);
   vector< int >parent(V,-1);



    priority_queue< pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;

    key[0] = 0;
    pq.push({0, 0});

    int mstWeight = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;

        inMST[u] = true;
        mstWeight += key[u];

        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].first;
            int weight = adj[u][i].second;

            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }

    cout << "Edges in MST:\n";
    for (int i = 1; i < V; i++) {
        cout << parent[i] << " - " << i << " (weight " << key[i] << ")\n";
    }

    return mstWeight;
}


void addEdge(int u, int v, int w) {
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
}

int main() {
    int V = 5;

    adj.resize(V);

    addEdge(0, 1, 2);
    addEdge(0, 3, 6);
    addEdge(1, 2, 3);
    addEdge(1, 3, 8);
    addEdge(1, 4, 5);
    addEdge(2, 4, 7);
    addEdge(3, 4, 9);

    int totalWeight = primMST(V);

    cout << "Total weight of MST = " << totalWeight << endl;

    /* int V, E;
    cout<<"give input";
    cin >> V >> E;

    adj.resize(V+1);
    cout<<"edge weight  ";

    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        addEdge(u, v, w);
    }*/


    return 0;
}
