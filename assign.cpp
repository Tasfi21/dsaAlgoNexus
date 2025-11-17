
#include <bits/stdc++.h>

using namespace std;


vector<vector<pair<int, int>>> adj;


long long primMPST(int V)
{
    vector<double> key(V, DBL_MAX);
    vector<bool> inMST(V, false);
    vector<int> parent(V, -1);
    vector<int> weightToParent(V, 1);


    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;

    key[0] = 0.0;
    pq.push({0.0, 0});

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;
        inMST[u] = true;

        for (int i = 0; i < adj[u].size(); i++)
        {
            int v = adj[u][i].first;
            int w = adj[u][i].second;

            double logWeight = log(w);

            if (!inMST[v] && logWeight < key[v])
            {
                key[v] = logWeight;
                parent[v] = u;
                weightToParent[v] = w;
                pq.push({key[v], v});
            }
        }
    }


    cout << "Edges in MPST:\n";
    long long product = 1;
    for (int i = 1; i < V; i++)
    {
        cout << parent[i] << " - " << i << "\n";
        product *= weightToParent[i];
    }

    cout << "Minimum product: " << product << endl;

    return product;
}


void addEdge(int u, int v, int w)
{
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
}

int main()
{
    // number of nodes=5


    int n, m;
    cout<<"number of vextex and edges \n";
    cin >> n >> m;

    adj.resize(n);
    cout<<"now give u,v,w\n";

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        addEdge(u, v, w);
    }

    primMPST(n);

    // Sample input (graph from the original example)
    /* addEdge(0, 1, 2);
     addEdge(0, 3, 6);
     addEdge(1, 2, 3);
     addEdge(1, 3, 8);
     addEdge(1, 4, 5);
     addEdge(2, 4, 7);
     addEdge(3, 4, 9);*/



    return 0;
}


