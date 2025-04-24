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

    std::vector fa(n + 1, std::vector<std::pair<int, int>>(m + 1));

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            fa[i][j] = {i, j};
        }
    }

    auto find = [&](auto &&self, std::pair<int, int> x) {
        auto &f = fa[x.first][x.second];
        if(x == f) {
            return x;
        }
        return f = self(self, f);
    };

    auto join = [&](std::pair<int, int> x, std::pair<int, int> y) {
        x = find(find, x);
        y = find(find, y);
        if(x == y) return;
        fa[x.first][x.second] = y;
    };
    
}