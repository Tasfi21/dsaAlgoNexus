#include <bits/stdc++.h>

using namespace std;


vector<vector<pair<int, int>>> adj;


int primMaxST(int V)
{
    vector<int> key(V, INT_MIN);
    vector<bool> inMST(V, false);
    vector<int> parent(V, -1);


    priority_queue< pair<int, int> > pq;

    key[0] = 0;
    pq.push({0, 0});

    int mstWeight = 0;

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;

        inMST[u] = true;
        mstWeight += key[u];


        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].first;
            int weight = adj[u][i].second;

            if (!inMST[v] && weight > key[v])
            {
                key[v] = weight;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }


    cout << "parent values:\n";
    for (int i = 0; i < V; i++)
        cout << parent[i]+1 << " ";
    cout << "\n";


    cout << "key values:\n";
    for (int i = 0; i < V; i++)
        cout << key[i] << " ";
    cout << "\n";

    cout << "The weight of the maximum spanning tree is " << mstWeight << "\n";

    return mstWeight;
}


void addEdge(int u, int v, int w)
{
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
}

int main()
{
    int V, E;
    cout<<"give input";
    cin >> V >> E;

    adj.resize(V);
    cout<<"edge weight  ";

    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        addEdge(u, v, w);
    }

    primMaxST(V);
    /* 5 7
1 2 2
1 4 6
2 3 3
2 4 8
2 5 5
3 5 7
4 5 9*/

    return 0;
}



/*#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int, int>>> adj;

int primMaxST(int V)
{
    vector<int> key(V + 1, INT_MIN);
    vector<bool> inMST(V + 1, false);
    vector<int> parent(V + 1, -1);

    priority_queue<pair<int, int>> pq;

    key[1] = 0;
    pq.push({0, 1});

    int mstWeight = 0;

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;

        inMST[u] = true;
        mstWeight += key[u];

        for (int i = 0; i < (int)adj[u].size(); i++) {
            int v = adj[u][i].first;
            int weight = adj[u][i].second;

            if (!inMST[v] && weight > key[v])
            {
                key[v] = weight;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }

    cout << "Edges in Maximum Spanning Tree:\n";
    for (int i = 2; i <= V; i++) {
        if(parent[i] != -1)
            cout << parent[i] << " - " << i << " (weight " << key[i] << ")\n";
    }

    cout << "Total weight of the maximum spanning tree is " << mstWeight << "\n";

    return mstWeight;
}

void addEdge(int u, int v, int w)
{
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
}

int main()
{
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    adj.resize(V + 1);

    cout << "Enter edges in format: u v w (1-based indexing)\n";
    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        addEdge(u, v, w);
    }

    primMaxST(V);

    return 0;



}*/


