#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int minDays(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int initialComponents = countConnectedComponents(grid, m, n);
        if (initialComponents == 0 || initialComponents > 1) return 0;
        if (countCells(grid, m, n) == 1) return 1;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    grid[i][j] = 0;
                    if (countConnectedComponents(grid, m, n) != 1) {
                        grid[i][j] = 1;
                        return 1;
                    }
                    grid[i][j] = 1;
                }
            }
        }
        return 2;
    }

private:
    struct UnionFind {
        vector<int> parent;
        UnionFind(int size): parent(size) {
            for (int i = 0; i < size; ++i)
                parent[i] = i;
        }

        int findSet(int x) {
            return parent[x] == x ? x : parent[x] = findSet(parent[x]);
        }

        void unionSets(int a, int b) {
            int rootA = findSet(a);
            int rootB = findSet(b);
            if (rootA != rootB)
                parent[rootB] = rootA;
        }
    };

    int countCells(const vector<vector<int>>& grid, int m, int n) {
        int total = 0;
        for (const auto& row : grid)
            for (int val : row)
                total += val;
        return total;
    }

    int countConnectedComponents(const vector<vector<int>>& grid, int m, int n) {
        int totalCells = m * n;
        UnionFind uf(totalCells);
        vector<bool> isLand(totalCells, false);
        auto getIndex = [&](int r, int c) { return r * n + c; };
        
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (grid[r][c] == 1) {
                    isLand[getIndex(r, c)] = true;
                }
            }
        }

        vector<pair<int,int>> directions = {{1,0}, {0,1}};
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (grid[r][c] == 1) {
                    int idx = getIndex(r, c);
                    for (auto& d : directions) {
                        int nr = r + d.first;
                        int nc = c + d.second;
                        if (nr < m && nc < n && grid[nr][nc] == 1) {
                            uf.unionSets(idx, getIndex(nr, nc));
                        }
                    }
                }
            }
        }

        unordered_set<int> roots;
        for (int i = 0; i < totalCells; ++i) {
            if (isLand[i])
                roots.insert(uf.findSet(i));
        }
        return roots.size();
    }
};
