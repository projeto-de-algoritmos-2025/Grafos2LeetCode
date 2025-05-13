#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minTimeToReach(vector<vector<int>>& openTime) {
        int n = openTime.size();
        int m = openTime[0].size();
        const int INF = INT_MAX;
        
        vector<vector<int>> dist(n, vector<int>(m, INF));
        using T = tuple<int,int,int,int>;
        priority_queue<T, vector<T>, greater<T>> pq;
        
        dist[0][0] = 0;
        pq.emplace(0, 0, 0, 0);        
        int dr[4] = {1,-1,0,0};
        int dc[4] = {0,0,1,-1};
        
        while (!pq.empty()) {
            auto [t, r, c, last] = pq.top(); 
            pq.pop();
            if (t > dist[r][c]) continue;
            
            int nextDur = (last == 1 ? 2 : 1);
            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i], nc = c + dc[i];
                if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
                
                int start = max(t, openTime[nr][nc]);
                int arrive = start + nextDur;
                if (arrive < dist[nr][nc]) {
                    dist[nr][nc] = arrive;
                    pq.emplace(arrive, nr, nc, nextDur);
                }
            }
        }
        
        return dist[n-1][m-1];
    }
};
