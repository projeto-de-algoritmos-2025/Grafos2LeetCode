#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        attachOriginalIndices(edges);
        sortByWeight(edges);
        int baseWeight = computeMST(n, edges, -1, -1);
        vector<int> critical, pseudo;
        for (int i = 0; i < edges.size(); ++i) {
            if (computeMST(n, edges, i, -1) > baseWeight)
                critical.push_back(edges[i][3]);
            else if (computeMST(n, edges, -1, i) == baseWeight)
                pseudo.push_back(edges[i][3]);
        }
        return {critical, pseudo};
    }

private:
    struct UnionFind {
        vector<int> parent;
        UnionFind(int size): parent(size) { iota(parent.begin(), parent.end(), 0); }
        int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
        void unite(int a, int b) { parent[find(b)] = find(a); }
    };

    void attachOriginalIndices(vector<vector<int>>& edges) {
        for (int i = 0; i < edges.size(); ++i)
            edges[i].push_back(i);
    }

    void sortByWeight(vector<vector<int>>& edges) {
        sort(edges.begin(), edges.end(), [](auto& a, auto& b) {
            return a[2] < b[2];
        });
    }

    int computeMST(int n, vector<vector<int>>& edges, int skip, int pick) {
        UnionFind uf(n);
        int weight = 0;
        if (pick != -1) {
            weight += edges[pick][2];
            uf.unite(edges[pick][0], edges[pick][1]);
        }
        for (int i = 0; i < edges.size(); ++i) {
            if (i == skip) continue;
            auto& e = edges[i];
            int u = e[0], v = e[1], w = e[2];
            if (uf.find(u) != uf.find(v)) {
                uf.unite(u, v);
                weight += w;
            }
        }
        int root = uf.find(0);
        for (int i = 1; i < n; ++i)
            if (uf.find(i) != root) return INT_MAX;
        return weight;
    }
};
