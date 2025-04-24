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
    std::vector<int> d(n + 1);
    int q = log2(n);
    std::vector st(n + 1, std::vector<int>(q + 1));
    auto dfs = [&](auto &&self, int u, int f, int cnt = 1) -> void {
        d[u] = cnt;
        st[u][0] = f;
        for(int j = 1; (1 << j) <= d[u]; j++) {
            st[u][j] = st[st[u][j - 1]][j - 1]; 
        }
        for(auto v : e[u]) {
            if(v == f) {
                continue;
            }
            self(self, v, u, cnt + 1);
        }
    };
    dfs(dfs, s, 0);
    auto LCA = [&](int x, int y) {
        if(d[x] < d[y]) {
            std::swap(x, y);
        }
        int k = d[x] - d[y];
        for(int i = q; i >= 0; i--) {
            if(1 & (k >> i)) {
                k -= (1 << i);
                x = st[x][i];
            }
        }
        if(x == y) {
            return y;
        }
        for(int i = q; i >= 0; i--) {
            if(st[x][i] == st[y][i]) {
                continue;
            }
            else {
                x = st[x][i], y = st[y][i]; 
            }
        }
        return st[x][0];
    };
    while(m--) {
        int a, b;
        std::cin >> a >> b;
        std::cout << LCA(a, b) << '\n';
    }
}