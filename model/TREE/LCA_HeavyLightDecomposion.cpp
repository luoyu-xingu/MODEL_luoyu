#include<bits/stdc++.h>

using ll = long long;

void solve();
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();

    return 0;
}

void solve() {
    int n, m, r;
    std::cin >> n >> m >> r;

    std::vector<std::vector<int>> e(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        std::cin >> u >> v;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }

    std::vector<int> hson(n + 1), dep(n + 1), top(n + 1), dfn(n + 1), rdfn(n + 1), fa(n + 1), sze(n + 1);
    auto dfs = [&](auto &&self, int u, int f) -> void {
        fa[u] = f;
        dep[u] = dep[f] + 1;
        sze[u] = 1;
        for (auto v : e[u]) {
            if (v == f) {
                continue;
            } 
            self(self, v, u);
            sze[u] += sze[v];
            if (sze[v] > sze[hson[u]]) {
                hson[u] = v;
            }
        }
    };
    dfs(dfs, r, r);

    int cur = 0;
    auto Set = [&](auto &&self, int u, int f) -> void {
        top[u] = f;
        dfn[u] = ++cur;
        rdfn[cur] = u;

        if (hson[u] == 0) {
            return;
        }

        self(self, hson[u], f);
        for (auto v : e[u]) {
            if (v == hson[u] || v == fa[u]) {
                continue;
            }
            self(self, v, v);
        }
    };
    Set(Set, r, r);
    //return;
    auto Lca = [&](int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) {
                v = fa[top[v]];
            } else {
                u = fa[top[u]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    };

    while (m--) {
        int u, v;
        std::cin >> u >> v;
        std::cout << Lca(u, v) << "\n";
    }

}