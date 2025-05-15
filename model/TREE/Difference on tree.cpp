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

    while(t--) {
       solve();
    }

    return 0;
}

void solve(){
    int n, k;
    std::cin >> n >> k;

    std::vector<std::vector<int>> e(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        std::cin >> u >> v;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }

    std::vector<int> dep(n + 1), a(n + 1);
    std::vector<std::array<int, 20>> st(n + 1);

    auto dfs = [&](auto &&self, int u = 1, int f = 0) -> void {
        dep[u] = dep[f] + 1;
        st[u][0] = f;
        for (int i = 1; (1 << i) <= dep[u]; i++) {
            st[u][i] = st[st[u][i - 1]][i - 1];
        }

        for (auto v : e[u]) {
            if (v == f) {
                continue;
            }

            self(self, v, u);
        }
    };  

    dfs(dfs);

    auto lca = [&](int x, int y) {
        if (dep[x] < dep[y]) {
            std::swap(x, y);
        }

        int k = dep[x] - dep[y];

        if (k) {
            for (int i = 19; i >= 0; i--) {
                if (k >> i & 1) {
                    x = st[x][i];
                    k -= 1 << i;
                }
            }
        }

        if (x == y) {
            return y;
        }

        for (int i = 19; i >= 0; i--) {
            if (st[x][i] != st[y][i]) {
                x = st[x][i];
                y = st[y][i];
            }
        }
        return st[x][0];
    };

    auto add = [&](int x, int y) {
        a[x]++;
        a[y]++;
        int L = lca(x, y);
        a[L]--;
        a[st[L][0]]--;
    };

    while(k--) {
        int x, y;
        std::cin >> x >> y;
        add(x, y);
    }

    auto D = [&](auto &&self, int u, int f) -> void {
        for (auto v : e[u]) {
            if (v == f) {
                continue;
            }

            self(self, v, u);
            a[u] += a[v];
        }
    };

    D(D, 1, 1);

    
    std::cout << *std::max_element(a.begin() + 1, a.end()) << "\n";
}