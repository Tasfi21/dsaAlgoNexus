
#include <iostream>
#include <vector>
using namespace std;

class DisjointSet {

    vector<int> parent;
    vector<int> rank;

public:

    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        makeSet(n);
    }


    void makeSet(int n) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }


    int findSet(int v) {
        if (v != parent[v]) {
            parent[v] = findSet(parent[v]);
        }
        return parent[v];
    }


    void unionSets(int a, int b) {
        a = findSet(a);
        b = findSet(b);
        if (a != b) {
            if (rank[a] < rank[b])
                swap(a, b);
            parent[b] = a;
            if (rank[a] == rank[b])
                rank[a]++;
        }
    }
};

int main() {
    int n = 7;
    DisjointSet ds(n);

    ds.unionSets(0, 1);
    ds.unionSets(1, 2);
    ds.unionSets(3, 4);
    ds.unionSets(5, 6);
    ds.unionSets(4, 5);

    cout << "FindSet(2): " << ds.findSet(2) << endl;
    cout << "FindSet(6): " << ds.findSet(6) << endl;

    if (ds.findSet(2) == ds.findSet(6))
        cout << "2 and 6 belong to the same set" << endl;
    else
        cout << "2 and 6 belong to different sets" << endl;
 /*// Count connected components
    set<int> uniqueParents;
    for (int i = 0; i < n; i++) {
        uniqueParents.insert(ds.findSet(i));
    }

    cout << "Number of connected components: " << uniqueParents.size() << endl*/
    return 0;


}


