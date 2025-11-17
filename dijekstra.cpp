#include <bits/stdc++.h>

using namespace std;


vector<vector<pair<int, int>>> adj;


void addEdge(int u, int v, int w)
{
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
}


void dijkstra(int start, vector<int>& key,vector<int>& parent)
{
    int V = adj.size();
    key.assign(V, INT_MAX);
    key[start] = 0;
    parent.assign(V,-1);


    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty())
    {
        pair<int, int> top = pq.top();
        pq.pop();

        int d = top.first;
        int u = top.second;

        if (d > key[u]) continue;

        for (int i = 0; i < adj[u].size(); i++)
        {
            int v = adj[u][i].first;
            int weight = adj[u][i].second;

            if (key[u] + weight < key[v])
            {
                key[v] = key[u] + weight;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }
}


int main()
{
    int V = 5;
    adj.resize(V);


    addEdge(0, 1, 10);
    addEdge(0, 4, 5);
    addEdge(1, 2, 1);
    addEdge(1, 4, 2);
    addEdge(2, 3, 4);
    addEdge(3, 0, 7);
    addEdge(3, 2, 6);
    addEdge(4, 1, 3);
    addEdge(4, 2, 9);
    addEdge(4, 3, 2);

    int start = 0;
    vector<int> key;
    vector<int>track;
    vector<int>parent;

    dijkstra(start, key,parent);



    for (int i = 0; i < V; i++)
    {
        cout << "Shortest distances from node " << start << "  to  ";
        if (key[i] == INT_MAX)
            cout << "Node " << i << "infinity";
        else
        {
            track.clear();
              cout << "Node " << i << ": " << key[i] << "  parent "<<parent[i]<<"\n";
                cout<<"path is ";
            for(int v=i; v!=-1; v=parent[v])
            {

                track.push_back(v);

            }
            for(int j=track.size()-1; j>=0; j--)
            {

                cout<<track[j]<<"   ";
            }
            cout << "\n";
        }

    }

    return 0;
}

