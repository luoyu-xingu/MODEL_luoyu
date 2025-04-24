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
//    std::cin >> t;
    while(t--) solve();
    return 0;
}
void solve(){
    int n, m ,s;
    std::cin >> n >> m >> s;
    std::vector e(n + 1, std::vector<int>());
    for(int i = 1; i < n; i++) {
        int u, v;
        std::cin >> u >> v;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    std::vector q(n + 1, std::vector<std::pair<int, int>>());
    for(int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        q[u].emplace_back(v, i);
        q[v].emplace_back(u, i);
    }
    std::vector<char> vis(n + 1);
    std::vector<int> fa(n + 1);
    std::iota(fa.begin(), fa.end(), 0);
    auto find = [&](auto &&self, int x) {
        if(fa[x] == x) {
            return x;
        }
        return fa[x] = self(self, fa[x]);
    };
    std::vector<int> ans(m);
    auto tarjan = [&](auto &&self, int u, int f) -> void{
        vis[u] = 1;
        for(auto v : e[u]) {
            if(v == f) {
                continue;
            }
            else {
                self(self, v, u);
                fa[v] = u;
            }
        }
        for(auto [v, i] : q[u]) {
            if(!vis[v]) {
                continue;
            }
            else {
                ans[i] = find(find, v);
            }
        }
    };

    tarjan(tarjan, s, s);

    for(auto x : ans) {
        std::cout << x << '\n';
    }
}