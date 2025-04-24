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
    int n;
    std::cin >> n;
    std::vector<int> a(n + 1);
    for(int i = 1; i <=  n; i++) {
        std::cin >> a[i];
    }
    int sum = std::accumulate(a.begin(), a.end(), 0);
    std::vector e(n + 1, std::vector<std::pair<int, int>>());
    for(int i = 1; i < n; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        e[u].emplace_back(v, w);
        e[v].emplace_back(u, w);
    }
    std::vector<int> sze(n + 1);
    auto msub = sze;
    auto dfs = [&](auto &&self, int u, int fa) -> void {
        sze[u] = a[u];
        for(const auto &[v, w] : e[u]) {
            if(v == fa) continue;
            self(self, v, u);
            sze[u] += sze[v];
            msub[u] = std::max(msub[u], sze[v]);
        }
        msub[u] = std::max(msub[u], sum - sze[u]);
    };
    dfs(dfs, 1, 1);
    int g = 0;
    for(int i = 1; i <= n; i++) {
        if(msub[i] <= sum / 2) {
            g = i;
            break;
        }
    }
    std::vector<ll> path(n + 1);
    auto P = [&](auto &&self, int u, int fa) -> void {
        for(const auto &[v, w] : e[u]) {
            if(v == fa) continue;
            path[v] = path[u] + w;
            self(self, v, u);
        }
    };
    ll ans = 0;
    P(P, g, g);
    for(int i = 1;i <= n ; i++) {
        ans += 1LL * path[i] * a[i];
    }
    std::cout << ans << '\n';
}