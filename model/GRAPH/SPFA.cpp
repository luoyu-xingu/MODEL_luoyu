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
    std::cout << std::fixed << std::setprecision(15);
    int t = 1;
    std::cin >> t;
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
        if(w >= 0) {
            e[u].emplace_back(v, w);
            e[v].emplace_back(u, w);
        }
        else {
            e[u].emplace_back(v, w);
        }
    } 
    std::vector<int> dis(n + 1, inf);
    auto SPFA = [&](int s) {
        std::vector<int> vis(n + 1);
        int cnt = 0;
        dis[s] = 0;
        std::queue<int> q;
        q.push(s);
        while(!q.empty()) {
            cnt++;
            if(cnt > n) break;
            int sze = q.size();
            for(int i = 1; i <= q.size(); i++) {
                auto u = q.front();
                q.pop();
                vis[u] = 0;
                for(auto &[v, w] : e[u]) {
                    if(dis[v] > dis[u] + w) {
                        dis[v] = dis[u] + w;
                        if(!vis[v]) {
                            vis[v] = 1;
                            q.push(v);  
                        }
                    }
                }
            }
        }
        return cnt > n;
    };
    if(SPFA(1)) {
        std::cout << "YES\n";
    }
    else {
        std::cout << "NO\n";
    }
}