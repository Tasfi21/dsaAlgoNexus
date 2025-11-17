#include <bits/stdc++.h>

using namespace std;


struct Edge
{
    int u, v, weight;
};


bool compareEdges( Edge& a,Edge& b)
{
    return a.weight < b.weight;
}


class DisjointSet
{

    vector<int> parent, rank;
public:
    DisjointSet(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }

    int findSet(int v)
    {
        if (v != parent[v])
            parent[v] = findSet(parent[v]);
        return parent[v];
    }

    void unionSets(int a, int b)
    {
        a = findSet(a);
        b = findSet(b);
        if (a != b)
        {
            if (rank[a] < rank[b]) swap(a, b);
            parent[b] = a;
            if (rank[a] == rank[b]) rank[a]++;
        }
    }
};

int kruskalMST(int n, vector<Edge>& edges)
{

    sort(edges.begin(), edges.end(), compareEdges);

    DisjointSet ds(n);
    int mst_weight = 0;

    cout << "Edges in MST:\n";
    for (int i = 0; i < edges.size(); i++)
    {
        if (ds.findSet(edges[i].u) != ds.findSet(edges[i].v))
        {
            ds.unionSets(edges[i].u, edges[i].v);
            mst_weight += edges[i].weight;
            cout << edges[i].u << " - " << edges[i].v << " (weight: " << edges[i].weight << ")\n";
        }
    }

    return mst_weight;
}

int main()
{
    int n = 6;
    vector<Edge> edges =
    {
        {0, 1, 4}, {0, 2, 4}, {1, 2, 2},
        {2, 3, 3}, {2, 5, 2}, {2, 4, 4},
        {3, 4, 3}, {5, 4, 3}
    };
    /* int n, m; // n = number of vertices, m = number of edges
    cout << "Enter number of vertices and edges: ";
    cin >> n >> m;

    vector<Edge> edges;

    cout << "Enter each edge in the format: u v weight\n";
    for (int i = 0; i < m; ++i) {
       int u, v, w;
       cin >> u >> v >> w;
       edges.push_back({u, v, w});
    }*/

    int mst_weight = kruskalMST(n, edges);
    cout << "Total weight of MST = " << mst_weight << endl;

    return 0;
}

