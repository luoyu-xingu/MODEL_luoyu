#include<bits/stdc++.h>

using ll = long long;

std::array<int, 8> dx = {1, -1, 0, 0, 1, -1, 1, -1};
std::array<int, 8> dy = {0, 0, 1, -1, 1, -1, -1, 1};

const int inf = 0x3f3f3f3f;
const ll  Inf = 0x3f3f3f3f3f3f3f3f;

void solve();

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t = 1;
    //std::cin >> t;
    while(t--) solve();
    return 0;
}
void solve(){
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<std::pair<int, int>>> e(n + 1);

    for(int i = 1; i <= m; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        e[u].emplace_back(v, w);
        e[v].emplace_back(u, w);
    }
    
    std::vector dis(n + 1, std::vector<ll>(n + 1, Inf));
    
    auto dijkstra = [&](int s) {
        std::vector<int> vis(n + 1);
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,std::greater<std::pair<int, int>>> pq;
        dis[s][s] = 0;
        
        pq.emplace(dis[s][s], s);
        while(!pq.empty()) {
            auto [_, u] = pq.top();
            pq.pop();
            if(vis[u]) continue;
            for(auto [v, w] : e[u]) {
                if(dis[s][v] > dis[s][u] + w) {
                    dis[s][v] = dis[s][u] + w;
                    pq.emplace(dis[s][v], v); 
                }
            }
        }
    };
    
    for(int i = 1; i <= n; i++) {
        dijkstra(i);
    }
    
    std::vector<int> d(n + 1);
    auto t = d;
    for(int i = 1; i <= n; i++) {
        std::cin >> d[i];
    }
    
    for(int i = 1; i <= n; i++) {
        std::cin >> t[i];
    }

    e = std::vector<std::vector<std::pair<int, int>>>(n + 1);

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n;j++) {
            if(dis[i][j] <= d[i]) {
                e[i].emplace_back(j, t[i]);
            }
        }
    }
    
    dis = std::vector(n + 1, std::vector<ll>(n + 1, Inf));

    dijkstra(1);
    
    for(int i = 1; i <= n; i++) {
        if(dis[1][i] == Inf) {
            std::cout << -1 << ' ';
        } 
        else {
            std::cout << dis[1][i] << ' ';
        }
    }
}
